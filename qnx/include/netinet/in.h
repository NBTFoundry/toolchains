/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: Internet addresses (network byte order). */
#ifndef _NBT_QNX_NETINET_IN_H
#define _NBT_QNX_NETINET_IN_H

#include <stdint.h>
#include <sys/socket.h>

typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;

#define IPPROTO_IP 0
#define IPPROTO_ICMP 1
#define IPPROTO_IPV4 4
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define IPPROTO_IPV6 41
#define IPPROTO_ICMPV6 58
#define IPPROTO_RAW 255

struct in_addr {
	in_addr_t s_addr;
} __attribute__((__packed__));

struct sockaddr_in {
	uint8_t sin_len;
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	int8_t sin_zero[8];
};

struct in6_addr {
	union {
		uint8_t __u6_addr8[16];
		uint16_t __u6_addr16[8];
		uint32_t __u6_addr32[4];
	} __u6_addr;
};
#define s6_addr __u6_addr.__u6_addr8

struct sockaddr_in6 {
	uint8_t sin6_len;
	sa_family_t sin6_family;
	in_port_t sin6_port;
	uint32_t sin6_flowinfo;
	struct in6_addr sin6_addr;
	uint32_t sin6_scope_id;
};

struct ip_mreq {
	struct in_addr imr_multiaddr;
	struct in_addr imr_interface;
};

#define __IPADDR(x) ((uint32_t)(x))
#define INADDR_ANY __IPADDR(0x00000000)
#define INADDR_LOOPBACK __IPADDR(0x7f000001)
#define INADDR_BROADCAST __IPADDR(0xffffffff)
#define INADDR_NONE __IPADDR(0xffffffff)
#define IN_LOOPBACKNET 127
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

#define IP_OPTIONS 1
#define IP_HDRINCL 2
#define IP_TOS 3
#define IP_TTL 4
#define IP_RECVOPTS 5
#define IP_RECVRETOPTS 6
#define IP_RECVDSTADDR 7
#define IP_RETOPTS 8
#define IP_MULTICAST_IF 9
#define IP_MULTICAST_TTL 10
#define IP_MULTICAST_LOOP 11
#define IP_ADD_MEMBERSHIP 12
#define IP_DROP_MEMBERSHIP 13
#define IP_PORTRANGE 19
#define IP_RECVIF 20

/* Host and network byte order: the head unit is little endian. */
#define ntohl(x) __builtin_bswap32((uint32_t)(x))
#define htonl(x) __builtin_bswap32((uint32_t)(x))
#define ntohs(x) ((uint16_t)__builtin_bswap16((uint16_t)(x)))
#define htons(x) ((uint16_t)__builtin_bswap16((uint16_t)(x)))

#endif
