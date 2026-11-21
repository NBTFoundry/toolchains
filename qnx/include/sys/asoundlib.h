/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: QNX Sound Architecture PCM playback and
 * capture (libasound.so.2): channel information, parameters, setup and
 * status, and the plugin layer that converts formats. */
#ifndef _NBT_QNX_SYS_ASOUNDLIB_H
#define _NBT_QNX_SYS_ASOUNDLIB_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>

#define SND_PCM_CHANNEL_PLAYBACK 0
#define SND_PCM_CHANNEL_CAPTURE 1
#define SND_PCM_OPEN_PLAYBACK 0x0001
#define SND_PCM_OPEN_CAPTURE 0x0002
#define SND_PCM_OPEN_DUPLEX 0x0003
#define SND_PCM_OPEN_NONBLOCK 0x1000
#define SND_PCM_MODE_BLOCK 1
#define SND_PCM_MODE_STREAM 2
#define SND_PCM_SFMT_U8 0
#define SND_PCM_SFMT_S8 1
#define SND_PCM_SFMT_S16_LE 4
#define SND_PCM_SFMT_S16_BE 5
#define SND_PCM_SFMT_S32_LE 12
#define SND_PCM_SFMT_FLOAT_LE 19
#define SND_PCM_START_DATA 1
#define SND_PCM_START_FULL 2
#define SND_PCM_START_GO 3
#define SND_PCM_STOP_STOP 1
#define SND_PCM_STOP_ROLLOVER 2
#define SND_PCM_FILL_NONE 1
#define SND_PCM_FILL_SILENCE 2
#define SND_PCM_STATUS_NOTREADY 0
#define SND_PCM_STATUS_READY 1
#define SND_PCM_STATUS_PREPARED 2
#define SND_PCM_STATUS_RUNNING 3
#define SND_PCM_STATUS_UNDERRUN 4
#define SND_PCM_STATUS_OVERRUN 5
#define SND_PCM_STATUS_PAUSED 10
#define SND_PCM_STATUS_ERROR 10000
#define SND_PCM_STATUS_CHANGE 10001
#define SND_PCM_RATE_8000 (1 << 1)
#define SND_PCM_RATE_11025 (1 << 2)
#define SND_PCM_RATE_16000 (1 << 3)
#define SND_PCM_RATE_22050 (1 << 4)
#define SND_PCM_RATE_32000 (1 << 5)
#define SND_PCM_RATE_44100 (1 << 6)
#define SND_PCM_RATE_48000 (1 << 7)

typedef struct snd_pcm snd_pcm_t;

typedef struct {
	int32_t type;
	char name[36];
	int32_t index;
	uint8_t reserved[120];
	int32_t weight;
} snd_mixer_eid_t;

typedef struct {
	int32_t type;
	char name[32];
	int32_t index;
	uint8_t reserved[124];
	int32_t weight;
} snd_mixer_gid_t;

typedef union snd_pcm_sync {
	uint8_t id[16];
	uint16_t id16[8];
	uint32_t id32[4];
	uint64_t id64[2];
} snd_pcm_sync_t;

typedef struct snd_pcm_digital {
	uint8_t dig_status[24];
	uint8_t dig_subcode[147];
	uint8_t dig_valid : 1;
	uint8_t dig_subframe[4];
	uint8_t reserved[128];
} snd_pcm_digital_t;

typedef struct snd_pcm_channel_info {
	int32_t subdevice;
	char subname[36];
	int32_t channel;
	int32_t zero1;
	int32_t zero2[4];
	uint32_t flags;
	uint32_t formats;
	uint32_t rates;
	int32_t min_rate;
	int32_t max_rate;
	int32_t min_voices;
	int32_t max_voices;
	int32_t max_buffer_size;
	int32_t min_fragment_size;
	int32_t max_fragment_size;
	int32_t fragment_align;
	int32_t fifo_size;
	int32_t transfer_block_size;
	uint8_t zero3[4];
	snd_pcm_digital_t dig_mask;
	uint32_t zero4;
	int32_t mixer_device;
	snd_mixer_eid_t mixer_eid;
	snd_mixer_gid_t mixer_gid;
	uint8_t reserved[128];
} snd_pcm_channel_info_t;

typedef struct snd_pcm_format {
	uint32_t interleave : 1;
	int32_t format;
	int32_t rate;
	int32_t voices;
	int32_t special;
	uint8_t reserved[124];
} snd_pcm_format_t;

