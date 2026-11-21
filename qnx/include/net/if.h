/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: network interfaces. struct ifreq's union
 * holds a sockaddr_storage, and its flags are an int (io-pkt). */
#ifndef _NBT_QNX_NET_IF_H
#define _NBT_QNX_NET_IF_H

#include <stdint.h>
#include <sys/socket.h>

#define IF_NAMESIZE 16
#define IFNAMSIZ IF_NAMESIZE

#define IFF_UP 0x00000001
#define IFF_BROADCAST 0x00000002
#define IFF_DEBUG 0x00000004
#define IFF_LOOPBACK 0x00000008
#define IFF_POINTOPOINT 0x00000010
#define IFF_NOTRAILERS 0x00000020
#define IFF_RUNNING 0x00000040
#define IFF_NOARP 0x00000080
#define IFF_PROMISC 0x00000100
#define IFF_ALLMULTI 0x00000200
#define IFF_OACTIVE 0x00000400
#define IFF_SIMPLEX 0x00000800
#define IFF_MULTICAST 0x00008000

struct ifreq {
	char ifr_name[IFNAMSIZ];
	union {
		struct sockaddr ifru_addr;
		struct sockaddr ifru_dstaddr;
		struct sockaddr ifru_broadaddr;
		struct sockaddr_storage ifru_space;
		int ifru_flags;
		int ifru_metric;
		int ifru_mtu;
		int ifru_dlt;
		unsigned int ifru_value;
		void *ifru_data;
		struct {
			uint32_t b_buflen;
			void *b_buf;
		} ifru_b;
	} ifr_ifru;
};
#define ifr_addr ifr_ifru.ifru_addr
#define ifr_dstaddr ifr_ifru.ifru_dstaddr
#define ifr_broadaddr ifr_ifru.ifru_broadaddr
#define ifr_space ifr_ifru.ifru_space
#define ifr_flags ifr_ifru.ifru_flags
#define ifr_metric ifr_ifru.ifru_metric
#define ifr_mtu ifr_ifru.ifru_mtu
#define ifr_value ifr_ifru.ifru_value
#define ifr_data ifr_ifru.ifru_data

struct ifconf {
	int ifc_len;
	union {
		void *ifcu_buf;
		struct ifreq *ifcu_req;
	} ifc_ifcu;
};
#define ifc_buf ifc_ifcu.ifcu_buf
#define ifc_req ifc_ifcu.ifcu_req

struct if_nameindex {
	unsigned int if_index;
	char *if_name;
};

__BEGIN_DECLS
unsigned int if_nametoindex(const char *__name);
char *if_indextoname(unsigned int __index, char *__name);
struct if_nameindex *if_nameindex(void);
void if_freenameindex(struct if_nameindex *__ptr);
__END_DECLS

#endif
