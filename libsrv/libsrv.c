
#include "libsrv.h"




unsigned int          nof=0;

char                  szServiceName[MAX_PATH];
SERVICE_STATUS        ServStatus ;
SERVICE_STATUS_HANDLE ServStatusHandle;
HANDLE                stopServEvent;



void WINAPI ServiceControlHandler(DWORD controlCode)
{
    switch ( controlCode )
    {
        case SERVICE_CONTROL_INTERROGATE:
            break;

        case SERVICE_CONTROL_SHUTDOWN:
        case SERVICE_CONTROL_STOP:

            TerminateProcess(GetCurrentProcess(), 
               GetExitCodeProcess(GetCurrentProcess(),0));
            ExitProcess(GetExitCodeProcess(GetCurrentProcess(),0));
            
            ServStatus.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus( ServStatusHandle, &ServStatus );
   
            SetEvent( stopServEvent );
                      
            exit(-1);
            
            //exit(-1);
            
            return;

        case SERVICE_CONTROL_PAUSE:
            break;

        case SERVICE_CONTROL_CONTINUE:
            break;

        default:
            if ( controlCode >= 128 && controlCode <= 255 )
                // user defined control code
                break;
            else
                // unrecognised control code
                break;
    }
    SetServiceStatus( ServStatusHandle, &ServStatus );  
}
void  WINAPI ServiceMain(DWORD argc,TCHAR* argv[])
{
    ServStatus.dwServiceType = SERVICE_WIN32;
    ServStatus.dwCurrentState = SERVICE_STOPPED ;
    ServStatus.dwControlsAccepted = 0;
    ServStatus.dwWin32ExitCode = NO_ERROR;
    ServStatus.dwServiceSpecificExitCode = NO_ERROR;
    ServStatus.dwCheckPoint = 0;
    ServStatus.dwWaitHint = 0;

    ServStatusHandle = RegisterServiceCtrlHandler( szServiceName, 
                                          ServiceControlHandler );

    if ( ServStatusHandle )
    {
        ServStatus.dwCurrentState = SERVICE_START_PENDING;
        SetServiceStatus( ServStatusHandle, &ServStatus );

        stopServEvent = CreateEvent( 0, FALSE, FALSE, 0 );

        ServStatus.dwControlsAccepted |=  (SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
        ServStatus.dwCurrentState = SERVICE_RUNNING  ;
        SetServiceStatus(ServStatusHandle, &ServStatus );

        WaitForSingleObject( stopServEvent, INFINITE ); 

        ServStatus.dwCurrentState = SERVICE_STOP_PENDING ;
        SetServiceStatus( ServStatusHandle, &ServStatus );

        CloseHandle( stopServEvent );
        stopServEvent = 0;

        ServStatus.dwControlsAccepted &= ~(SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
        ServStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus( ServStatusHandle, &ServStatus );
        
    } 
}


/////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI SRV_cvcinit( const char* lpServ) 
{
   szServiceName[0] = '\0';
   strcpy(szServiceName,lpServ);
   if(!nof) ++nof;
   return strlen(szServiceName);         
}
DWORD WINAPI SRV_cinstall( const char* displyname,
                                   const char* description,
                                   const char* commandline,
								   unsigned int nflage) 
{
	DWORD nProg;
	
	switch(nflage){
	  case 1: nProg = SERVICE_DEMAND_START; break;
	  default:
	     nProg = SERVICE_AUTO_START;
	  break;
   };
   
    if(!nof) return S_FALSE; 
    SC_HANDLE hSCM,hServ;
    char szkey[] = "SYSTEM\\CurrentControlSet\\Services\\";
    char szmodule[MAX_PATH],hfile[MAX_PATH],lpbuf[MAX_PATH];
    HKEY hKey;
    char *buffer;
    lstrcat(szkey,szServiceName);
    //GetModuleFileNameA(NULL,hfile,sizeof(hfile));
    //lstrcat(hfile,arg);
    hSCM = OpenSCManagerA(0,0,SC_MANAGER_CREATE_SERVICE);
    if(hSCM)
    {
        hServ = CreateServiceA(hSCM,szServiceName,displyname ,
                 SERVICE_ALL_ACCESS,SERVICE_WIN32_OWN_PROCESS,
                 nProg ,SERVICE_ERROR_NORMAL,
                 commandline,0,0,0,0,0);
        if(hServ){

          if(RegCreateKeyA(HKEY_LOCAL_MACHINE,szkey,&hKey)) return 103;
          if(RegSetValueExA(hKey,"Description",0,REG_SZ,
                  (BYTE*)(LPSTR)description,strlen(description))) return 104;
          RegCloseKey(hKey); //"Tcpip Tcpip6"
          CloseServiceHandle(hServ);
          return S_OK;
        }
        CloseServiceHandle(hSCM);
        return 102; 
    }
    return 101;         
} 
DWORD WINAPI SRV_cunstall( void) 
{
	if(!nof) return S_FALSE;
    SC_HANDLE hSCM,hServ;
    //SERVICE_STATUS ServStatus;
    hSCM = OpenSCManagerA(0,0,SC_MANAGER_CONNECT);  
    if(hSCM){
       hServ = OpenServiceA(hSCM,szServiceName,SERVICE_QUERY_STATUS | DELETE);
       if(hServ){
          if(QueryServiceStatus(hServ,&ServStatus)){
            if(ServStatus.dwCurrentState == SERVICE_STOPPED){
               DeleteService(hServ);
               return S_OK; 
            }else{
               SRV_cstop();
               DeleteService(hServ);
               return S_OK;
            }
          }
       }
       CloseServiceHandle(hSCM);
       return 202;
    }
    return 201;                      
}

DWORD WINAPI SRV_cstart( void) 
{
	if(!nof) return S_FALSE;
    SC_HANDLE hSCM,hServ;     
    //SERVICE_STATUS ServStatus;
    hSCM = OpenSCManagerA(0,0,SC_MANAGER_CONNECT);
    if(hSCM){
       hServ = OpenServiceA(hSCM,szServiceName,SERVICE_ALL_ACCESS);
       if(hServ){ 
          if(!StartServiceA(hServ, 0,NULL)){
              return 301;
          }
       }
       CloseServiceHandle(hSCM);
    }
    return S_OK;     
}
DWORD WINAPI SRV_cstop( void) 
{
	if(!nof) return S_FALSE;
    SC_HANDLE hSCM,hServ;     
    //SERVICE_STATUS ServStatus;
    hSCM = OpenSCManagerA(0,0,SC_MANAGER_CONNECT);
    if(hSCM){
       hServ = OpenServiceA(hSCM,szServiceName,SERVICE_ALL_ACCESS);
       if(hServ){ 
          ServStatus.dwCurrentState = SERVICE_STOPPED;
          ServStatus.dwControlsAccepted = SERVICE_CONTROL_STOP;
          if(!ControlService(hServ,SERVICE_ACCEPT_STOP,&ServStatus))
          {
              return 401;
          }
       }
       CloseServiceHandle(hSCM);
    }
    return S_OK;
}
DWORD WINAPI SRV_crun( void) 
{
   if(!nof) return S_FALSE;
   SERVICE_TABLE_ENTRY serviceTable[] ={ {szServiceName,ServiceMain},{0,0} };
   if(!StartServiceCtrlDispatcher( serviceTable )) return 1;
   return S_OK;      
}
DWORD WINAPI SRV_cstatus( DWORD *status)
{
	if(!nof) return S_FALSE;
    SC_HANDLE hSCM,hServ;
    //SERVICE_STATUS ServStatus;
    hSCM = OpenSCManagerA(0,0,SC_MANAGER_CONNECT);  
    if(hSCM){
       hServ = OpenServiceA(hSCM,szServiceName,SERVICE_QUERY_STATUS );
       if(hServ){   
          if(QueryServiceStatus(hServ,&ServStatus)){
             *status = ServStatus.dwCurrentState;
          }
       }else{
           return 601;
       }
      CloseServiceHandle(hSCM);
    }
    return S_OK;           
}
