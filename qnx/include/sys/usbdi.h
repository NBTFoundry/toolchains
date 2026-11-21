/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: the USB stack's client library (libusbdi):
 * connecting to io-usb, attaching devices, descriptors, pipes and URBs. */
#ifndef _NBT_QNX_SYS_USBDI_H
#define _NBT_QNX_SYS_USBDI_H

#include <sys/types.h>

#define USBD_VERSION 0x0101
#define USBD_CONNECT_WAIT 60
#define USBD_CONNECT_WILDCARD 0xffffffff

#define URB_DIR_IN 0x00000001
#define URB_DIR_OUT 0x00000002
#define URB_DIR_NONE 0x00000003
#define URB_SHORT_XFER_OK 0x00000004
#define URB_ENQUEUE_HEAD 0x00000008
#define URB_ENQUEUE_TAIL 0x00000000
#define URB_ISOCH_ASAP 0x00000010

#define USBD_URB_STATUS_MASK 0xFF000000
#define USBD_STATUS_INPROG 0x00000000
#define USBD_STATUS_CMP 0x01000000
#define USBD_STATUS_CMP_ERR 0x02000000
#define USBD_STATUS_TIMEOUT 0x04000000
#define USBD_STATUS_ABORTED 0x08000000
#define USBD_STATUS_DEVICE_RESET 0x10000000
#define USBD_USB_STATUS_MASK 0x00FFFFFF
#define USBD_STATUS_CRC_ERR 0x00000001
#define USBD_STATUS_BITSTUFFING 0x00000002
#define USBD_STATUS_TOGGLE_MISMATCH 0x00000003
#define USBD_STATUS_STALL 0x00000004
#define USBD_STATUS_DEV_NOANSWER 0x00000005
#define USBD_STATUS_PID_FAILURE 0x00000006
#define USBD_STATUS_BAD_PID 0x00000007
#define USBD_STATUS_DATA_OVERRUN 0x00000008
#define USBD_STATUS_DATA_UNDERRUN 0x00000009
#define USBD_STATUS_BUFFER_OVERRUN 0x0000000C
#define USBD_STATUS_BUFFER_UNDERRUN 0x0000000E
#define USBD_STATUS_NOT_ACCESSED 0x0000000F
#define USBD_TIME_DEFAULT 0x00000000
#define USBD_TIME_INFINITY 0xFFFFFFFF

/* USB 1.1 definitions: descriptor types, endpoints and request types, as in
 * the USB specification. */
#define USB_VERSION 0x0110
#define USB_DESC_DEVICE 0x01
#define USB_DESC_CONFIGURATION 0x02
#define USB_DESC_STRING 0x03
#define USB_DESC_INTERFACE 0x04
#define USB_DESC_ENDPOINT 0x05
#define USB_DESC_DEVICE_QUALIFIER 0x06
#define USB_DESC_OTHER_SPEED_CONF 0x07
#define USB_DESC_INTERFACE_POWER 0x08
#define USB_DESC_HID 0x21
#define USB_DESC_REPORT 0x22
#define USB_ENDPOINT_CONTROL 0
#define USB_ENDPOINT_MASK 0x0F
#define USB_ENDPOINT_IN 0x80
#define USB_ENDPOINT_OUT 0x00
#define USB_ATTRIB_CONTROL 0x00
#define USB_ATTRIB_ISOCHRONOUS 0x01
#define USB_ATTRIB_BULK 0x02
#define USB_ATTRIB_INTERRUPT 0x03
#define USB_RECIPIENT_DEVICE (0 << 0)
#define USB_RECIPIENT_INTERFACE (1 << 0)
#define USB_RECIPIENT_ENDPOINT (2 << 0)
#define USB_RECIPIENT_OTHER (3 << 0)
#define USB_TYPE_STANDARD (0 << 5)
#define USB_TYPE_CLASS (1 << 5)
#define USB_TYPE_VENDOR (2 << 5)
#define USB_DIRECTION_DEVICE (0 << 7)
#define USB_DIRECTION_HOST (1 << 7)

struct usbd_connection;
struct usbd_desc_node;
struct usbd_device;
struct usbd_pipe;
struct usbd_urb;

typedef struct usb100_generic_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
} usb100_generic_descriptor_t;

