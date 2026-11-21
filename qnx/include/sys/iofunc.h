/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the default handlers of a resource manager
 * and the attributes of what it serves. */
#ifndef _NBT_QNX_SYS_IOFUNC_H
#define _NBT_QNX_SYS_IOFUNC_H

#include <sys/resmgr.h>
#include <sys/stat.h>

#ifndef IOFUNC_MOUNT_T
#define IOFUNC_MOUNT_T struct _iofunc_mount
#endif
struct _iofunc_mmap_list;
struct _iofunc_lock_list;
struct _client_info;

typedef struct _iofunc_attr {
	IOFUNC_MOUNT_T *mount;
	_Uint32t flags;
	_Int32t lock_tid;
	_Uint16t lock_count;
	_Uint16t count;
	_Uint16t rcount;
	_Uint16t wcount;
	_Uint16t rlocks;
	_Uint16t wlocks;
	struct _iofunc_mmap_list *mmap_list;
	struct _iofunc_lock_list *lock_list;
	void *lockobj;
	_Uint32t reserved;
	off64_t nbytes;
	ino64_t inode;
	uid_t uid;
	gid_t gid;
	time_t mtime;
	time_t atime;
	time_t ctime;
	mode_t mode;
	nlink_t nlink;
	dev_t rdev;
} iofunc_attr_t;

__BEGIN_DECLS
void iofunc_func_init(unsigned __nconnect, resmgr_connect_funcs_t *__connect, unsigned __nio,
		      resmgr_io_funcs_t *__io);
void iofunc_attr_init(iofunc_attr_t *__attr, mode_t __mode, iofunc_attr_t *__dattr, struct _client_info *__info);
__END_DECLS

#endif
