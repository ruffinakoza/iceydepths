/*-
 * Copyright (c) 1998 fjoe <fjoe@iclub.nsu.ru>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: hometown.c,v 1.7 1998/12/09 11:57:51 fjoe Exp $
 */

#include <sys/time.h>
#include <stdio.h>

#include "merc.h"
#include "hometown.h"

static char* restrict_none(CHAR_DATA*);
static char* restrict_ofcol(CHAR_DATA*);
static char* restrict_old_midgaard(CHAR_DATA*);

/*	altar	(good, neut, evil)
	recall	(good, neut, evil)
	pit	(good, neut, evil) */
struct hometown_data hometown_table[] = {
	{
		"Midgaard",
		restrict_none,
		{ 3070, 3054, 3072 },
		{ 3068, 3001, 3071 },
		{ 3010, 3010, 3010 }
	},
	{
		"New Thalos",
		restrict_none,
		{ 9605, 9605, 9605 },
		{ 9609, 9609, 9609 },
		{ 3010, 3010, 3010 }
	},
	{
		"Valley of the Titans",
		restrict_none,
		{ 18127, 18127, 18127 },
		{ 18126, 18126, 18126 },
		{ 18101, 18101, 18101 }
	},
	{
		"New Ofcol",
		restrict_ofcol,
		{ 669, 669, 669 },
		{ 698, 698, 698 },
		{ 670, 670, 670 }
	},
	{
		"Old Midgaard",
		restrict_old_midgaard,
		{ 5386, 5386, 5386 },
		{ 5379, 5379, 5379 },
		{ 3010, 3010, 3010 }
	}, 
	{ NULL }
};

int get_recall(CHAR_DATA *ch)
{
	int point;

	if (IS_GOOD(ch)) 
		point = hometown_table[ch->hometown].recall[0];
	else if (IS_EVIL(ch))
		point = hometown_table[ch->hometown].recall[2];
	else
		point = hometown_table[ch->hometown].recall[1];

	return point;
}

static char*
restrict_none(CHAR_DATA* ch)
{
	return NULL;
}

static char*
restrict_ofcol(CHAR_DATA* ch)
{
	if (!IS_NEUTRAL(ch))
		return "Only neutral people can live in Ofcol";
	return NULL;
}

static char*
restrict_old_midgaard(CHAR_DATA* ch)
{
	if (ch->class == CLASS_VAMPIRE || ch->class == CLASS_NECROMANCER)
		return NULL;
	return "Only vampires and necromancers live there";
}

