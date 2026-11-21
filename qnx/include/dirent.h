/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: directories. struct dirent carries no
 * d_type: QNX's directory entries hold the inode, offset and name only. */
#ifndef _NBT_QNX_DIRENT_H
#define _NBT_QNX_DIRENT_H

#include <sys/types.h>
#include <sys/stat.h>

struct dirent {
#ifdef __NBT_OFF64
	ino_t d_ino;
	off_t d_offset;
#else
	ino_t d_ino;
	ino_t d_ino_hi;
	off_t d_offset;
	off_t d_offset_hi;
#endif
	_Int16t d_reclen;
	_Int16t d_namelen;
	char d_name[1];
};

struct dirent64 {
	ino64_t d_ino;
	off64_t d_offset;
	_Int16t d_reclen;
	_Int16t d_namelen;
	char d_name[1];
};

typedef struct _dir DIR;

__BEGIN_DECLS
int closedir(DIR *__dir);
DIR *opendir(const char *__name);
struct dirent *readdir(DIR *__dir) __NBT_ALIAS64("readdir64");
struct dirent64 *readdir64(DIR *__dir);
int readdir_r(DIR *__restrict __dir, struct dirent *__restrict __entry, struct dirent **__restrict __result);
void rewinddir(DIR *__dir);
void seekdir(DIR *__dir, long __pos);
long telldir(DIR *__dir);
int alphasort(const void *__a, const void *__b);
int scandir(char *__dir, struct dirent ***__namelist, int (*__select)(const struct dirent *),
	    int (*__compar)(const void *, const void *));
int dircntl(DIR *__dir, int __cmd, ...);
__END_DECLS

#endif
