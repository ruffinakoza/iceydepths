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
 * $Id: race.h,v 1.1 1998/10/30 07:02:24 fjoe Exp $
 */

#ifndef _RACE_H_
#define _RACE_H_

struct race_data
{
	const char *	name;		/* call name of the race	*/
	const char *	file_name;	/* filename			*/
	flag_t		act;		/* act bits			*/
	flag_t		aff;		/* aff bits			*/
	flag_t		off;		/* off bits			*/
	flag_t		imm;		/* imm bits			*/
	flag_t		res;		/* res bits			*/
	flag_t		vuln;		/* vuln bits			*/
	flag_t		form;		/* default form flag		*/
	flag_t		parts;		/* default body parts		*/
	RACE_PCDATA *	pcdata;		/* additional data for pc races */
};

/* additional data for pc races */
struct race_pcdata
{
	char 	who_name[6];		/* 5-letter who-name		*/
	int 	points; 		/* cost in exp of the race	*/
	varr	classes;		/* available classes		*/
	const char *	bonus_skills;	/* bonus skills for the race	*/
	varr 	skills;			/* race skills			*/
	int	stats[MAX_STATS];	/* starting stats		*/
	int	max_stats[MAX_STATS];	/* maximum stats		*/
	sflag_t	size;			/* aff bits for the race	*/
	int 	hp_bonus;		/* initial hp bonus		*/
	int 	mana_bonus;		/* initial mana bonus		*/
	int 	prac_bonus;		/* initial practice bonus	*/
	int	slang;			/* spoken language		*/
	int	restrict_align;		/* alignment restrictions	*/
	int	restrict_sex;		/* sex restrictions		*/
};

/* additional data for available classes for race */
struct race_class_data {
	const char *	name;		/* class name */
	int		mult;		/* exp multiplier */
};

struct race_skill {
	int	sn;
	int	level;
};

extern varr races;

#define RACE(i)		((RACE_DATA*) VARR_GET(&races, i))
#define race_lookup(i)	((RACE_DATA*) varr_get(&races, i))
#define race_skill_lookup(race, sn) \
	((RACE_SKILL*) varr_bsearch(&race->pcdata->skills, &sn, cmpint))
#define race_class_lookup(race, name) \
	((RACE_CLASS_DATA*) varr_bsearch(&race->pcdata->classes, &name, cmpstr))

RACE_DATA *	race_new(void);
RACE_PCDATA *	race_pcdata_new(void);
void		race_free(RACE_DATA*);
void		race_pcdata_free(RACE_PCDATA*);

const char *	race_name(int);
int		rn_lookup(const char*);

#endif
