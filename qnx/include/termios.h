/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: terminal (serial device) control. Speeds
 * are the baud rates themselves. */
#ifndef _NBT_QNX_TERMIOS_H
#define _NBT_QNX_TERMIOS_H

#include <sys/_typedefs.h>

#define NCCS 40
typedef unsigned char cc_t;
typedef long speed_t;
typedef unsigned long tcflag_t;

struct termios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
	_Uint32t reserved[3];
	speed_t c_ispeed;
	speed_t c_ospeed;
};

#define IGNBRK 0x00000001
#define BRKINT 0x00000002
#define IGNPAR 0x00000004
#define PARMRK 0x00000008
#define INPCK 0x00000010
#define ISTRIP 0x00000020
#define INLCR 0x00000040
#define IGNCR 0x00000080
#define ICRNL 0x00000100
#define IUCLC 0x00000200
#define IXON 0x00000400
#define IXANY 0x00000800
#define IXOFF 0x00001000
#define IMAXBEL 0x00002000

#define OPOST 0x00000001
#define OLCUC 0x00000002
#define ONLCR 0x00000004
#define OCRNL 0x00000008
#define ONOCR 0x00000010
#define ONLRET 0x00000020

#define IHFLOW 0x00000001
#define OHFLOW 0x00000002
#define CSIZE 0x00000030
#define CS5 0x00
#define CS6 0x10
#define CS7 0x20
#define CS8 0x30
#define CSTOPB 0x00000040
#define CREAD 0x00000080
#define PARENB 0x00000100
#define PARODD 0x00000200
#define HUPCL 0x00000400
#define CLOCAL 0x00000800

#define ISIG 0x00000001
#define ICANON 0x00000002
#define XCASE 0x00000004
#define ECHO 0x00000008
#define ECHOE 0x00000010
#define ECHOK 0x00000020
#define ECHONL 0x00000040
#define NOFLSH 0x00000080
#define TOSTOP 0x00000100
#define ECHOCTL 0x00000200
#define ECHOKE 0x00000800
#define IEXTEN 0x00008000

#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VEOL 5
#define VEOL2 6
#define VSTART 8
#define VSTOP 9
#define VSUSP 10
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE 14
#define VLNEXT 15
#define VMIN 16
#define VTIME 17

#define B0 0
#define B50 50
#define B75 75
#define B110 110
#define B134 134
#define B150 150
#define B200 200
#define B300 300
#define B600 600
#define B1200 1200
#define B1800 1800
#define B2400 2400
#define B4800 4800
#define B9600 9600
#define B19200 19200
#define B38400 38400u
#define B57600 57600u
#define B76800 76800L
#define B115200 115200L

#define TCSANOW 0x0001
#define TCSADRAIN 0x0002
#define TCSAFLUSH 0x0004
#define TCIFLUSH 0x0000
#define TCOFLUSH 0x0001
#define TCIOFLUSH 0x0002
#define TCOOFF 0x0000
#define TCOON 0x0001
#define TCIOFF 0x0002
#define TCION 0x0003

__BEGIN_DECLS
speed_t cfgetispeed(const struct termios *__t);
speed_t cfgetospeed(const struct termios *__t);
int cfsetispeed(struct termios *__t, speed_t __speed);
int cfsetospeed(struct termios *__t, speed_t __speed);
int cfmakeraw(struct termios *__t);
int tcdrain(int __fd);
int tcflow(int __fd, int __action);
int tcflush(int __fd, int __queue);
int tcgetattr(int __fd, struct termios *__t);
int tcsendbreak(int __fd, int __duration);
int tcsetattr(int __fd, int __action, const struct termios *__t);
pid_t tcgetsid(int __fd);
int tcgetsize(int __fd, int *__rows, int *__cols);
int tcsetsize(int __fd, int __rows, int __cols);
__END_DECLS

#endif
