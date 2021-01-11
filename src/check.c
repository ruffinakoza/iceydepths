/***************************************************************************
*       FALLEN ANGLEL mud is protected by french law of intelectual        *
*                            property. we share freely all we have coded   *
*                            provided this message isn't removed from the  *
*                            files and you respect the name of all the     *
*                            coders,area builders, and all the Diku,Merc,  *
*                            Rom licences.                                 *
*                                                                          *
*                   Thank to : ROM consortium .                            *
*                   Big thank to : Gary Gygax !!!!!!!!!!!!!!               *
*                                                                          *
*       Fallen Angel project by : Loran      ( laurent zilbert )           *
*                                 Silfen or                                *
*                                 Gwendoline ( jerome despret  )           *
*                                                                          *
*       Despret@ecoledoc.lip6.fr ...                                       *
***************************************************************************/

/***************************************************************************
*                                                                          *
*  To use this snipet you must set the following line in the "check" help  *
*                                                                          *
*    Coded for Fallen Angels by : Zilber laurent,Despret jerome.           *
*                                                                          *
*  And send a mail to say you use it ( feel free to comment ) at :         *
*                                                                          *
*  [despret@ecoledoc.lip6.fr] or/and at [loran@hotmail.com]                *
****************************************************************************/

/***************************************************************************
*                                                                          *
* If you want to put this snipet on your web site you are allowed to but   *
*  the file must remain unchanged and you have to send us a mail at :      *
*                                                                          *
*  [despret@ecoledoc.lip6.fr] or/and at [loran@hotmail.com]                *
*  with the site URL.                                                      *
*                                                                          *
***************************************************************************/

#if defined(macintosh)
#include <types.h>
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merc.h"
#include "db.h"
#include "magic.h"


/* Immortal command */

void do_check( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    BUFFER *buffer;
    CHAR_DATA *victim;
    AFFECT_DATA *paf;
    int count = 1;
    int last_room = 0;
    
    one_argument( argument, arg );
    
    if (arg[0] == '\0'|| !str_prefix(arg,"stats"))
    {
        buffer = new_buf();
    	for (victim = char_list; victim != NULL; victim = victim->next)
    	{
    	    if (IS_NPC(victim) || !can_see(ch,victim)) 
    	    	continue;
    	    	
	    if (victim->desc == NULL)
	    {
	    	sprintf(buf,"%3d) %s is linkdead.\n\r", count, victim->name);
	    	add_buf(buffer, buf);
	    	count++;
	    	continue;	    	
	    }
	    
	    if (victim->desc->connected >= CON_GET_NEW_RACE
	     && victim->desc->connected <= CON_PICK_WEAPON)
	    {
	    	sprintf(buf,"%3d) %s is being created.\n\r",
 	    	    count, victim->name);
	    	add_buf(buffer, buf);
	    	count++;
	    	continue;
	    }
	    
	    if ( (victim->desc->connected == CON_GET_OLD_PASSWORD
	       || victim->desc->connected >= CON_READ_IMOTD)
	     && get_trust(victim) <= get_trust(ch) )
	    {
	    	sprintf(buf,"%3d) %s is connecting.\n\r",
 	    	    count, victim->name);
	    	add_buf(buffer, buf);
	    	count++;
	    	continue; 	    		 
	    }
	    
	    if (victim->desc->connected == CON_PLAYING)
	    {
	        if (get_trust(victim) > get_trust(ch))
	            sprintf(buf,"%3d) %s.\n\r", count, victim->name);
	        else
	        {
		    sprintf(buf,"%3d) %s, Level %d connected since %d hours (%d total hours)\n\r",
		    	count, victim->name,victim->level,
                        ((int)(current_time - victim->logon)) /3600, 
		    	(victim->played + (int)(current_time - victim->logon)) /3600 );
		    add_buf(buffer, buf);
		    if (arg[0]!='\0' && !str_prefix(arg,"stats"))
		    {
		      sprintf(buf,"  %d HP %d Mana (%d %d %d %d %d) %ld golds %d Tr %d Pr %d Qpts.\n\r",
		    	victim->max_hit, victim->max_mana,victim->perm_stat[STAT_STR],
		    	victim->perm_stat[STAT_INT],victim->perm_stat[STAT_WIS],
		    	victim->perm_stat[STAT_DEX],victim->perm_stat[STAT_CON],
		    	victim->gold + victim->silver/100,
		    	victim->train, victim->practice, victim->questpoints);
		      add_buf(buffer, buf);
		    }
		    count++;
		}
	        continue;
	    }
	    
	    sprintf(buf,"%3d) bug (oops)...please report to Loran: %s %d\n\r",
	    	count, victim->name, victim->desc->connected);
	    add_buf(buffer, buf);
	    count++;   
    	}
    	page_to_char(buf_string(buffer),ch);
    	free_buf(buffer);
    	return;
    }
    
    if (!str_prefix(arg,"eq"))
    {
        buffer = new_buf();
    	for (victim = char_list; victim != NULL; victim = victim->next)
    	{
    	    if (IS_NPC(victim) 
    	     || victim->desc->connected != CON_PLAYING
    	     || !can_see(ch,victim)
    	     || get_trust(victim) > get_trust(ch) )
    	    	continue;
    	    	
    	    sprintf(buf,"%3d) %s, %d items (weight %d) Hit:%d Dam:%d Save:%d AC:%d %d %d %d.\n\r",
    	    	count, victim->name, victim->carry_number, victim->carry_weight, 
    	    	victim->hitroll, victim->damroll, victim->saving_throw,
    	    	victim->armor[AC_PIERCE], victim->armor[AC_BASH],
    	    	victim->armor[AC_SLASH], victim->armor[AC_EXOTIC]);
    	    add_buf(buffer, buf);
    	    count++;  
    	}
    	page_to_char(buf_string(buffer),ch);
    	free_buf(buffer);    	
    	return;
    }

  if (!str_prefix(arg,"snoop")) /* this part by jerome */
    {
        char bufsnoop [100];

        if(ch->level < MAX_LEVEL )
          {
            send_to_char("You can't use this check option.\n\r",ch);
            return;
          }
        buffer = new_buf();

        for (victim = char_list; victim != NULL; victim = victim->next)
        {
            if (IS_NPC(victim)
             || victim->desc->connected != CON_PLAYING
             || !can_see(ch,victim)
             || get_trust(victim) > get_trust(ch) )
                continue;

            if(victim->desc->snoop_by != NULL)
              sprintf(bufsnoop," %15s .",victim->desc->snoop_by->character->name);
            else
              sprintf(bufsnoop,"     (none)      ." );

            sprintf(buf,"%3d %15s : %s \n\r",count,victim->name, bufsnoop);
            add_buf(buffer, buf);
            count++;
        }
        page_to_char(buf_string(buffer),ch);
        free_buf(buffer);
        return;
    }

        
    send_to_char("Syntax: 'check'       display info about players\n\r",ch);
    send_to_char("        'check stats' display info and resume stats\n\r",ch);
    send_to_char("        'check eq'    resume eq of all players\n\r",ch);
    send_to_char("Use the stat command in case of doubt about someone...\n\r",ch);
    return;
}
