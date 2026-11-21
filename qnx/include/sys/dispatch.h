/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the dispatch layer (blocking for and
 * handling messages) and names attached under /dev/name. */
#ifndef _NBT_QNX_SYS_DISPATCH_H
#define _NBT_QNX_SYS_DISPATCH_H

#include <sys/resmgr.h>
#include <sys/ftype.h>

typedef union _dispatch_context dispatch_context_t;

typedef struct _name_attach {
	dispatch_t *dpp;
	int chid;
	int mntid;
	int zero[2];
} name_attach_t;

#define NAME_FLAG_ATTACH_GLOBAL 0x00000002
#define NAME_FLAG_DETACH_SAVEDPP 0x00000001
#define DISPATCH_FLAG_NOLOCK 0x00000001

__BEGIN_DECLS
dispatch_t *dispatch_create(void);
dispatch_t *dispatch_create_channel(int __chid, unsigned __reserved);
int dispatch_destroy(dispatch_t *__dpp);
dispatch_context_t *dispatch_context_alloc(dispatch_t *__dpp);
void dispatch_context_free(dispatch_context_t *__ctp);
dispatch_context_t *dispatch_block(dispatch_context_t *__ctp);
void dispatch_unblock(dispatch_context_t *__ctp);
int dispatch_handler(dispatch_context_t *__ctp);
int dispatch_timeout(dispatch_t *__dpp, struct timespec *__reltime);
name_attach_t *name_attach(dispatch_t *__dpp, const char *__path, unsigned __flags);
int name_detach(name_attach_t *__attach, unsigned __flags);
int name_open(const char *__name, int __flags);
int name_close(int __fd);
__END_DECLS

#endif
