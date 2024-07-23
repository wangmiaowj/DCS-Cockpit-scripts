dofile(LockOn_Options.script_path.."command_defs.lua")
dofile(LockOn_Options.script_path.."utils.lua")

local dev = GetSelf()
local sensorData = get_base_data()

local update_time_step = 0.02 --每秒50次调用update()函数
make_default_activity(update_time_step)
if not StringContains(package.cpath,';'..LockOn_Options.script_path.. '../../bin/?.dll') then
    package.cpath 			= package.cpath..";".. LockOn_Options.script_path.. "../../bin/?.dll"
end
local av = require('avSimplestWeaponSystem')

local cockpit3dHost
local cockpit2dHost
local aircraftHost
local world2dHost
local uiHost
local testSoundSource_aircraft
local testSoundSource_cockpit

function post_initialize() --默认初始化函数
    --添加主机
    cockpit2dHost = av.snd.addHost('CPT_2D_HOST','COCKPIT_2D',0,0,0)
    -------------------------------主机名---------主机类型----x,y,z
    cockpit3dHost = av.snd.addHost('CPT_3D_HOST','COCKPIT_3D',0,0,0)
    local px,py,pz = sensorData:getSelfCoordinates()--获取飞机自身坐标，以米为单位,返回经度,高度,纬度
    local vx,vy,vz = sensorData:getSelfVelocity()--获取飞机自身速度的向量,以米每秒为单位,返回x,y,z三个向量速度,注意，x,y,z的向量方向以世界为参考系而不是飞机自身
    local qx,qy,qz,qw = 0,0,0,0--角度四元数
    local timestamp = get_absolute_model_time()
    aircraftHost = av.snd.addHost('AIRCRAFT_HOST','WORLD_3D',px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp)
    world2dHost = av.snd.addHost('WORLD_2D_HOST','WORLD_2D',0,0,0)
    uiHost = av.snd.addHost('UI_HOST','UI',0,0,0)
    --删除主机
    --av.snd.delHost(uiHost)
    
    --添加音源
    testSoundSource_aircraft = av.snd.addSrc(aircraftHost,'music/Rammstein - Feuer Frei! (Rammstein Vs Junkie XL Remix)',4*60+10)
    testSoundSource_cockpit = av.snd.addSrc(cockpit3dHost,'music/Rammstein - Feuer Frei! (Rammstein Vs Junkie XL Remix)',4*60+10)
    --删除音源
    --av.snd.delSrc(testSoundSource_aircraft)

    --关联座舱内和座舱外的音源
    av.snd.srcLink(testSoundSource_aircraft,testSoundSource_cockpit)
    --解除关联音源
    --av.snd.srcUnlink(testSoundSource_aircraft)

    --仅播放一次音源
    av.snd.playOnce(testSoundSource_aircraft)
    --循环播放音源
    --av.snd.playLoop(testSoundSource_aircraft)
    --停止播放音源
    --av.snd.stop(testSoundSource_aircraft)
    --检测音源是否正在播放，如果播放将它停止
    -- if av.snd.isPlaying(testSoundSource_aircraft) then
    --     av.snd.stop(testSoundSource_aircraft)
    -- end
end

function SetCommand(command,value)
    
end

function update() --刷新状态
    local px,py,pz = sensorData:getSelfCoordinates()--获取飞机自身坐标，以米为单位,返回经度,高度,纬度
    local vx,vy,vz = sensorData:getSelfVelocity()--获取飞机自身速度的向量,以米每秒为单位,返回x,y,z三个向量速度,注意，x,y,z的向量方向以世界为参考系而不是飞机自身
    local qx,qy,qz,qw = 0,0,0,0--角度四元数
    local timestamp = get_absolute_model_time()
    --更新主机参数，仅针对于WORLD_3D的主机
    av.snd.updateHost(aircraftHost,update_time_step,px,py,pz,vx,vy,vz,qx,qy,qz,qw,timestamp)
end

function CockpitEvent(event, val)
    
end

need_to_be_closed = false 