
#include "libar.h"

char * getmoduledir(void)
{
	char *ptr=NULL;
	char *file=NULL;
	uint32_t length = 256;
do{	
	file = (char *) emalloc( length);
	if(file==NULL){
	   fatal("allocate memory", __FILE__, __FUNCTION__, __LINE__);
	   break;
	}
	//getcwd(szfile, sizeof(szfile) );
	GetModuleFileName(NULL, file, length);
	
	if((ptr=strrchr(file, '\\' ))!=NULL) 
  	 { 	
  	    *ptr =0;
  	    ptr= NULL;
		
		length = strlen(file);
	}else
	if((ptr=strrchr(file, '/'))!=NULL){
	    *ptr=0;
		ptr=NULL;
		
		length = strlen(file);
	}
	   
	file[length] = '\0';
	
}while(0);
	return file;
}
