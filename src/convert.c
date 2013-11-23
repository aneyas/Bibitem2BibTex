// This is the main file.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#include"convert.h"

//No bibitem entry should be longer than 1024 char.
static char info[1024];


int
main(){
	//Open the file to read.
	FILE *fp;
	fp = fopen("BZT_for_NC_bibitem.txt", "r");
	//fp = fopen("test.txt", "r");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	//Read char*
	char* s = info;
	enum state_tag current_state, next_state;
	int scanf_state;
	
	current_state = BEGIN;


/*
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
*/

	char* bibkey=""; //Initialize the string.
	char* authors="";
	bool isSingleAuthtor=true;
	char* journal="";
	char* year ="";

//s = "D.";
//authors = Str_catv(authors,1,0,s,1,0," ",1,2,NULL);
//printf("%s\n",authors);

//exit(0);


	while(EOF!=fscanf(fp, "%s", s)){

		next_state = state_change(current_state,s);

		//printf("%d, %d, %s\n", current_state, next_state,s);

		switch(next_state){
			case BIBKEY_END:
				printf("%s\n", "----------------");
				//bibkey = extract_bibkey(s);
				printf("%s\n",s);
				break;
			case SINGLE_AUTHOR:
				printf("%s\n", authors);
				authors = "";
				break;
			case AUTHOR:
				authors = Str_catv(authors,1,0,s,1,0," ",1,2,NULL);
				break;
			case LAST_AUTHOR:
				authors = Str_catv(authors,1,0,s,1,0," ",1,2,NULL);
				break;
			case AUTHOR_END:
				authors = Str_catv(authors,1,0,s,1,0," ",1,2,NULL);
				printf("%s\n", authors);
				authors = "";
				break;
			case JOURNAL_NAME:
				journal = Str_catv(journal,1,0,s,1,0," ",1,2,NULL);
				break;
			case PAGE_NUMBER:
				journal = Str_catv(journal,1,0,s,1,0," ",1,2,NULL);
				break;
			case PAGE_NUMBER_END:
				journal = Str_catv(journal,1,0,s,1,0," ",1,2,NULL);
				printf("%s\n", journal);
				journal = "";
				break;
			case YEAR:
				year = Str_catv(year,1,0,s,1,0," ",1,2,NULL);
				printf("%s\n", year);
				year ="";
				
				break;
			default:			
				break;
		}
		current_state = next_state;

	}


	//Last phase of the program.
	fclose(fp);
	return 0;
}
