/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: file types a resource manager serves. */
#ifndef _NBT_QNX_SYS_FTYPE_H
#define _NBT_QNX_SYS_FTYPE_H

enum _file_type {
	_FTYPE_MATCHED = -1,
	_FTYPE_ALL = -1,
	_FTYPE_ANY = 0,
	_FTYPE_FILE,
	_FTYPE_LINK,
	_FTYPE_SYMLINK,
	_FTYPE_PIPE,
	_FTYPE_SHMEM,
	_FTYPE_MQUEUE,
	_FTYPE_SOCKET,
	_FTYPE_SEM,
	_FTYPE_PHOTON,
	_FTYPE_DUMPER,
	_FTYPE_MOUNT,
	_FTYPE_NAME,
	_FTYPE_TYMEM
};

#endif
