

#ifndef LIBCSP_H
#define LIBCSP_H

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include <iserverx.h>

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

DLLIMPORT void *csp_module_startup( sapi_server *req, zrequest_externs_t *ext );
DLLIMPORT void *csp_module_execute( sapi_server *req);
DLLIMPORT void *csp_module_cleanup( sapi_server *req);

#endif

