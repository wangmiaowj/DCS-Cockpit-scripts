[English](README.md) | [简体中文](README_zh-CN.md) 
DCSAvionicsExport.dll是为了解决lua环境不可使用的航空电子设备的函数而开发出的，这些函数只能在c++进行调用。下面说明这个dll可用的函数
# 假设模组的结构是这样的
# bin
#   DCSAvionicsExport.dll
#   EFM.dll
# Cockpit
#   Scripts
#       Systems
#           demo.lua
#       device_init.lua
#
# 在demo.lua中
```lua
package.cpath = package.cpath..';'..LockOn_Options.script_path..'../../bin/?.dll'
local av = require('DCSAvionicsExport')
```
# 以下是av的结构
```
av = {
    init = {
        ils = function(deviceId),--对应的DCS设备类是avILS
        electric = function(deviceId),--对应的DCS设备类是avSimpleElectricSystem
        intercom = function(deviceId),--对应的DCS设备类是avIntercomV2和avIntercom
        vhf = function(deviceId,isFM),--对应的DCS设备类是avVHF_ARC_186
        uhf = function(deviceId),--对应的DCS设备类是avUHF_ARC_164和avUHF_ARC_164v2
        a11Clock = function(deviceId)--对应的DCS设备类是avA11Clock
    },
    UHF = {
        setFreq = function(freq),--设置UHF无线电频率,在lua环境GetDevice(devices.UHF_RADIO):set_frequency(freq)也可达到对应效果
        getFreq = function(),--获取UHF无线电频率,在lua环境GetDevice(devices.UHF_RADIO):get_frequency(freq)也可达到对应效果
        --注意上面2个函数的频率单位是赫兹而不是兆赫兹
        setVolume = function(volume),--设置UHF无线电音量,参数范围是0-1
        pushTalk = function(),--使用UHF无线电进行呼叫
        setElectPower = function(onOff)--设置UHF无线电的电力开关,参数是0和1,0代表断电,1代表通电(需要电力系统的支持)
    },
    VHF = {
        setFM = function(),--将VHF无线电切换到FM
        setAM = function(),--将VHF无线电切换到AM
        --上面2个函数是仅针对于你创建了2个VHF，一个是FM(30MHz-108MHz)，一个是AM(116MHz-151.95MHz),如果你只创建了一个VHF并且想在FM和AM来回切换，请使用境GetDevice(devices.VHF_RADIO):set_modulation(MODULATION_AM)参数值可用MODULATION_AM,MODULATION_FM,MODULATION_AM_AND_FM,UHF无线电也同样适用
        --MODULATION_AM = 0
        --MODULATION_FM = 1
        --MODULATION_AM_AND_FM = 2
        setFreq = function(freq),
        getFreq = function(),
        setVolume = function(volume),
        pushTalk = function(),
        setElectPower = function(onOff),
        --和UHF一样
        isFM = function()--针对于创建了2个VHF无线电，返回是否正在使用VHF的FM电台,返回值类型:bool
    },
    ILS = {
        setFreq = function(freq),--设置ILS设备的频率,单位是兆赫兹
        getGlideslopeFreq = function(freq),--获取指定ILS定位器频率的下滑道信标的频率,参数freq的单位是赫兹
        getLocalizerFreq = function(),--获取ILS设备当前的频率,单位赫兹
        isLocalizerValid = function(),--ILS设备是否捕获到ILS定位器信标,返回值类型:bool
        isGlideslopeValid = function(),--ILS设备是否捕获到ILS下滑道信标,返回值类型:bool
        getLocalizerDeviation = function(),--获取ILS的航向道中心偏移量,返回值单位:弧度
        getGlideslopeDeviation = function(),--获取ILS的下滑道偏移量,返回值单位:弧度
        isInnerMarkerSignal = function(),--是否接收到ILS内指点标信号,返回值类型:bool,返回true时ILS会发出长，长，长，长的摩斯电码声
        isMiddleMarkerSignal = function(),--是否接收到ILS中指点标信号,返回值类型:bool,返回true时ILS会发出短，长，短，长的摩斯电码声
        isOuterMarkerSignal = function(),--是否接收到ILS外指点标信号,返回值类型:bool,返回true时ILS会发出短，短，短，短的摩斯电码声
        isMarkerBeacon = function(),--是否接收到最终ILS指点标信号,,返回值类型:bool,可能用于决断高度?当我按照ILS引导降落的过程中，地面高度低于100米时该函数就会返回true，同时ILS发出滴滴滴的响声
        setElectPower = function(onOff),--设置ILS设备的电力,参数是0和1,0代表断电,1代表通电(需要电力系统的支持)
    },
    snd = {
        addHost = function(hostName,context,px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp),--创建一个发声器的主机,返回已创建的主机id
        --hostName:string,发声器主机名
        --context:string,发声器类型,可用值有:UI,HEADPHONES,COCKPIT_3D,WORLD_3D,COCKPIT_2D,WORLD_2D
        --px,py,pz:double,发声器主机的x,y,z位置,单位米
        --以下是可选参数
        --vx,vy,vz:double,发声器主机的速度向量xyz,单位米每秒
        --qx,qy,qz,qw:double,发声器的四元数万向角,单位弧度(应该是...)
        --timestamp:double,时间戳,我也不知道有什么用
        
        updateHost = function(hostId,dt,px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp),--更新主机的参数
        --hostId:int,已创建的主机id
        --dt:double,更新时间间隔,必须与lua环境的make_default_activity(update_time_step)函数传递的值一致
        --px,py,pz:double,发声器主机的x,y,z位置,单位米
        --以下是可选参数
        --vx,vy,vz:double,发声器主机的速度向量xyz,单位米每秒
        --qx,qy,qz,qw:double,发声器的四元数万向角,单位弧度(应该是...)
        --timestamp:double,时间戳,我也不知道有什么用

        delHost = function(hostId),--删除指定的发声器,
        addSrc = function(hostId,proto,sndLength,radius,pitch,lowpass),--创建音源,返回已创建的音源id
        --hostId:int,发声器主机id
        --proto:string,音频sdef文件的路径，以sounds/sdef文件夹为根路径
        --以下参数可选
        --sndLength:double,音频文件的长度,默认-1
        --以下3个参数应该没什么用
        --radius:double,音源作用半径,默认1000
        --pitch:double,音高变调，默认1
        --lowpass:double,音频最低频率，如果音频播放的过程中，频率低于指定的最低频率将不会播放

        addSrcAlt = function(hostId,proto,altProto,sndLength,radius,pitch,lowpass),--创建音源,返回已创建的音源id
        --hostId:int,发声器主机id
        --proto:string,音频sdef文件的路径，以sounds/sdef文件夹为根路径
        --altProto:string,音频sdef文件的路径，以sounds/sdef文件夹为根路径(我不知道这个函数与addSrc有什么区别)
        --以下参数可选
        --sndLength:double,音频文件的长度,默认-1
        --以下3个参数应该没什么用
        --radius:double,音源作用半径,默认1000
        --pitch:double,音高变调，默认1
        --lowpass:double,音频最低频率，如果音频播放的过程中，频率低于指定的最低频率将不会播放

        delSrc = function(srcId),--删除指定的音源
        isPlaying = function(srcId),--检测音源是否在播放,返回值bool
        srcLink = function(srcId1,srcId2),--关联音源,关联后将会同步播放状态，常用于座舱内与座舱外的音频同步
        srcUnlink = function(srcId),--解除关联指定的音源,解除关联后将不会同步播放状态
        playOnce = function(srcId),--播放一次指定的音源,如果调用函数addSrc传递了sndLength,在调用updateHost函数传递的参数dt的累计影响下，如果播放时间超过sndLength将会停止播放
        playLoop = function(srcId),--循环播放指定的音源
        stop = function(srcId),--停止播放指定的音源
        --以下函数可能是无用的函数
        setSrcGain = function(srcId,gain),--设置指定音源的音量增益
        --srcId:int,音源id
        --gain:double,音量增益

        setSrcPitch = function(srcId,pitch),--设置指定音源的音高增益
        --srcId:int,音源id
        --pitch:double,音高增益

        setSrcLowpass = function(srcId,lowpass),--设置指定音源的最低播放频率
        --srcId:int,音源id
        --lowpass:double,最低播放频率，单位赫兹

        setSrcRadius = function(srcId,radius),--设置指定音源的作用半径
        --srcId:int,音源id
        --radius:double,作用半径,单位米

        setListenerGain = function(gain),--设置监听器的音量增益
        setListenerPitch = function(pitch),--设置监听器的音高增益
        setListenerLowpass = function(lowpass),--设置监听器的最低播放频率
    }
}
```
[代码示例](/DCSAvionicsExportDemo/Cockpit/Scripts/)