typedef struct usbd_device_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint16t bcdUSB;
	_Uint8t bDeviceClass;
	_Uint8t bDeviceSubClass;
	_Uint8t bDeviceProtocol;
	_Uint8t bMaxPacketSize0;
	_Uint16t idVendor;
	_Uint16t idProduct;
	_Uint16t bcdDevice;
	_Uint8t iManufacturer;
	_Uint8t iProduct;
	_Uint8t iSerialNumber;
	_Uint8t bNumConfigurations;
} usbd_device_descriptor_t;

typedef struct usbd_configuration_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint16t wTotalLength;
	_Uint8t bNumInterfaces;
	_Uint8t bConfigurationValue;
	_Uint8t iConfiguration;
	_Uint8t bmAttributes;
	_Uint8t MaxPower;
} usbd_configuration_descriptor_t;

typedef struct usbd_string_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint16t bString[1];
} usbd_string_descriptor_t;

typedef struct usbd_interface_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint8t bInterfaceNumber;
	_Uint8t bAlternateSetting;
	_Uint8t bNumEndpoints;
	_Uint8t bInterfaceClass;
	_Uint8t bInterfaceSubClass;
	_Uint8t bInterfaceProtocol;
	_Uint8t iInterface;
} usbd_interface_descriptor_t;

typedef struct usbd_endpoint_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint8t bEndpointAddress;
	_Uint8t bmAttributes;
	_Uint16t wMaxPacketSize;
	_Uint8t bInterval;
} usbd_endpoint_descriptor_t;

typedef struct usbd_audio_endpoint_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint8t bEndpointAddress;
	_Uint8t bmAttributes;
	_Uint16t wMaxPacketSize;
	_Uint8t bInterval;
	_Uint8t bRefresh;
	_Uint8t bSyncAddress;
} usbd_audio_endpoint_descriptor_t;

typedef struct usbd_hid_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint16t bcdHID;
	_Uint8t bCountryCode;
	_Uint8t bNumDescriptors;
	_Uint8t bReportDescriptorType;
	_Uint16t wDescriptorLength;
} usbd_hid_descriptor_t;

typedef struct usbd_hub_descriptor {
	_Uint8t bLength;
	_Uint8t bDescriptorType;
	_Uint8t bNbrPorts;
	_Uint16t wHubCharacteristics;
	_Uint8t bPwrOn2PwrGood;
	_Uint8t bHubContrCurrent;
	_Uint8t DeviceRemovable[1];
	_Uint8t PortPwrCtrlMask[1];
} usbd_hub_descriptor_t;

typedef union usbd_descriptors {
	usb100_generic_descriptor_t generic;
	usbd_device_descriptor_t device;
	usbd_configuration_descriptor_t configuration;
	usbd_string_descriptor_t string;
	usbd_interface_descriptor_t interface;
	usbd_endpoint_descriptor_t endpoint;
	usbd_audio_endpoint_descriptor_t audio;
	usbd_hid_descriptor_t hid;
	usbd_hub_descriptor_t hub;
} usbd_descriptors_t;

typedef struct usbd_device_ident {
	_Uint32t vendor;
	_Uint32t device;
	_Uint32t dclass;
	_Uint32t subclass;
	_Uint32t protocol;
} usbd_device_ident_t;

typedef struct usbd_device_instance {
	_Uint8t path;
	_Uint8t devno;
	_Uint16t generation;
	usbd_device_ident_t ident;
	_Uint32t config;
	_Uint32t iface;
	_Uint32t alternate;
} usbd_device_instance_t;

typedef struct usbd_funcs {
	_Uint32t nentries;
	void (*insertion)(struct usbd_connection *, usbd_device_instance_t *instance);
	void (*removal)(struct usbd_connection *, usbd_device_instance_t *instance);
	void (*event)(struct usbd_connection *, usbd_device_instance_t *instance, _Uint16t type);
} usbd_funcs_t;
#define _USBDI_NFUNCS ((sizeof(usbd_funcs_t) - sizeof(_Uint32t)) / sizeof(void *))

typedef struct usbd_connect_parm {
	const char *path;
	_Uint16t vusb;
	_Uint16t vusbd;
	_Uint32t flags;
	_Int32t argc;
	char **argv;
	_Uint32t evtbufsz;
	usbd_device_ident_t *ident;
	usbd_funcs_t *funcs;
	_Uint16t connect_wait;
	_Uint8t evtprio;
	_Uint8t _reserved[13];
} usbd_connect_parm_t;
#define USBD_CONNECT_FLAG_NO_DESCRIPTOR_CACHE 0x00000001

