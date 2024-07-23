[English](README.md) | [简体中文](README_zh-CN.md) 
DCSAvionicsExport.dll was developed to solve the problem that the functions of avionics equipment cannot be used in the Lua environment. These functions can only be called in C++. The following are the functions available in this dll
# Assume the mod structure is like this
# bin
#   DCSAvionicsExport.dll
#   EFM.dll
# Cockpit
#   Scripts
#       Systems
#           demo.lua
#       device_init.lua
#
# in demo.lua
```lua
package.cpath = package.cpath..';'..LockOn_Options.script_path..'../../bin/?.dll'
local av = require('DCSAvionicsExport')
```
# The following is the structure of av
```
av = {
    init = {
        ils = function(deviceId),--The corresponding DCS device class is avILS
        electric = function(deviceId),--The corresponding DCS device class is avSimpleElectricSystem
        intercom = function(deviceId),--The corresponding DCS device class is avIntercomV2 and avIntercom
        vhf = function(deviceId,isFM),--The corresponding DCS device class is avVHF_ARC_186
        uhf = function(deviceId),--The corresponding DCS device class is avUHF_ARC_164和avUHF_ARC_164v2
        a11Clock = function(deviceId)--The corresponding DCS device class is avA11Clock
    },
    UHF = {
        setFreq = function(freq),--Set the UHF radio frequency. In the lua environment, GetDevice(devices.UHF_RADIO):set_frequency(freq) can also achieve the corresponding effect.
        getFreq = function(),--Get the UHF radio frequency. In the lua environment, GetDevice(devices.UHF_RADIO):get_frequency(freq) can also achieve the corresponding effect.
        --Note that the frequency units of the above two functions are Hz instead of MHz
        setVolume = function(volume),--Set the UHF radio volume, the parameter range is 0-1
        pushTalk = function(),--Calling using UHF radio
        setElectPower = function(onOff)--Set the power switch of the UHF radio. The parameters are 0 and 1. 0 represents power off and 1 represents power on (requires support from the electric system)
    },
    VHF = {
        setFM = function(),--Switch your VHF radio to FM
        setAM = function(),--Switch your VHF radio to AM
        --The above two functions are only for you to create two VHF, one is FM (30MHz-108MHz), one is AM (116MHz-151.95MHz). If you only create one VHF and want to switch back and forth between FM and AM, please use GetDevice(devices.VHF_RADIO):set_modulation(MODULATION_AM) parameter values ​​can be MODULATION_AM, MODULATION_FM, MODULATION_AM_AND_FM, UHF radio is also applicable
        --MODULATION_AM = 0
        --MODULATION_FM = 1
        --MODULATION_AM_AND_FM = 2
        setFreq = function(freq),
        getFreq = function(),
        setVolume = function(volume),
        pushTalk = function(),
        setElectPower = function(onOff),
        --Same as UHF
        isFM = function()--For two VHF radios created, returns whether the VHF FM station is being used. Return value type: bool
    },
    ILS = {
        setFreq = function(freq),--Set the frequency of the ILS device in MHz
        getGlideslopeFreq = function(freq),--Get the frequency of the glideslope beacon for the specified ILS localizer frequency. The unit of parameter freq is Hz
        getLocalizerFreq = function(),--Get the current frequency of the ILS device in Hz
        isLocalizerValid = function(),--Check whether the ILS device has captured the ILS localizer beacon, return value type: bool
        isGlideslopeValid = function(),--Check whether the ILS device has captured the ILS glideslope beacon, return value type: bool
        getLocalizerDeviation = function(),--Get the ILS localizer center offset, return value unit: radian
        getGlideslopeDeviation = function(),--Get the ILS glideslope offset, return value unit: radian
        isInnerMarkerSignal = function(),--Check whether the ILS inner marker signal is received, return value type: bool, if true is returned, the ILS will emit a long, long, long, long Morse code sound
        isMiddleMarkerSignal = function(),--Check whether the ILS middle marker signal is received, return value type: bool, if true is returned, the ILS will emit short, long, short, long Morse code sounds
        isOuterMarkerSignal = function(),--Checks whether the ILS outer marker signal is received. Return value type: bool. If true is returned, the ILS will emit a short, short, short, short Morse code sound.
        isMarkerBeacon = function(),--Check whether the final ILS beacon signal is received. Return value type: bool. May be used for decision altitude? When I land according to the ILS guidance, the ground altitude is less than 100 meters. This function will return true, and the ILS will make a beeping sound.
        setElectPower = function(onOff),--Set the power of the ILS device. The parameters are 0 and 1. 0 represents power off and 1 represents power on (requires support from the electric system)
    },
    snd = {
        addHost = function(hostName,context,px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp),--Create a sounder host and return the created host id
        --hostName:string,sounder host name
        --context:string,sounder type,parameter values ​​can be UI,HEADPHONES,COCKPIT_3D,WORLD_3D,COCKPIT_2D and WORLD_2D
        --px,py,pz:double,The x, y, z position of the sounder host, in meters
        --Optional parameters:
        --vx,vy,vz:double,The velocity vector xyz of the sound generator host, in meters per second
        --qx,qy,qz,qw:double,Quaternion universal angle of the sound generator, in radians (should be...)
        --timestamp:double,I don't know what the timestamp is for.
        
        updateHost = function(hostId,dt,px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp),--update parameters of a host
        -- hostId: int, the ID of the created host  
        -- dt: double, the update time interval, must match the value passed to the make_default_activity(update_time_step) function in the lua environment  
        -- px, py, pz: double, the x, y, z position of the sound emitter host in meters  
        -- Optional parameters:  
        -- vx, vy, vz: double, the velocity vector of the sound emitter host in meters per second  
        -- qx, qy, qz, qw: double, the quaternion orientation of the sound emitter in radians (presumably)  
        -- timestamp: double, the timestamp, purpose unclear  

        delHost = function(hostId),--delete a specified sound emitter,
        addSrc = function(hostId,proto,sndLength,radius,pitch,lowpass),--create a sound source and return its ID
        -- hostId: int, the ID of the sound emitter host  
        -- proto: string, the path to the sound sdef file, relative to the sounds/sdef folder  
        -- Optional parameters:  
        -- sndLength: double, the length of the audio file, default -1  
        -- The following 3 parameters are likely not frequently used:  
        -- radius: double, the radius of influence of the sound source, default 1000  
        -- pitch: double, pitch shift, default 1  
        -- lowpass: double, the lowest frequency to play, sound below this frequency will not play ,default 24000

        addSrcAlt = function(hostId,proto,altProto,sndLength,radius,pitch,lowpass),--create a sound source and return its ID
        -- hostId: int, the ID of the sound emitter host  
        -- proto: string, the path to the sound sdef file, relative to the sounds/sdef folder  
        -- altProto: string, an alternative path to the sound sdef file, relative to the sounds/sdef folder (Unclear difference from addSrc)  
        -- Optional parameters:  
        -- sndLength: double, the length of the sound file, default -1  
        -- The following 3 parameters are likely not frequently used:  
        -- radius: double, the radius of influence of the sound source, default 1000  
        -- pitch: double, pitch shift, default 1  
        -- lowpass: double, the lowest frequency to play, sound below this frequency will not play ,default 24000

        delSrc = function(srcId),--delete a specified sound source
        isPlaying = function(srcId),--check if a sound source is playing, returns a boolean
        srcLink = function(srcId1,srcId2),--link two sound sources, causing them to synchronize playback states, often used for cockpit and external sound synchronization
        srcUnlink = function(srcId),--unlink a specified sound source, stopping playback state synchronization
        playOnce = function(srcId),--play a specified sound source once, if sndLength is passed to addSrc and the cumulative effect of dt passed to updateHost exceeds sndLength, playback will stop
        playLoop = function(srcId),--loop a specified sound source
        stop = function(srcId),--stop playback of a specified sound source
        --The following functions might be considered as potentially unnecessary or specific to a certain sound manipulation context:
        setSrcGain = function(srcId,gain),--Sets the volume gain for a specified sound source
        --srcId:int,id of the sound source
        --gain:double,The volume gain factor

        setSrcPitch = function(srcId,pitch),--Sets the pitch shift for a specified sound source
        --srcId:int,The ID of the sound source
        --pitch:double,The volume pitch factor

        setSrcLowpass = function(srcId,lowpass),--Sets the low-pass filter cutoff frequency for a specified sound source
        --srcId:int,The ID of the sound source
        --lowpass:double,The cutoff frequency for the low-pass filter, in Hz

        setSrcRadius = function(srcId,radius),--Sets the influence radius for a specified sound source
        --srcId:int,The ID of the sound source
        --radius:double,The influence radius, in meters

        setListenerGain = function(gain),--Sets the volume gain for the listener
        setListenerPitch = function(pitch),--Sets the pitch shift for the listener
        setListenerLowpass = function(lowpass),--Sets the low-pass filter cutoff frequency for the listener
    }
}
```
[demo code](/DCSAvionicsExportDemo/Cockpit/Scripts/)