#include "libzendw.h"


int lsp_module_startup(sapi_module_struct *sf, 
zend_module_entry *additional_modules, 
ZEND_API uint32_t num_additional_modules)
{
	return 0;
}

int lsp_module_shutdown(void)
{
	return 0;
}

int php_execute_script(zend_file_handle *primary_file)
{
	return 0;
}