typedef struct usbd_hcd_info {
	_Uint16t vusb;
	_Uint16t vusbd;
	char controller[8];
	_Uint32t capabilities;
	_Uint8t ndev;
	_Uint8t cindex;
	_Uint16t vhcd;
	_Uint32t max_td_io;
	_Uint8t _reserved[12];
} usbd_hcd_info_t;

__BEGIN_DECLS
int usbd_connect(usbd_connect_parm_t *__parm, struct usbd_connection **__connection);
int usbd_disconnect(struct usbd_connection *__connection);
int usbd_hcd_info(struct usbd_connection *__connection, usbd_hcd_info_t *__info);
int usbd_attach(struct usbd_connection *__connection, usbd_device_instance_t *__instance, size_t __extra,
		struct usbd_device **__device);
int usbd_detach(struct usbd_device *__device);
int usbd_select_config(struct usbd_device *__device, _Uint8t __config);
int usbd_select_interface(struct usbd_device *__device, _Uint8t __iface, _Uint8t __alternate);
int usbd_open_pipe(struct usbd_device *__device, usbd_descriptors_t *__desc, struct usbd_pipe **__pipe);
int usbd_close_pipe(struct usbd_pipe *__pipe);
int usbd_reset_pipe(struct usbd_pipe *__pipe);
int usbd_abort_pipe(struct usbd_pipe *__pipe);
int usbd_reset_device(struct usbd_device *__device);
struct usbd_urb *usbd_alloc_urb(struct usbd_urb *__link);
struct usbd_urb *usbd_free_urb(struct usbd_urb *__urb);
void *usbd_alloc(size_t __size);
void usbd_free(void *__ptr);
paddr_t usbd_mphys(const void *__ptr);
int usbd_descriptor(struct usbd_device *__device, int __set, _Uint8t __type, _Uint16t __rtype, _Uint8t __index,
		    _Uint16t __langid, _Uint8t *__desc, size_t __len);
int usbd_feature(struct usbd_device *__device, int __set, _Uint16t __feature, _Uint16t __rtype, _Uint16t __index);
int usbd_status(struct usbd_device *__device, _Uint16t __rtype, _Uint16t __index, void *__addr, _Uint32t __len);
int usbd_setup_vendor(struct usbd_urb *__urb, _Uint32t __flags, _Uint16t __request, _Uint16t __rtype,
		      _Uint16t __value, _Uint16t __index, void *__addr, _Uint32t __len);
int usbd_setup_bulk(struct usbd_urb *__urb, _Uint32t __flags, void *__addr, _Uint32t __len);
int usbd_setup_interrupt(struct usbd_urb *__urb, _Uint32t __flags, void *__addr, _Uint32t __len);
int usbd_setup_isochronous(struct usbd_urb *__urb, _Uint32t __flags, _Int32t __frame, void *__addr, _Uint32t __len);
int usbd_io(struct usbd_urb *__urb, struct usbd_pipe *__pipe, void (*__func)(struct usbd_urb *, struct usbd_pipe *, void *),
	    void *__handle, _Uint32t __timeout);
int usbd_urb_status(struct usbd_urb *__urb, _Uint32t *__status, _Uint32t *__length);
usbd_descriptors_t *usbd_parse_descriptors(struct usbd_device *__device, struct usbd_desc_node *__root, _Uint8t __type,
					   int __index, struct usbd_desc_node **__node);
char *usbd_string(struct usbd_device *__device, _Uint8t __index, int __langid);
struct usbd_device *usbd_device_lookup(struct usbd_connection *__connection, usbd_device_instance_t *__instance);
void *usbd_device_extra(struct usbd_device *__device);
_Uint8t usbd_pipe_endpoint(struct usbd_pipe *__pipe);
struct usbd_device *usbd_pipe_device(struct usbd_pipe *__pipe);
usbd_device_descriptor_t *usbd_device_descriptor(struct usbd_device *__device, struct usbd_desc_node **__node);
usbd_configuration_descriptor_t *usbd_configuration_descriptor(struct usbd_device *__device, _Uint8t __config,
							       struct usbd_desc_node **__node);
usbd_interface_descriptor_t *usbd_interface_descriptor(struct usbd_device *__device, _Uint8t __config, _Uint8t __iface,
						       _Uint8t __alternate, struct usbd_desc_node **__node);
usbd_endpoint_descriptor_t *usbd_endpoint_descriptor(struct usbd_device *__device, _Uint8t __config, _Uint8t __iface,
						     _Uint8t __alternate, _Uint8t __endpoint,
						     struct usbd_desc_node **__node);
__END_DECLS

#endif
