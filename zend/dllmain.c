/* Replace "dll.h" with the name of your header */
#include "libzendw.h"

const char *get_path_sid_key(const char *pathname, size_t pathname_len, size_t *key_len)
{/*{{{*/
	PSID pSid = 0;

	if (!pSid) {
		*key_len = pathname_len;
		return pathname;
	}

}/*}}}*/


BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
