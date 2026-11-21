/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: sockets (io-pkt, BSD layouts: socket
 * addresses start with their length). */
#ifndef _NBT_QNX_SYS_SOCKET_H
#define _NBT_QNX_SYS_SOCKET_H

#include <sys/_typedefs.h>
#include <sys/uio.h>

typedef __nbt_socklen_t socklen_t;
typedef __nbt_sa_family_t sa_family_t;

#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_RDM 4
#define SOCK_SEQPACKET 5

#define SOL_SOCKET 0xffff
#define SO_DEBUG 0x0001
#define SO_ACCEPTCONN 0x0002
#define SO_REUSEADDR 0x0004
#define SO_KEEPALIVE 0x0008
#define SO_DONTROUTE 0x0010
#define SO_BROADCAST 0x0020
#define SO_USELOOPBACK 0x0040
#define SO_LINGER 0x0080
#define SO_OOBINLINE 0x0100
#define SO_REUSEPORT 0x0200
#define SO_TIMESTAMP 0x0400
#define SO_BINDTODEVICE 0x0800
#define SO_SNDBUF 0x1001
#define SO_RCVBUF 0x1002
#define SO_SNDLOWAT 0x1003
#define SO_RCVLOWAT 0x1004
#define SO_SNDTIMEO 0x1005
#define SO_RCVTIMEO 0x1006
#define SO_ERROR 0x1007
#define SO_TYPE 0x1008

#define AF_UNSPEC 0
#define AF_LOCAL 1
#define AF_UNIX AF_LOCAL
#define AF_INET 2
#define AF_ROUTE 17
#define AF_LINK 18
#define AF_INET6 24
#define AF_BLUETOOTH 31
#define AF_MAX 34
#define PF_UNSPEC AF_UNSPEC
#define PF_LOCAL AF_LOCAL
#define PF_UNIX AF_UNIX
#define PF_INET AF_INET
#define PF_ROUTE AF_ROUTE
#define PF_LINK AF_LINK
#define PF_INET6 AF_INET6
#define PF_BLUETOOTH AF_BLUETOOTH
#define PF_MAX AF_MAX

#define SOMAXCONN 128

#define MSG_OOB 0x0001
#define MSG_PEEK 0x0002
#define MSG_DONTROUTE 0x0004
#define MSG_EOR 0x0008
#define MSG_TRUNC 0x0010
#define MSG_CTRUNC 0x0020
#define MSG_WAITALL 0x0040
#define MSG_DONTWAIT 0x0080
#define MSG_BCAST 0x0100
#define MSG_MCAST 0x0200
#define MSG_NOSIGNAL 0x0800

#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2

#define SCM_RIGHTS 0x01
#define SCM_TIMESTAMP 0x02
#define SCM_CREDS 0x04

struct linger {
	int l_onoff;
	int l_linger;
};

struct sockaddr {
	_Uint8t sa_len;
	sa_family_t sa_family;
	char sa_data[14];
};

struct sockaddr_storage {
	_Uint8t ss_len;
	sa_family_t ss_family;
	char __ss_pad1[6];
	_Int64t __ss_align;
	char __ss_pad2[112];
};

struct msghdr {
	void *msg_name;
	socklen_t msg_namelen;
	struct iovec *msg_iov;
	int msg_iovlen;
	void *msg_control;
	socklen_t msg_controllen;
	int msg_flags;
};

struct cmsghdr {
	socklen_t cmsg_len;
	int cmsg_level;
	int cmsg_type;
};

/* Control messages are aligned as the socket library says. */
__BEGIN_DECLS
int __cmsg_alignbytes(void);
__END_DECLS
#define __CMSG_ALIGN(n) (((n) + __cmsg_alignbytes()) & ~__cmsg_alignbytes())
#define CMSG_ALIGN(n) __CMSG_ALIGN(n)
#define CMSG_DATA(cmsg) ((unsigned char *)(cmsg) + __CMSG_ALIGN(sizeof(struct cmsghdr)))
#define CMSG_FIRSTHDR(mhdr) \
	((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? (struct cmsghdr *)(mhdr)->msg_control : (struct cmsghdr *)0)
#define CMSG_NXTHDR(mhdr, cmsg) \
	(((char *)(cmsg) + __CMSG_ALIGN((cmsg)->cmsg_len) + __CMSG_ALIGN(sizeof(struct cmsghdr)) > \
	  ((char *)(mhdr)->msg_control) + (mhdr)->msg_controllen) \
		 ? (struct cmsghdr *)0 \
		 : (struct cmsghdr *)((char *)(cmsg) + __CMSG_ALIGN((cmsg)->cmsg_len)))
#define CMSG_SPACE(l) (__CMSG_ALIGN(sizeof(struct cmsghdr)) + __CMSG_ALIGN(l))
#define CMSG_LEN(l) (__CMSG_ALIGN(sizeof(struct cmsghdr)) + (l))

__BEGIN_DECLS
int accept(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict __len);
int bind(int __fd, const struct sockaddr *__addr, socklen_t __len);
int connect(int __fd, const struct sockaddr *__addr, socklen_t __len);
int getpeername(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict __len);
int getsockname(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict __len);
int getsockopt(int __fd, int __level, int __name, void *__restrict __val, socklen_t *__restrict __len);
int listen(int __fd, int __backlog);
ssize_t recv(int __fd, void *__buf, size_t __len, int __flags);
ssize_t recvfrom(int __fd, void *__restrict __buf, size_t __len, int __flags, struct sockaddr *__restrict __addr,
		 socklen_t *__restrict __addrlen);
ssize_t recvmsg(int __fd, struct msghdr *__msg, int __flags);
ssize_t send(int __fd, const void *__buf, size_t __len, int __flags);
ssize_t sendmsg(int __fd, const struct msghdr *__msg, int __flags);
ssize_t sendto(int __fd, const void *__buf, size_t __len, int __flags, const struct sockaddr *__addr,
	       socklen_t __addrlen);
int setsockopt(int __fd, int __level, int __name, const void *__val, socklen_t __len);
int shutdown(int __fd, int __how);
int sockatmark(int __fd);
int socket(int __domain, int __type, int __protocol);
int socketpair(int __domain, int __type, int __protocol, int __fds[2]);
__END_DECLS

#endif
