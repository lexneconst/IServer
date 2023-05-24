
#ifndef __LIBAR_H
#define __LIBAR_H

#include <iserverx.h>

#if CBUILDING_DLL
#define DLLRUN __declspec(dllexport)
#else
#define DLLRUN __declspec(dllimport)
#endif


DLLRUN void fatal_fini(void);
DLLRUN void fatal_init(void);
DLLRUN char *get_fatal(void);
DLLRUN void fatal(char *str, const char *file,const char *func, unsigned long line);

DLLRUN char *_newadd_str(const char *str, const char *pad);
DLLRUN char *_new_str(const char *zstr);
DLLRUN char *_new_str1(const char *zstr, uint32_t length);

DLLRUN uint32_t einit(void *s);
DLLRUN uint32_t efini(void *s);
DLLRUN void *emalloc(uint32_t  length);
DLLRUN void efree(void *ptr);

DLLRUN uint32_t cstring_create(cstring_t** ptr);
DLLRUN uint32_t cstring_clean(cstring_t** ptr);
DLLRUN uint32_t cstring_clone(cstring_t** ptr, cstring_t *str);
DLLRUN uint32_t cstring_check(cstring_t **ptr);
DLLRUN char* cstring_str(cstring_t *ptr);
DLLRUN uint32_t cstring_len(cstring_t *ptr);
DLLRUN uint32_t cstring_newadd(cstring_t **ptr, cstring_t *dst , cstring_t *src);
DLLRUN uint32_t cstring_new(cstring_t **ptr, const char *buf);
DLLRUN uint32_t cstring_newpad(cstring_t **ptr, const char *buf,const char *pad);
DLLRUN uint32_t cstring_renew(cstring_t **ptr, const char *buf);
DLLRUN uint32_t cstring_stat(cstring_t **ptr, const char v);
DLLRUN uint32_t cstring_remove(cstring_t **ptr, uint32_t len);
DLLRUN uint32_t cstring_clear(cstring_t **ptr);

DLLRUN char * getmoduledir(void);

#endif