typedef struct snd_pcm_channel_params {
	int32_t channel;
	int32_t mode;
	snd_pcm_sync_t sync;
	snd_pcm_format_t format;
	snd_pcm_digital_t digital;
	int32_t start_mode;
	int32_t stop_mode;
	int32_t time : 1, ust_time : 1;
	uint32_t why_failed;
	union {
		struct {
			int32_t queue_size;
			int32_t fill;
			int32_t max_fill;
			uint8_t reserved[124];
		} stream;
		struct {
			int32_t frag_size;
			int32_t frags_min;
			int32_t frags_max;
			uint8_t reserved[124];
		} block;
		uint8_t reserved[128];
	} buf;
	char sw_mixer_subchn_name[32];
	uint8_t reserved[96];
} snd_pcm_channel_params_t;

typedef struct snd_pcm_channel_setup {
	int32_t channel;
	int32_t mode;
	snd_pcm_format_t format;
	snd_pcm_digital_t digital;
	union {
		struct {
			int32_t queue_size;
			uint8_t reserved[124];
		} stream;
		struct {
			int32_t frag_size;
			int32_t frags;
			int32_t frags_min;
			int32_t frags_max;
			uint32_t max_frag_size;
			uint8_t reserved[124];
		} block;
		uint8_t reserved[128];
	} buf;
	int16_t msbits_per_sample;
	int16_t pad1;
	int32_t mixer_device;
	snd_mixer_eid_t *mixer_eid;
	snd_mixer_gid_t *mixer_gid;
	uint8_t mmap_valid : 1;
	uint8_t mmap_active : 1;
	int32_t mixer_card;
	uint8_t reserved[104];
} snd_pcm_channel_setup_t;

typedef struct snd_pcm_channel_status {
	int32_t channel;
	int32_t mode;
	int32_t status;
	uint32_t scount;
	struct timeval stime;
	uint64_t ust_stime;
	int32_t frag;
	int32_t count;
	int32_t free;
	int32_t underrun;
	int32_t overrun;
	int32_t overrange;
	uint32_t subbuffered;
	uint8_t reserved[124];
} snd_pcm_channel_status_t;

__BEGIN_DECLS
const char *snd_strerror(int __errnum);
int snd_cards(void);
int snd_pcm_open(snd_pcm_t **__handle, int __card, int __device, int __mode);
int snd_pcm_open_name(snd_pcm_t **__handle, char *__name, int __mode);
int snd_pcm_open_preferred(snd_pcm_t **__handle, int *__rcard, int *__rdevice, int __mode);
int snd_pcm_close(snd_pcm_t *__handle);
int snd_pcm_file_descriptor(snd_pcm_t *__handle, int __channel);
int snd_pcm_nonblock_mode(snd_pcm_t *__handle, int __nonblock);
int snd_pcm_channel_info(snd_pcm_t *__handle, snd_pcm_channel_info_t *__info);
int snd_pcm_channel_params(snd_pcm_t *__handle, snd_pcm_channel_params_t *__params);
int snd_pcm_channel_setup(snd_pcm_t *__handle, snd_pcm_channel_setup_t *__setup);
int snd_pcm_channel_status(snd_pcm_t *__handle, snd_pcm_channel_status_t *__status);
int snd_pcm_channel_prepare(snd_pcm_t *__handle, int __channel);
int snd_pcm_channel_go(snd_pcm_t *__handle, int __channel);
int snd_pcm_channel_flush(snd_pcm_t *__handle, int __channel);
ssize_t snd_pcm_write(snd_pcm_t *__handle, const void *__buffer, size_t __size);
int snd_pcm_plugin_info(snd_pcm_t *__handle, snd_pcm_channel_info_t *__info);
int snd_pcm_plugin_params(snd_pcm_t *__handle, snd_pcm_channel_params_t *__params);
int snd_pcm_plugin_setup(snd_pcm_t *__handle, snd_pcm_channel_setup_t *__setup);
int snd_pcm_plugin_status(snd_pcm_t *__handle, snd_pcm_channel_status_t *__status);
int snd_pcm_plugin_prepare(snd_pcm_t *__handle, int __channel);
int snd_pcm_plugin_playback_drain(snd_pcm_t *__handle);
int snd_pcm_plugin_flush(snd_pcm_t *__handle, int __channel);
ssize_t snd_pcm_plugin_write(snd_pcm_t *__handle, const void *__buffer, size_t __size);
ssize_t snd_pcm_plugin_read(snd_pcm_t *__handle, void *__buffer, size_t __size);
unsigned int snd_pcm_plugin_set_disable(snd_pcm_t *__handle, unsigned int __mask);
__END_DECLS

#endif
