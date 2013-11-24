#ifndef CONVERT
#define CONVERT

#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#include"str.h"

enum state_tag{
	BIBKEY=0,
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
extern bool IsSingleAuthor(FILE* fp);
#endif
