
#ifndef LIBSRV32_H
#define LIBSRV32_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */


DLLIMPORT DWORD WINAPI SRV_cvcinit( const char* lpServ) ;
DLLIMPORT DWORD WINAPI SRV_cinstall( const char* displyname,
                                   const char* description,
                                   const char* commandline,
								   unsigned int nflage) ;
DLLIMPORT DWORD WINAPI SRV_cunstall( void);
DLLIMPORT DWORD WINAPI SRV_cstart( void) ;
DLLIMPORT DWORD WINAPI SRV_cstop( void);
DLLIMPORT DWORD WINAPI SRV_crun( void) ;
DLLIMPORT DWORD WINAPI SRV_cstatus( DWORD *status);


#endif

