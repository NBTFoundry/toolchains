/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: resource managers (a process serving a
 * path name). The message types are only declared: handlers receive them by
 * pointer. */
#ifndef _NBT_QNX_SYS_RESMGR_H
#define _NBT_QNX_SYS_RESMGR_H

#include <sys/neutrino.h>
#include <pthread.h>

typedef struct _dispatch dispatch_t;
typedef struct _pulse io_pulse_t;
typedef union _resmgr_iomsgs resmgr_iomsgs_t;

typedef struct _io_open io_open_t;
typedef struct _io_unlink io_unlink_t;
typedef struct _io_rename io_rename_t;
typedef union _io_rename_extra io_rename_extra_t;
typedef struct _io_mknod io_mknod_t;
typedef struct _io_readlink io_readlink_t;
typedef struct _io_link io_link_t;
typedef union _io_link_extra io_link_extra_t;
typedef struct _io_mount io_mount_t;
typedef struct _io_mount_extra io_mount_extra_t;
typedef struct _io_close io_close_t;
typedef struct _io_write io_write_t;
typedef struct _io_read io_read_t;
typedef struct _io_stat io_stat_t;
typedef struct _io_notify io_notify_t;
typedef struct _io_devctl io_devctl_t;
typedef struct _io_pathconf io_pathconf_t;
typedef struct _io_lseek io_lseek_t;
typedef struct _io_chmod io_chmod_t;
typedef struct _io_chown io_chown_t;
typedef struct _io_utime io_utime_t;
typedef struct _io_openfd io_openfd_t;
typedef struct _io_fdinfo io_fdinfo_t;
typedef struct _io_lock io_lock_t;
typedef struct _io_space io_space_t;
typedef struct _io_shutdown io_shutdown_t;
typedef struct _io_msg io_msg_t;
typedef struct _io_mmap io_mmap_t;
typedef struct _io_dup io_dup_t;
typedef struct _io_sync io_sync_t;
typedef struct _io_power io_power_t;

struct _xendian_context {
	_Uint16t type;
	_Uint16t mode;
	_Uint32t hint;
};

struct _extended_context {
	size_t length;
	struct _xendian_context xendian;
};

typedef struct _resmgr_context {
	int rcvid;
	struct _msg_info info;
	resmgr_iomsgs_t *msg;
	dispatch_t *dpp;
	int id;
	struct _extended_context *extra;
	unsigned msg_max_size;
	int status;
	int offset;
	int size;
	iov_t iov[1];
} resmgr_context_t;

#ifndef RESMGR_HANDLE_T
#define RESMGR_HANDLE_T void
#endif
#ifndef RESMGR_OCB_T
#define RESMGR_OCB_T void
#endif

/* Handlers for path requests (connect messages) and for an opened file (I/O
 * messages); iofunc_func_init() fills both with the defaults. */
