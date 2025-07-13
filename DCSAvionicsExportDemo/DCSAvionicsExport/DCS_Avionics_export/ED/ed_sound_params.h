#ifndef _ED_SOUND_PARAMS_H_
#define _ED_SOUND_PARAMS_H_

enum SND_Params {
    SND_POSITION          = 0x0001,
    SND_ORIENTATION       = 0x0002,
    SND_VELOCITY          = 0x0004,
    SND_RADIUS            = 0x0008,
    SND_GAIN              = 0x0010,
    SND_PITCH             = 0x0020,
    SND_LOWPASS           = 0x0040,

    SND_TIMESTAMP         = 0x8000,

    SND_PLAYMODE          = 0x01000000,
    SND_OFFSET            = 0x02000000,
    SND_PLAYLIST          = 0x04000000,

    SND_HOST_PARAMS       = SND_POSITION | SND_ORIENTATION | SND_VELOCITY | SND_GAIN | SND_TIMESTAMP,
    SND_LISTENER_PARAMS   = SND_POSITION | SND_ORIENTATION | SND_VELOCITY | SND_GAIN |
                            SND_PITCH | SND_LOWPASS | SND_TIMESTAMP,
    SND_SOURCE_PARAMS     = SND_POSITION | SND_ORIENTATION | SND_GAIN | SND_PITCH | SND_LOWPASS | SND_RADIUS,
    SND_PLAY_PARAMS       = SND_PLAYMODE | SND_OFFSET | SND_PLAYLIST | SND_TIMESTAMP,
};

#define SND_CUTOFF_MIN (24.0f)
#define SND_CUTOFF_MAX (24000.0f)

enum SND_PlayMode {
    SND_PLAYMODE_ONCE,
    SND_PLAYMODE_LOOPED,
    SND_PLAYMODE_TRIGGER,
    SND_PLAYMODE_LIVE
};

struct SND_HostParams {
    int fields;

    double position[3];
    double orientation[4];
    double velocity[3];
    float  gain;
    double timestamp;
};

struct SND_ListenerParams {
    int fields;

    double position[3];
    double orientation[4];
    double velocity[3];
    float  gain;
    float  pitch;
    float  lowpass;
    double timestamp;
};

struct SND_SourceParams {
    int fields;

    double position[3];
    double orientation[4];
    float  gain;
    float  pitch;
    float  radius;
    float  lowpass;
};

struct SND_PlayParams {
    int fields;

    int        playmode;
    float      offset;
    double     timestamp;
    const char **playlist; // NULL terminated array of zero-terminated strings
};

#endif /* _ED_SOUND_PARAMS_H_ */
