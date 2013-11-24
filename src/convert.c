// This is the main file.

#include"convert.h"

//No bibitem entry should be longer than 1024 char.
static char s[1024];


int
main(){
	//Open the file to read.
	FILE *fp;
	//fp = fopen("BZT_for_NC_bibitem.txt", "r");
	fp = fopen("BZT_for_NC_bibitem_NO_book.txt", "r");
	//fp = fopen("test.txt", "r");

	if( fp == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	enum state_tag current_state, next_state;
	enum op_tag current_op, next_op;

	current_op = BEGIN;
	current_state = BIBKEY;

    char* info="";


    struct raw_record_tag raw_records[400];
    struct bibtex_record_tag bibtex_records[400];
    int count = 0;

	while(EOF!=fscanf(fp, "%s", s)){
        //printf("@-- %d %d %s | %s\n", current_op,current_state, info, s);

		switch (current_op){
			case BEGIN:
				switch (current_state){
					case BIBKEY:
						info = Str_catv(info,1,0," ",1,2,s,1,0,NULL);
						//printf("%s\n", info);
                        raw_records[count].bibkey = Str_dup(info,1,0,1);
						info = "";
						if(IsSingleAuthor(fp)){
							current_op = END;
							current_state = AUTHOR;
						}else{
							current_op = CONTINUE;
							current_state = AUTHOR;
						}
						break;
					default:
						current_op = CONTINUE;
						break;
				}
				break;
			case END:
				info = Str_catv(info,1,0," ",1,2,s,1,0,NULL);
				switch (current_state){
					case YEAR:
						//printf("%s\n", info);
                        raw_records[count].year = Str_dup(info,1,0,1);
                        ++count;
						info="";
						//printf("%s\n", "-----------");
						current_op = BEGIN;
						current_state = BIBKEY;
						break;
					case AUTHOR:
						if((strlen(s) >= 1 && !Str_cmp(s,-1,0,",",1,2))){
							//printf("%s\n", info);
                            raw_records[count].authors = Str_dup(info,1,0,1);
							info="";
							current_op = CONTINUE;
							current_state = JOURNAL;
						}else{
							current_op = END;
							current_state = AUTHOR;
						}
						break;
					case JOURNAL:
						//printf("%s\n", info);
                        raw_records[count].journal= Str_dup(info,1,0,1);
						info="";
						current_op = END;
						current_state = YEAR;
						break;
					case BIBKEY:
						printf("%s\n", "Cannot be here (C). Somthing is wrong!");
						exit(1);
				}
				break;
			case CONTINUE:
				info = Str_catv(info,1,0," ",1,2,s,1,0,NULL);
				switch (current_state){
					case YEAR:
						printf("%s\n", "Cannot be here (A). Somthing is wrong!");
						exit(1);
					case BIBKEY:
						printf("%s\n", "Cannot be here (B). Somthing is wrong!");
						exit(1);
					case AUTHOR:
						if (strlen(s) >= 3 && Str_find(s,1,4,"and")){
							current_op = END;
							current_state = AUTHOR;
						}else{
							current_op = CONTINUE;
							current_state = AUTHOR;
						}
						break;
					case JOURNAL:
						if((strlen(s) >= 1 && !Str_cmp(s,-1,0,",",1,2))){ //Volume
							current_op = END;
							current_state = JOURNAL;
						}else{
							current_op = CONTINUE;
							current_state = JOURNAL;
						}
						break;

				}
				break;
		}
	}

	//Last phase of the program.
	fclose(fp);

    //Change to the fine format.
   raw_records_process(raw_records,bibtex_records,count);
   //Print.
   bibtex_records_print(bibtex_records,count);

	return 0;
}