typedef struct _resmgr_connect_funcs {
	unsigned nfuncs;
	int (*open)(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra);
	int (*unlink)(resmgr_context_t *ctp, io_unlink_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int (*rename)(resmgr_context_t *ctp, io_rename_t *msg, RESMGR_HANDLE_T *handle, io_rename_extra_t *extra);
	int (*mknod)(resmgr_context_t *ctp, io_mknod_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int (*readlink)(resmgr_context_t *ctp, io_readlink_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int (*link)(resmgr_context_t *ctp, io_link_t *msg, RESMGR_HANDLE_T *handle, io_link_extra_t *extra);
	int (*unblock)(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int (*mount)(resmgr_context_t *ctp, io_mount_t *msg, RESMGR_HANDLE_T *handle, io_mount_extra_t *extra);
} resmgr_connect_funcs_t;
#define _RESMGR_CONNECT_NFUNCS ((sizeof(resmgr_connect_funcs_t) - sizeof(unsigned)) / sizeof(void *))

typedef struct _resmgr_io_funcs {
	unsigned nfuncs;
	int (*read)(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
	int (*write)(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);
	int (*close_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int (*stat)(resmgr_context_t *ctp, io_stat_t *msg, RESMGR_OCB_T *ocb);
	int (*notify)(resmgr_context_t *ctp, io_notify_t *msg, RESMGR_OCB_T *ocb);
	int (*devctl)(resmgr_context_t *ctp, io_devctl_t *msg, RESMGR_OCB_T *ocb);
	int (*unblock)(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_OCB_T *ocb);
	int (*pathconf)(resmgr_context_t *ctp, io_pathconf_t *msg, RESMGR_OCB_T *ocb);
	int (*lseek)(resmgr_context_t *ctp, io_lseek_t *msg, RESMGR_OCB_T *ocb);
	int (*chmod)(resmgr_context_t *ctp, io_chmod_t *msg, RESMGR_OCB_T *ocb);
	int (*chown)(resmgr_context_t *ctp, io_chown_t *msg, RESMGR_OCB_T *ocb);
	int (*utime)(resmgr_context_t *ctp, io_utime_t *msg, RESMGR_OCB_T *ocb);
	int (*openfd)(resmgr_context_t *ctp, io_openfd_t *msg, RESMGR_OCB_T *ocb);
	int (*fdinfo)(resmgr_context_t *ctp, io_fdinfo_t *msg, RESMGR_OCB_T *ocb);
	int (*lock)(resmgr_context_t *ctp, io_lock_t *msg, RESMGR_OCB_T *ocb);
	int (*space)(resmgr_context_t *ctp, io_space_t *msg, RESMGR_OCB_T *ocb);
	int (*shutdown)(resmgr_context_t *ctp, io_shutdown_t *msg, RESMGR_OCB_T *ocb);
	int (*mmap)(resmgr_context_t *ctp, io_mmap_t *msg, RESMGR_OCB_T *ocb);
	int (*msg)(resmgr_context_t *ctp, io_msg_t *msg, RESMGR_OCB_T *ocb);
	int (*reserved)(resmgr_context_t *ctp, void *msg, RESMGR_OCB_T *ocb);
	int (*dup)(resmgr_context_t *ctp, io_dup_t *msg, RESMGR_OCB_T *ocb);
	int (*close_dup)(resmgr_context_t *ctp, io_close_t *msg, RESMGR_OCB_T *ocb);
	int (*lock_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int (*unlock_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int (*sync)(resmgr_context_t *ctp, io_sync_t *msg, RESMGR_OCB_T *ocb);
	int (*power)(resmgr_context_t *ctp, io_power_t *msg, RESMGR_OCB_T *ocb);
} resmgr_io_funcs_t;
#define _RESMGR_IO_NFUNCS ((sizeof(resmgr_io_funcs_t) - sizeof(unsigned)) / sizeof(void *))

typedef struct _resmgr_attr {
	unsigned flags;
	unsigned nparts_max;
	unsigned msg_max_size;
	int (*other_func)(resmgr_context_t *ctp, void *msg);
	unsigned reserved[4];
} resmgr_attr_t;

#define _RESMGR_NOREPLY (0x80000000u)
#define _RESMGR_DEFAULT (0x80000001u)
#define _RESMGR_NPARTS(n) (-(n))
#define _RESMGR_ERRNO(e) (e)
#define _RESMGR_PTR(ctp, p, n) (SETIOV((ctp)->iov + 0, (p), (n)), _RESMGR_NPARTS(1))
#define _RESMGR_STATUS(ctp, s) ((ctp)->status = (s))

#define _RESMGR_FLAG_BEFORE 0x0001
#define _RESMGR_FLAG_AFTER 0x0002
#define _RESMGR_FLAG_OPAQUE 0x0004
#define _RESMGR_FLAG_FTYPEONLY 0x0008
#define _RESMGR_FLAG_FTYPEALL 0x0010
#define _RESMGR_FLAG_DIR 0x0100
#define _RESMGR_FLAG_SELF 0x0200
#define _RESMGR_DETACH_ALL 0x0000
#define _RESMGR_DETACH_PATHNAME 0x0001
#define _RESMGR_DETACH_CLOSE 0x8000

__BEGIN_DECLS
int resmgr_attach(dispatch_t *__dpp, resmgr_attr_t *__attr, const char *__path, int __file_type, unsigned __flags,
		  const resmgr_connect_funcs_t *__connect_funcs, const resmgr_io_funcs_t *__io_funcs,
		  RESMGR_HANDLE_T *__handle);
int resmgr_detach(dispatch_t *__dpp, int __id, unsigned __flags);
__END_DECLS

#endif
