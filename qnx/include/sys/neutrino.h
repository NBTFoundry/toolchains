/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: Neutrino kernel calls (message passing,
 * channels and connections, timeouts, thread control). Each call also has
 * an _r form that returns -errno instead of setting errno. */
#ifndef _NBT_QNX_SYS_NEUTRINO_H
#define _NBT_QNX_SYS_NEUTRINO_H

#include <sys/types.h>
#include <signal.h>

/* Kernel thread states; timeouts name the states they end. */
enum {
	STATE_DEAD,
	STATE_RUNNING,
	STATE_READY,
	STATE_STOPPED,
	STATE_SEND,
	STATE_RECEIVE,
	STATE_REPLY,
	STATE_STACK,
	STATE_WAITTHREAD,
	STATE_WAITPAGE,
	STATE_SIGSUSPEND,
	STATE_SIGWAITINFO,
	STATE_NANOSLEEP,
	STATE_MUTEX,
	STATE_CONDVAR,
	STATE_JOIN,
	STATE_INTR,
	STATE_SEM,
	STATE_WAITCTX,
	STATE_NET_SEND,
	STATE_NET_REPLY,
	STATE_MAX = 24
};

#define _NTO_TIMEOUT_RECEIVE (1 << STATE_RECEIVE)
#define _NTO_TIMEOUT_SEND (1 << STATE_SEND)
#define _NTO_TIMEOUT_REPLY (1 << STATE_REPLY)
#define _NTO_TIMEOUT_SIGSUSPEND (1 << STATE_SIGSUSPEND)
#define _NTO_TIMEOUT_SIGWAITINFO (1 << STATE_SIGWAITINFO)
#define _NTO_TIMEOUT_NANOSLEEP (1 << STATE_NANOSLEEP)
#define _NTO_TIMEOUT_MUTEX (1 << STATE_MUTEX)
#define _NTO_TIMEOUT_CONDVAR (1 << STATE_CONDVAR)
#define _NTO_TIMEOUT_JOIN (1 << STATE_JOIN)
#define _NTO_TIMEOUT_INTR (1 << STATE_INTR)
#define _NTO_TIMEOUT_SEM (1 << STATE_SEM)

#define _NTO_CHF_FIXED_PRIORITY 0x0001
#define _NTO_CHF_UNBLOCK 0x0002
#define _NTO_CHF_THREAD_DEATH 0x0004
#define _NTO_CHF_DISCONNECT 0x0008
#define _NTO_CHF_NET_MSG 0x0010
#define _NTO_CHF_SENDER_LEN 0x0020
#define _NTO_CHF_COID_DISCONNECT 0x0040
#define _NTO_CHF_REPLY_LEN 0x0080
#define _NTO_COF_CLOEXEC 0x0001
#define _NTO_COF_DEAD 0x0002
#define _NTO_COF_NOSHARE 0x0040
#define _NTO_SIDE_CHANNEL 0x40000000

#define _NTO_TCTL_IO 1
#define _NTO_TCTL_THREADS_HOLD 2
#define _NTO_TCTL_THREADS_CONT 3
#define _NTO_TCTL_RUNMASK 4
#define _NTO_TCTL_ALIGN_FAULT 5
#define _NTO_TCTL_NAME 11

#define _PULSE_CODE_MINAVAIL 0
#define _PULSE_CODE_MAXAVAIL 127
#define _PULSE_CODE_UNBLOCK (-32)
#define _PULSE_CODE_DISCONNECT (-33)
#define _PULSE_CODE_THREADDEATH (-34)
#define _PULSE_CODE_COIDDEATH (-35)

#define ND_LOCAL_NODE 0

#define SETIOV(_iov, _addr, _len) ((_iov)->iov_base = (void *)(_addr), (_iov)->iov_len = (_len))
#define GETIOVBASE(_iov) ((_iov)->iov_base)
#define GETIOVLEN(_iov) ((_iov)->iov_len)

struct _msg_info {
	_Uint32t nd;
	_Uint32t srcnd;
	pid_t pid;
	_Int32t tid;
	_Int32t chid;
	_Int32t scoid;
	_Int32t coid;
	_Int32t msglen;
	_Int32t srcmsglen;
	_Int32t dstmsglen;
	_Int16t priority;
	_Int16t flags;
	_Uint32t reserved;
};

struct _pulse {
	_Uint16t type;
	_Uint16t subtype;
	_Int8t code;
	_Uint8t zero[3];
	union sigval value;
	_Int32t scoid;
};

__BEGIN_DECLS
int ChannelCreate(unsigned __flags);
int ChannelCreate_r(unsigned __flags);
int ChannelDestroy(int __chid);
int ChannelDestroy_r(int __chid);
int ConnectAttach(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
int ConnectAttach_r(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
int ConnectDetach(int __coid);
int ConnectDetach_r(int __coid);
int MsgSend(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
int MsgSend_r(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
int MsgSendnc(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
int MsgSendsv(int __coid, const void *__smsg, int __sbytes, const struct iovec *__riov, int __rparts);
int MsgSendvs(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
int MsgSendvs_r(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
int MsgSendv(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
int MsgSendv_r(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
int MsgReceive(int __chid, void *__msg, int __bytes, struct _msg_info *__info);
int MsgReceive_r(int __chid, void *__msg, int __bytes, struct _msg_info *__info);
int MsgReceivev(int __chid, const struct iovec *__iov, int __parts, struct _msg_info *__info);
int MsgReceivePulse(int __chid, void *__pulse, int __bytes, struct _msg_info *__info);
int MsgReply(int __rcvid, int __status, const void *__msg, int __bytes);
int MsgReplyv(int __rcvid, int __status, const struct iovec *__iov, int __parts);
int MsgRead(int __rcvid, void *__msg, int __bytes, int __offset);
int MsgReadv(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
int MsgWrite(int __rcvid, const void *__msg, int __bytes, int __offset);
int MsgWritev(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
int MsgSendPulse(int __coid, int __priority, int __code, int __value);
int MsgDeliverEvent(int __rcvid, const struct sigevent *__event);
int MsgError(int __rcvid, int __err);
int MsgInfo(int __rcvid, struct _msg_info *__info);
int ThreadCtl(int __cmd, void *__data);
int ThreadCtl_r(int __cmd, void *__data);
int TimerTimeout(clockid_t __id, int __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
		 _Uint64t *__otime);
int TimerTimeout_r(clockid_t __id, int __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
		   _Uint64t *__otime);
int ClockTime(clockid_t __id, const _Uint64t *__new, _Uint64t *__old);
int ClockTime_r(clockid_t __id, const _Uint64t *__new, _Uint64t *__old);
int SchedYield(void);
int SyncCondvarWait(sync_t *__sync, sync_t *__mutex);
int SyncCondvarSignal(sync_t *__sync, int __all);
int InterruptAttachEvent(int __intr, const struct sigevent *__event, unsigned __flags);
int InterruptDetach(int __id);
int InterruptWait(int __flags, const _Uint64t *__timeout);
int InterruptMask(int __intr, int __id);
int InterruptUnmask(int __intr, int __id);
__END_DECLS

#endif
