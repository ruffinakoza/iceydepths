/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
*	ROM 2.4 is copyright 1993-1996 Russ Taylor			   *
*	ROM has been brought to you by the ROM consortium		   *
*	    Russ Taylor (rtaylor@efn.org)				   *
*	    Gabrielle Taylor						   *
*	    Brian Moore (zump@rom.org)					   *
*	By using this code, you have agreed to follow the terms of the	   *
*	ROM license, in the file Rom24/doc/rom.license			   *
***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "merc.h"
#include "arena.h"

void do_startwar(CHAR_DATA *ch, char *argument)
{
  char buf[MAX_STRING_LENGTH];
  char arg1[MAX_INPUT_LENGTH], arg2[MAX_INPUT_LENGTH];
  char arg3[MAX_INPUT_LENGTH];
  DESCRIPTOR_DATA *d;

  argument = one_argument(argument, arg1);
  argument = one_argument(argument, arg2);
  argument = one_argument(argument, arg3);
  if (arg1[0] == '\0' || arg2[0] == '\0' || arg3[0] == '\0')
  {
    send_to_char("Syntax: startwar <type> <min_level> <max_level>\n\r", ch);
    return;
  }

  if (atoi(arg1) < 1 || atoi(arg1) > 2)
  {
    send_to_char("The type either has to be 1, or 2.\n\r", ch);
    return;
  }

  if (atoi(arg2) <= 0 || atoi(arg2) > 90)
  {
    send_to_char("Level must be between 1 and 90.\n\r", ch);
    return;
  }

  if (atoi(arg3) <= 0 || atoi(arg3) > 90)
  {
    send_to_char("Level must be between 1 and 90.\n\r", ch);
    return;
  }

  if (atoi(arg3) < atoi(arg2))
  {
    send_to_char("Max level must be greater than the min level.\n\r", ch);
    return;
  }

  if (iswar == TRUE)
  {
    send_to_char("There is already a war going!\n\r", ch);
    return;
  }

  iswar = TRUE;
  wartype = atoi(arg1);
  min_level = atoi(arg2);
  max_level = atoi(arg3);
  sprintf(buf, "{c%s {Rwar started for levels {Y%d {Rto {Y%d{R.  Type 'WAR' to kill or be killed", wartype == 1 ? "Single" : "Team", min_level, max_level);
  do_wartalk(buf);
  wartimeleft = 3;
  for (d = descriptor_list; d != NULL; d = d->next)
  {
    if (!IS_NPC(d->character))
    {
      if (IS_SET(d->character->act, PLR_ARENA))
        REMOVE_BIT(d->character->act, PLR_ARENA);
    }
  }
}

void do_war(CHAR_DATA *ch)
{
  char buf[MAX_STRING_LENGTH];
  ROOM_INDEX_DATA *location;

  if (iswar != TRUE) 
  {
    send_to_char("There is no war going!\n\r", ch);
    return;
  }

  if (ch->level < min_level || ch->level > max_level)
  {
    send_to_char("Sorry, you can't join this war.\n\r", ch);
    return;
  }

  if (IS_SET(ch->act, PLR_ARENA))
  {
    send_to_char("I don't think so.\n\r", ch);
    return;
  }

  if (wartype == 1)
  {
    if ((location = get_room_index(SINGLE_WAR_WAITING_ROOM)) == NULL)
    {
      send_to_char("Arena is not yet completed, sorry.\n\r", ch);
      return;
    }
    else
    {
      act("$n goes to get $s {Rass{w whipped in war!", ch, NULL, NULL, TO_ROOM); 
      char_from_room(ch);
      char_to_room(ch, location);
      SET_BIT(ch->act, PLR_ARENA);
      sprintf(buf, "{c%s {R({cLevel {Y%d{R) joins the war!", ch->name, ch->level);
      do_wartalk(buf);
      act("$n arrives to get $s {Rass{w whipped!", ch, NULL, NULL, TO_ROOM);
      inwar++;
      do_look(ch, "auto");
      return;
    }
  }
}

void war_update(void)
{
  char buf[MAX_STRING_LENGTH];
  CHAR_DATA *ch;
  DESCRIPTOR_DATA *d;
  ROOM_INDEX_DATA *random;
  int x;
  
  if (wartimeleft > 0)
  {
    sprintf(buf, "%d tick%s left to join the war.", wartimeleft, wartimeleft == 1 ? "" : "s");
    do_wartalk(buf);
    sprintf(buf, "%d %s %s fighting in the war, so far.", inwar, inwar == 1 ? "person" : "people", inwar == 1 ? "is" : "are");
    do_wartalk(buf);
    sprintf(buf, "Type of war: {Y%d {R- {Y%d{R, {C%s war{R.{w", min_level, max_level, wartype == 1 ? "Single" : "Team");
    do_wartalk(buf);
    wartimeleft--;
    return;
  }

  if (wartimeleft == 0 && iswar == TRUE && wartimer == 0)
  {  
    if (inwar == 0 || inwar == 1)
    {
      sprintf(buf, "Not enough people for war.  War reset.");
      do_wartalk(buf);
      iswar = FALSE;
      wartimeleft = 0;
      wartimer = 0;
      min_level = 0;
      max_level = 0;
      wartype = 0;
      for(d = descriptor_list; d != NULL; d = d->next)
      {
        if (IS_SET(d->character->act, PLR_ARENA))
        {
          char_from_room(d->character);
          char_to_room(d->character, (get_room_index(ROOM_VNUM_TEMPLE)));
          do_look(d->character, "auto");
        }
      }
    }
    else
    {
      sprintf(buf, "The battle begins! %d players are fighting!", inwar);
      do_wartalk(buf);
      wartimer = 20;
      for(d = descriptor_list; d != NULL; d = d->next)
      {
        if (IS_SET(d->character->act, PLR_ARENA))
        {
          random = get_room_index(12004);
          char_from_room(d->character);
          char_to_room(d->character, random);
          do_look(d->character, "auto");
        }
      }
    }
  }
  return;
}
