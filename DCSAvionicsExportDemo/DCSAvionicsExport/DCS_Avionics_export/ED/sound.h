#pragma once
#include <stdio.h>
#include "../utils.h"
#include "ed_sounds_api.h"
#include "../Table.h"
class Sound {
public:
	enum ContextID {
		// main contexts
		UI_CONTEXT,
		HEADPHONES_CONTEXT,
		COCKPIT_CONTEXT,
		WORLD_CONTEXT,

		// supplementary contexts
		COCKPIT2D_CONTEXT,
		WORLD2D_CONTEXT,

		// add new contexts BEFORE this line
		NUM_CONTEXTS
	};
	Sound() {
		snd_api = ed_get_snd_api();
	}
	SND_Host_id add_host(SND_Context_id cid, const char* name, const struct SND_HostParams* params)
	{
		return snd_api.snd_add_host(cid, name, params);
	}
	void update_host(SND_Host_id hostId, const struct SND_HostParams* params)
	{
		snd_api.snd_host_update(hostId, params);
	}
	void del_host(SND_Host_id hostId)
	{
		snd_api.snd_host_del(hostId);
	}
	SND_Source_id add_source(SND_Host_id hid, const wchar_t* proto, const struct SND_SourceParams* params)
	{
		return snd_api.snd_add_src(hid, wcharToChar(proto).c_str(), params);
	}
	SND_Source_id add_source_alt(SND_Host_id hid, const std::wstring proto, const char* alt_proto, const struct SND_SourceParams* params)
	{
		return snd_api.snd_add_src_alt(hid, proto, alt_proto, params);
	}
	void snd_play(SND_Source_id src, const struct SND_PlayParams* play, const struct SND_SourceParams* params)
	{
		snd_api.snd_src_play(src, play, params);
	}
	void snd_update(SND_Source_id src, const struct SND_SourceParams* params)
	{
		snd_api.snd_src_update(src, params);
	}
	void snd_stop(SND_Source_id src)
	{
		snd_api.snd_src_stop(src);
	}
	void snd_del(SND_Source_id src)
	{
		snd_api.snd_src_del(src);
	}
	int snd_is_playing(SND_Source_id src)
	{
		return snd_api.snd_src_is_playing(src);
	}
	int snd_link(SND_Source_id src1, SND_Source_id src2)
	{
		return snd_api.snd_src_link(src1, src2);
	}
	int snd_unlink(SND_Source_id src)
	{
		return snd_api.snd_src_unlink(src);
	}
	void snd_set_listener(SND_Context_id ctx, const struct SND_ListenerParams* params)
	{
		snd_api.snd_set_listener(ctx, params);
	}

private:
	ed_snd_api snd_api;
};
class SoundSource {
public:
	SoundSource(Sound& p_snd, SND_Host_id hostId, SND_PlayMode playMode, const Proto& proto)
		:snd(p_snd), linkId(-1), soundLength(proto.length)
	{
		params = std::make_unique<SND_SourceParams>();
		playParams = std::make_unique<SND_PlayParams>();
		playParams->playmode = playMode;
		params->fields = 6;
		params->gain = proto.gain;
		params->lowpass = proto.lowpass;
		params->pitch = proto.pitch;
		params->radius = proto.radius;
		params->orientation[0] = 0.0;
		params->orientation[1] = 0.0;
		params->orientation[2] = 0.0;
		params->orientation[3] = 0.0;
		params->position[0] = 0.0;
		params->position[1] = 0.0;
		params->position[2] = 0.0;
		id = snd.add_source(hostId, proto.path.c_str(), params.get());
	}
	~SoundSource()
	{
		destroy();
	}
	SND_Source_id getSrcId()
	{
		return id;
	}
	void updatePosition(double x, double y, double z)
	{
		params->position[0] = x;
		params->position[1] = z;
		params->position[2] = y;
	}
	void updateOrientation(double x, double y, double z, double p)
	{
		params->orientation[0] = x;
		params->orientation[1] = z;
		params->orientation[2] = y;
		params->orientation[3] = p;
	}
	void updateGain(double gain)
	{
		params->gain = gain;
	}
	void updatePitch(double pitch)
	{
		params->pitch = pitch;
	}
	void updateField(int fields)
	{
		params->fields = fields;
	}
	void updateLowpass(float lowpass)
	{
		params->lowpass = lowpass;
	}
	void updateRadius(double radius)
	{
		params->radius = radius;
	}
	void destroy()
	{
		if (linkId != -1)
		{
			snd.snd_unlink(id);
			linkId = -1;
		}
		snd.snd_stop(id);
		snd.snd_del(id);
	}
	void playOnce()
	{
		if (!isPlaying())
		{
			playParams->playmode = SND_PLAYMODE_ONCE;
			snd.snd_play(id, playParams.get(), params.get());
		}
	}
	void playLoop()
	{
		if (!isPlaying())
		{
			playParams->playmode = SND_PLAYMODE_LOOPED;
			snd.snd_play(id, playParams.get(), params.get());
		}
	}
	void link(SoundSource& linkSource)
	{
		if (linkSource.getSrcId() >= 0)
		{
			linkSource.playParams->playmode = playParams->playmode;
			snd.snd_link(id, linkSource.getSrcId());
			linkId = linkSource.getSrcId();
		}
	}
	void stop()
	{
		snd.snd_stop(id);
	}
	bool isPlaying()
	{
		return snd.snd_is_playing(id);
	}
	void update(double dt, Vec3 worldPosition, Quaternion& quaternion)
	{
		if (snd.snd_is_playing(id))
		{
			timestamp += (dt * params->pitch);
			if (playParams->playmode == SND_PLAYMODE_ONCE)
			{
				if (timestamp > soundLength)
				{
					stop();
					printf("stop()\n");
				}
			}
		}
		else
		{
			timestamp = 0;
		}
		//playParams->timestamp = timestamp;
		params->position[0] = worldPosition.x;
		params->position[1] = worldPosition.y;
		params->position[2] = worldPosition.z;
		params->orientation[0] = quaternion.x;
		params->orientation[1] = quaternion.y;
		params->orientation[2] = quaternion.z;
		params->orientation[3] = quaternion.w;
		snd.snd_update(id, params.get());
	}
private:
	std::unique_ptr<SND_SourceParams> params;
	SND_Source_id id = SND_SOURCE_ID_NONE;
	std::unique_ptr<SND_PlayParams> playParams;
	Sound& snd;
	SND_Source_id linkId = SND_SOURCE_ID_NONE;
	double soundLength = 0;
	double timestamp = 0;
};
class SoundHost {
public:
	SoundHost(SND_Context_id p_ctx, const char* p_name, Sound& p_snd) : ctx(p_ctx), name(p_name), snd(p_snd)
	{
		params = std::make_unique<SND_HostParams>();
		params->fields = 5;
		params->gain = 1.0;
		params->orientation[0] = 0.0;
		params->orientation[1] = 0.0;
		params->orientation[2] = 0.0;
		params->orientation[3] = 0.0;
		params->position[0] = 0;
		params->position[1] = 0;
		params->position[2] = 0;
		params->velocity[0] = 0;
		params->velocity[1] = 0;
		params->velocity[2] = 0;
		params->timestamp = 0;
		id = snd.add_host(ctx, name, params.get());
	}
	~SoundHost()
	{
		destroy();
	}
	SND_Context_id ctx;
	const char* name;
	SND_Host_id getHostId()
	{
		return id;
	}
	void updatePosition(double x, double y, double z)
	{
		params->position[0] = x;
		params->position[1] = z;
		params->position[2] = y;
	}
	void updateVelocity(double x, double y, double z)
	{
		params->velocity[0] = x;
		params->velocity[1] = z;
		params->velocity[2] = y;
	}
	void updateOrientation(double x, double y, double z, double p)
	{
		params->orientation[0] = x;
		params->orientation[1] = z;
		params->orientation[2] = y;
		params->orientation[3] = p;
	}
	void updateGain(double gain)
	{
		params->gain = gain;
	}
	void updateField(int fields)
	{
		params->fields = fields;
	}
	void updateTimestamp(double timestamp)
	{
		params->timestamp = timestamp;
	}
	void destroy()
	{
		snd.del_host(id);
	}
	int addSource(SND_PlayMode playMode, const Proto& proto)
	{
		std::unique_ptr<SoundSource> src = std::make_unique<SoundSource>(snd, id, playMode, proto);
		SND_Source_id sourceId = src->getSrcId();
		if (sourceId != SND_HOST_ID_NONE)
		{
			sndSources.push_back(std::move(src));
			int srcId = sndSources.size() - 1;
			wavMap[proto.path] = srcId;
			return srcId;
		}
		return SND_HOST_ID_NONE;
	}
	SoundSource& getSource(Proto proto)
	{
		return *sndSources[wavMap[proto.path]];
	}
	int getSourceIndex(const Proto& proto)
	{
		return wavMap[proto.path];
	}
	SoundSource& getSource(int srcId)
	{
		return *sndSources[srcId];
	}
	void update(double dt, Vec3 worldPosition, Vec3 localSpeed, double timestamp, Quaternion& quaternion)
	{
		if (ctx == snd.WORLD_CONTEXT)
		{
			params->position[0] = worldPosition.x;
			params->position[1] = worldPosition.y;
			params->position[2] = worldPosition.z;
			params->orientation[0] = quaternion.x;
			params->orientation[1] = quaternion.y;
			params->orientation[2] = quaternion.z;
			params->orientation[3] = quaternion.w;
			params->velocity[0] = localSpeed.x;
			params->velocity[1] = localSpeed.y;
			params->velocity[2] = localSpeed.z;
		}
		for (size_t i = 0; i < sndSources.size(); i++)
		{
			sndSources[i]->update(dt, worldPosition, quaternion);
		}
		params->timestamp = timestamp;
		snd.update_host(id, params.get());
	}
private:
	SND_Host_id id = SND_HOST_ID_NONE;
	Sound& snd;
	std::unique_ptr<SND_HostParams> params;
	std::map<std::wstring, int>wavMap;
	std::vector<std::unique_ptr<SoundSource>> sndSources;
};