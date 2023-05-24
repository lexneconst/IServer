#include "libar.h"

char logs_fatal[MAX_PATH];

void fatal_init(void)
{
	memset(logs_fatal,0,sizeof(logs_fatal));
}
void fatal_fini(void)
{
	
}


void fatal(char *str, const char *file,const char *func, unsigned long line)
{
	sprintf(logs_fatal,"%s,%d\0", str, line);
     printf("%s! %s %s,%s %d \n", __FUNCTION__, str, file, func, line);
}

char    *get_fatal(void)
{
	char  str[MAX_PATH]; 
    char *logs_ptr = (char *) &str;
	if(logs_ptr != NULL){
		strcpy(logs_ptr, logs_fatal);
	}	
    return logs_ptr;
}