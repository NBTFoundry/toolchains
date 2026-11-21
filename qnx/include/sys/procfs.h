/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the process file system's devctl requests
 * (on /proc/<pid>/as). */
#ifndef _NBT_QNX_SYS_PROCFS_H
#define _NBT_QNX_SYS_PROCFS_H

#include <sys/types.h>
#include <devctl.h>

#define __PROC_SUBCMD_PROCFS 0

typedef struct _procfs_debug_info {
	_Uint64t vaddr;
	char path[1];
} procfs_debuginfo;

typedef struct _procfs_map_info {
	_Uint64t vaddr;
	_Uint64t size;
	_Uint32t flags;
	dev_t dev;
	off64_t offset;
	ino64_t ino;
	_Uint64t paddr;
} procfs_mapinfo;

#define DCMD_PROC_MAPINFO __DIOF(_DCMD_PROC, __PROC_SUBCMD_PROCFS + 2, procfs_mapinfo)
#define DCMD_PROC_MAPDEBUG __DIOTF(_DCMD_PROC, __PROC_SUBCMD_PROCFS + 3, procfs_debuginfo)
#define DCMD_PROC_MAPDEBUG_BASE __DIOF(_DCMD_PROC, __PROC_SUBCMD_PROCFS + 3, procfs_debuginfo)

#endif
