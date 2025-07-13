#pragma once
#include <windows.h>
#include "ed_sound_params.h"
typedef int SND_Context_id;
typedef int SND_Host_id;
typedef int SND_Source_id;
#define SND_CONTEXT_ID_NONE (-1)
#define SND_HOST_ID_NONE (-1)
#define SND_SOURCE_ID_NONE (-1)

typedef SND_Host_id(*SND_add_host)(SND_Context_id ctx, const char* name, const struct SND_HostParams* params);
typedef void (*SND_host_update)(SND_Host_id hid, const struct SND_HostParams* params);
typedef void (*SND_host_del)(SND_Host_id hid);

typedef SND_Source_id(*SND_add_source)(SND_Host_id hid, const char* proto, const struct SND_SourceParams* params);
typedef SND_Source_id(*SND_add_source_alt)(SND_Host_id hid, std::wstring proto, const char* alt_proto, const struct SND_SourceParams* params);
typedef void (*SND_source_play)(SND_Source_id src, const struct SND_PlayParams* play, const struct SND_SourceParams* params);
typedef void (*SND_source_update)(SND_Source_id src, const struct SND_SourceParams* params);
typedef void (*SND_source_stop)(SND_Source_id src);
typedef void (*SND_source_del)(SND_Source_id src);
typedef void (*SND_set_listener)(SND_Context_id ctx, const struct SND_ListenerParams* params);
typedef int (*SND_source_is_playing)(SND_Source_id src);


/**
 * 链接源，因此播放/更新/停止链接链中任一源都会影响所有源。
 * 可能只有一个来源已链接。
 * @return 1 表示成功，0 表示失败（无效源或两者都已链接）
 */
typedef int (*SND_source_link)(SND_Source_id src1, SND_Source_id src2);

/**
 * 从它的链中取消链接源。
 * @return 1 表示成功，0 表示失败（未链接或源 ID 无效）
 */
typedef int (*SND_source_unlink)(SND_Source_id src);


/* -------------------
 * Live streaming API.
 */

 /**
   * 将音频缓冲区推送到实时播放源，每次调用都会将数据附加到源播放队列。
   * @return 消耗的帧数。
   * @note 当前忽略源链接。
  */
typedef unsigned (*SND_source_live_push)(SND_Source_id src,
	unsigned samplerate, unsigned channels,
	unsigned frames, const short* data);

/**
 * 获取直播源的当前播放时间（以秒为单位）。
 */
typedef double (*SND_source_live_time)(SND_Source_id src);



struct ed_snd_api
{
	SND_add_host snd_add_host;
	SND_host_update snd_host_update;
	SND_host_del snd_host_del;
	SND_set_listener snd_set_listener;

	SND_add_source snd_add_src;
	SND_add_source_alt snd_add_src_alt;
	SND_source_play snd_src_play;
	SND_source_update snd_src_update;
	SND_source_stop snd_src_stop;
	SND_source_del snd_src_del;
	SND_source_is_playing snd_src_is_playing;
	SND_source_link snd_src_link;
	SND_source_unlink snd_src_unlink;

	SND_source_live_push snd_src_live_push;
	SND_source_live_time snd_src_live_time;
};

inline ed_snd_api  ed_get_snd_api()
{
	HMODULE edSound_dll = GetModuleHandleA("ed_sound.dll"); //assume that we work inside same process

	ed_snd_api ret;
	ret.snd_add_host = (SND_add_host)GetProcAddress(edSound_dll, "SND_add_host");
	ret.snd_host_update = (SND_host_update)GetProcAddress(edSound_dll, "SND_host_update");
	ret.snd_host_del = (SND_host_del)GetProcAddress(edSound_dll, "SND_host_del");
	ret.snd_set_listener = (SND_set_listener)GetProcAddress(edSound_dll, "SND_set_listener");

	ret.snd_add_src = (SND_add_source)GetProcAddress(edSound_dll, "SND_add_source");
	ret.snd_add_src_alt = (SND_add_source_alt)GetProcAddress(edSound_dll, "SND_add_source_alt");
	ret.snd_src_play = (SND_source_play)GetProcAddress(edSound_dll, "SND_source_play");
	ret.snd_src_update = (SND_source_update)GetProcAddress(edSound_dll, "SND_source_update");
	ret.snd_src_stop = (SND_source_stop)GetProcAddress(edSound_dll, "SND_source_stop");
	ret.snd_src_del = (SND_source_del)GetProcAddress(edSound_dll, "SND_source_del");
	ret.snd_src_is_playing = (SND_source_is_playing)GetProcAddress(edSound_dll, "SND_source_is_playing");
	ret.snd_src_link = (SND_source_link)GetProcAddress(edSound_dll, "SND_source_link");
	ret.snd_src_unlink = (SND_source_unlink)GetProcAddress(edSound_dll, "SND_source_unlink");

	ret.snd_src_live_push = (SND_source_live_push)GetProcAddress(edSound_dll, "SND_source_live_push");
	ret.snd_src_live_time = (SND_source_live_time)GetProcAddress(edSound_dll, "SND_source_live_time");
	return ret;
}