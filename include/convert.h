#ifndef CONVERT
#define CONVERT

#include"str.h"

enum state_tag{
	BIBKEY,
	AUTHOR,
	JOURNAL,
	YEAR,
};

enum op_tag{
	BEGIN=0,
	CONTINUE,
	END,
};


extern char *extract_bibkey(const char *s);
#endif
