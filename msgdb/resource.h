#ifndef _RESOURCE_H_
#define _RESOURCE_H_

/*
 * $Id: resource.h,v 1.97 1999/01/18 05:16:33 fjoe Exp $
 */

#define msg(msgid, ch) vmsg(msgid, ch, ch)
const char *	vmsg		(int msgid, CHAR_DATA *ch, CHAR_DATA *victim);
void		msgdb_load	(void);

enum {
	MSG_YOU_TOO_EXHAUSTED,
	MSG_YOU_CANT_WAKE_M,
	MSG_ARRIVED,
	MSG_ARRIVED_RIDING,
	MSG_THANK_YOU_BRAVE,
	MSG_HAVE_BECOME_BETTER,
	MSG_LEARN_FROM_MISTAKES,
	MSG_WHEN_YOU_ATTEMPT_YOU_BREAK_WEBS,
	MSG_N_BREAKS_THE_WEBS,
	MSG_YOU_ATTEMPT_WEBS_HOLD_YOU,
	MSG_YOU_STEP_OUT_SHADOWS,
	MSG_N_STEPS_OUT_OF_SHADOWS,
	MSG_YOU_STEP_OUT_COVER,
	MSG_N_STEPS_OUT_COVER,
	MSG_YOU_FAILED_TO_PASS,
	MSG_N_TRIES_TO_PASS_FAILED,
	MSG_TOO_PUMPED_TO_PRAY,
	MSG_YOU_SUCCESSED_TO_OPEN_DOOR,
	MSG_YOU_FALL_ON_FACE,
	MSG_N_FALLS_ON_FACE,
	MSG_N_THROWS_GLOBE,
	MSG_N_IS_GONE,
	MSG_N_APPEARS_FROM_NOWHERE,
	MSG_YOU_TOUCH_NS_NECK,
	MSG_N_TOUCHES_NS_NECK,
	MSG_YOU_RAISE_A_LEVEL,
	MSG_BRAVE_BUT_LET_SOMEONE_ELSE,
	MSG_HAS_MURDERED,
	MSG_THE_PENALTY_IS,
	MSG_NOT_ENOUGH_QP,
	MSG_NO_DEATHS,
	MSG_N_GIVES_YOU_GOLD,
	MSG_NEVER_QUEST,
	MSG_HAVENT_COMPLETE,
	MSG_DIDNT_COMPLETE_IN_TIME,
	MSG_YOU_COMPLETED_SOMEONES_QUEST,
	MSG_ALMOST_COMPLETE_QUEST,
	MSG_PUSH_VICT_WEBBED,
	MSG_N_PUSHES_VICT_WEBBED,
	MSG_N_TRIED_PUSH_YOU,
	MSG_N_TRIED_PUSH_N,
	MSG_YOU_SETTLE_DOWN,
	MSG_CANT_PRAY_NOW,
	MSG_ESCAPE_FAILED,
	MSG_N_ESCAPED,
	MSG_YOU_ESCAPED_FROM_COMBAT,
	MSG_YOU_FLED_FROM_COMBAT,
	MSG_FAIL_TO_MOUNT,
	MSG_YOU_FALL_OFF_N,
	MSG_N_FALLS_OFF_N,
	MSG_N_FALLS_OFF_YOU,
	MSG_N_SNARLS_YOU,
	MSG_N_SNARLS_N,
	MSG_YOU_SNARL_N,
	MSG_IS_DEAD,
	MSG_IS_LYING_HERE_STUNNED,
	MSG_N_LOOKS_AT_SELF,
	MSG_N_LOOKS_AT_YOU,
	MSG_N_LOOKS_AT_N,
	MSG_SEE_NOTHING_SPECIAL,
	MSG_HAVE_KILLED,
	MSG_MUST_PROVIDE_NAME,
	MSG_ILLEGAL_CHARACTER_TITLE,
	MSG_TOO_RELAXED,
	MSG_BETTER_STANDUP,
	MSG_YOU_ZAPPED_BY_P,
	MSG_N_ZAPPED_BY_P,
	MSG_DONT_BE_SO_GREEDY,
	MSG_N_WANDERS_ON_HOME,
	MSG_N_SHIVERS_ILL,
	MSG_N_TRIES_TO_USE,
	MSG_N_SACS_SELF,
	MSG_MISPRONOUNCE_SYLLABLE,
	MSG_YOUR_THIRST_QUENCHED,
};

#endif
