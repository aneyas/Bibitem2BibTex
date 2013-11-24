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


struct raw_record_tag{
    char* bibkey;
    char* authors;
    char* journal;
    char* year;
};

struct bibtex_record_tag{
    char* bibkey;
    char* authors;
    char* jour_name;
    char* jour_vol;
    char* jour_page;
    char* year;
};

extern void raw_records_process(struct raw_record_tag records[],struct bibtex_record_tag arecords[],int count);
extern void bibtex_records_print(struct bibtex_record_tag bibtex_records[], int count);
#endif
