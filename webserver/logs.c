
#include "iserver.h"

char *get_realtime(void){
    char ptr[MAX_PATH];
	char *p = &ptr;
	time_t     t;
	struct tm *m;
	
	t = time(NULL);
	m = localtime(&t);
	
	sprintf(p, "%02d-%02d-%02d %02d-%02d-%02d-%04d", 
		   m->tm_hour, m->tm_min, m->tm_sec, 
		   m->tm_wday, m->tm_mday , m->tm_mon+1 , m->tm_year+1900 );
		   
	if(p[strlen(p)-1] == '\n')
	   p[strlen(p)-1] = '\0';
	
	return p;
}



uint32_t clogs(iserver_config *s){
	printf("%s : %x \n", __FUNCTION__, s);
}

uint32_t caccess(iserver_config *s)
{
	printf("%s : %x \n", __FUNCTION__, s);
}


uint32_t ulogs_access(zlogs_data *s)
{
	printf("%s %s %s %s\n", s->ipaddr,  s->fulldate, s->request, s->logs );
	return 0;
}