#ifndef CONVERT
#define CONVERT

#include"str.h"

enum state_tag{
	BEGIN = 0,
	NEW_BIBITEM,
	BIBKEY_END,
	BLOCK_BREAK,
	AUTHOR,
	LAST_AUTHOR,
	AUTHOR_END,
	JOURNAL_NAME,
	PAGE_NUMBER,
	PAGE_NUMBER_END,
	YEAR,
};


extern enum state_tag state_change(enum state_tag current_state, const char* s);
extern char *extract_bibkey(const char *s);
#endif
