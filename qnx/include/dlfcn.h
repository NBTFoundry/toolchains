/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: run-time loading of the car's shared
 * libraries. */
#ifndef _NBT_QNX_DLFCN_H
#define _NBT_QNX_DLFCN_H

#include <sys/cdefs.h>

typedef struct dl_info {
	const char *dli_fname;
	void *dli_fbase;
	const char *dli_sname;
	void *dli_saddr;
} Dl_info;

#define RTLD_LAZY 0x0001
#define RTLD_NOW 0x0002
#define RTLD_NOLOAD 0x0004
#define RTLD_GLOBAL 0x0100
#define RTLD_LOCAL 0x0200
#define RTLD_GROUP 0x0400
#define RTLD_WORLD 0x0800
#define RTLD_NODELETE 0x1000
#define RTLD_NOSHARE 0x2000
#define RTLD_DEFAULT ((void *)-2)
#define RTLD_NEXT ((void *)-3)

__BEGIN_DECLS
char *dlerror(void);
void *dlopen(const char *__path, int __mode);
void *dlsym(void *__restrict __handle, const char *__restrict __name);
int dladdr(void *__addr, Dl_info *__info);
int dlclose(void *__handle);
__END_DECLS

#endif
