

#include "iserver.h"

iserver_module module = 
{
        ISERVER_VERSION,
        ISERVER_NAME,
        ISERVER_OS,
        cstartup,
        ccleanup,
        cbuild,
        
        cmodule,
        cread,
        cwrite,
        cdone,
        ctimem,
        cipaddr,
        
        tread,
        twrite,
        
        clogs,
        caccess
};

iserver_config     config;
zconfig_server_t   *server;

unsigned __stdcall threadproc(void *s)
{
         //printf("> %s \n", __FUNCTION__);
         uint32_t  ret= 1;
		 config.argv = s;
    do{

         module.cstartup(&config);
         ret = module.cbuild(&config);
         if(!ret) break;
         while(ret){
              ret = module.cmodule(&module, &config);
              //if(!ret) break;             
         }
    }while(0);
    
         module.ccleanup(&config);
}

int bio_sign = 0;

int main(int argc, char *argv[])
{
  unsigned ret;
  char   *ptr=NULL;
  char   *szfile=NULL;
  char   lpszcmd[MAX_PATH];
  
  szfile = getmoduledir();
  //
  //printf("DIR> %s \n", szfile);
  //GetModuleFileNameA(NULL, szfile, sizeof(szfile));
  //printf("DIR> %s \n", szfile);
  #ifndef DEBUG_H
  if((ptr=strrchr(szfile, '\\' ))!=NULL) 
  { 	
  	 *ptr =0;
  	 ptr= NULL;    
  }
  #endif
	  
  if(argc > 1){
     if(strcmp(argv[1],"http")==0){
          printf("HTTP(80) Protocol\n");
          bio_sign=0; 
     }else
     if(strcmp(argv[1],"https")==0){
          printf("HTTPS(443) Protocol\n");
          bio_sign=1;
          
     }else
     if(strcmp(argv[1], "-k") ==0){
     	printf("'%s' Service is ", ISERVER_NAME);
     	GetModuleFileName(NULL, lpszcmd, sizeof(lpszcmd));
     	if(strcmp(argv[2], "http")==0){
     		strcat(lpszcmd, " -k http run");
     		SRV_cvcinit("iserverhttp");
     		if(strcmp(argv[3], "install") == 0){
     			printf("Install");
     			SRV_cinstall("iserver", "webserver ", lpszcmd, 0);
			}else
			if(strcmp(argv[3], "unstall")== 0){
				printf("Unstall");
				SRV_cunstall();
			}else
			if(strcmp(argv[3], "start")==0){
				printf("Start");
				SRV_cstart();
			}else
			if(strcmp(argv[3], "stop") ==0){
				printf("Stop");
				SRV_cstop();
			}else{
				SRV_crun();
			}
     		printf("\n");
		}else
		if(strcmp(argv[2], "https")==0){
			strcat(lpszcmd, " -k https run");
			SRV_cvcinit("iserverhttps");
			if(strcmp(argv[3], "install") == 0){
     			SRV_cinstall("iserver", "webserver ", lpszcmd, 0);
			}else
			if(strcmp(argv[3], "unstall")== 0){
			    SRV_cunstall();
			}else
			if(strcmp(argv[3], "start")==0){
				SRV_cstart();
			}else
			if(strcmp(argv[3], "stop") ==0){
				SRV_cstop();
			}else{
				SRV_crun();
			}
		}
     	
	 }
     
  }else{
  	  
      bio_sign=0; 
  } 
  
  #ifdef DEBUG_H
  printf("FILE:%s\n", szfile);
  #endif
  
  _beginthreadex(NULL,0, threadproc, szfile,0, &ret);
  
  
  
  while(1){
           sleep(100);
  }	
  return 0;
}


