/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: popen() and pclose(). The car's libc.so.3
 * does not export them (QNX programs link them statically), so the target's
 * own library provides them: a shell started with posix_spawn(), its
 * standard input or output on a pipe. */
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

struct nbt_popen {
	struct nbt_popen *next;
	FILE *fp;
	pid_t pid;
};

static struct nbt_popen *nbt_popen_list;
static pthread_mutex_t nbt_popen_lock = PTHREAD_MUTEX_INITIALIZER;

FILE *popen(const char *command, const char *mode)
{
	int reading = mode[0] == 'r';
	if ((mode[0] != 'r' && mode[0] != 'w') || mode[1] != '\0') {
		errno = EINVAL;
		return NULL;
	}
	struct nbt_popen *entry = malloc(sizeof *entry);
	if (!entry)
		return NULL;
	int fds[2];
	if (pipe(fds) != 0) {
		free(entry);
		return NULL;
	}
	/* The child's end becomes its stdin or stdout; neither end stays open in
	 * it under its own number, nor do the streams of earlier popen()s. */
	int child_end = reading ? fds[1] : fds[0];
	int our_end = reading ? fds[0] : fds[1];
	posix_spawn_file_actions_t actions;
	posix_spawn_file_actions_init(&actions);
	posix_spawn_file_actions_adddup2(&actions, child_end, reading ? STDOUT_FILENO : STDIN_FILENO);
	posix_spawn_file_actions_addclose(&actions, child_end);
	posix_spawn_file_actions_addclose(&actions, our_end);
	pthread_mutex_lock(&nbt_popen_lock);
	for (struct nbt_popen *p = nbt_popen_list; p; p = p->next)
		posix_spawn_file_actions_addclose(&actions, fileno(p->fp));
	char *argv[] = { "sh", "-c", (char *)command, NULL };
	pid_t pid;
	int err = posix_spawn(&pid, "/bin/sh", &actions, NULL, argv, environ);
	posix_spawn_file_actions_destroy(&actions);
	close(child_end);
	FILE *fp = err == 0 ? fdopen(our_end, mode) : NULL;
	if (!fp) {
		pthread_mutex_unlock(&nbt_popen_lock);
		close(our_end);
		if (err == 0)
			waitpid(pid, NULL, 0);
		free(entry);
		errno = err ? err : errno;
		return NULL;
	}
	fcntl(our_end, F_SETFD, FD_CLOEXEC);
	entry->fp = fp;
	entry->pid = pid;
	entry->next = nbt_popen_list;
	nbt_popen_list = entry;
	pthread_mutex_unlock(&nbt_popen_lock);
	return fp;
}

int pclose(FILE *fp)
{
	pthread_mutex_lock(&nbt_popen_lock);
	struct nbt_popen **link = &nbt_popen_list;
	while (*link && (*link)->fp != fp)
		link = &(*link)->next;
	struct nbt_popen *entry = *link;
	if (entry)
		*link = entry->next;
	pthread_mutex_unlock(&nbt_popen_lock);
	if (!entry) {
		errno = ECHILD;
		return -1;
	}
	fclose(fp);
	int status = 0;
	pid_t r;
	do {
		r = waitpid(entry->pid, &status, 0);
	} while (r < 0 && errno == EINTR);
	free(entry);
	return r < 0 ? -1 : status;
}
