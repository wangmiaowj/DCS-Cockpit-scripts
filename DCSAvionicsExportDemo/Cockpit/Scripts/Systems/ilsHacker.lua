dofile(LockOn_Options.script_path.."command_defs.lua")
dofile(LockOn_Options.script_path.."Systems/device_header.lua")
dofile(LockOn_Options.script_path.."utils.lua")

local dev = GetSelf()
local ilsPower = 0;
if not StringContains(package.cpath,';'..LockOn_Options.script_path.. '../../bin/?.dll') then
    package.cpath 			= package.cpath..";".. LockOn_Options.script_path.. "../../bin/?.dll"
end
local av = require('avSimplestWeaponSystem')

local update_time_step = 0.02 --每秒50次调用update()函数
make_default_activity(update_time_step)

function post_initialize() --默认初始化函数
    local birth = LockOn_Options.init_conditions.birth_place
    av.init.electric(devices.ELECTRIC)
    av.init.ils(devices.ILS)
    if birth=="GROUND_HOT" or birth=="AIR_HOT" then --"GROUND_COLD","GROUND_HOT","AIR_HOT"
        ilsPower = 1
    elseif birth=="GROUND_COLD" then

    end
    av.ILS.setElectPower(ilsPower)
end

function SetCommand(command,value)
    -- 最基础的航电功能监听
    if command == Keys.ILS_POWER then
        ilsPower = 1 - ilsPower
        av.ILS.setElectPower(ilsPower)
    end
end

local function setFreq(freq)
    av.ILS.setFreq(freq)--111.5
end

function update() --刷新状态
    local localizerFreq = av.ILS.getLocalizerFreq()
    -- localizerFreq = 111500000
    local glideslopeFreq = av.ILS.getGlideslopeFreq(localizerFreq)
    local isLocalizerValid = av.ILS.isLocalizerValid()
    local isGlideslopeValid = av.ILS.isGlideslopeValid()
    local localizerDeviation = av.ILS.getLocalizerDeviation()
    local glideslopeDeviation = av.ILS.getGlideslopeDeviation()
    local isInnerMarkerSignal = av.ILS.isInnerMarkerSignal()
    local isMiddleMarkerSignal = av.ILS.isMiddleMarkerSignal()
    local isOuterMarkerSignal = av.ILS.isOuterMarkerSignal()
    local isMarkerBeacon = av.ILS.isMarkerBeacon()
end

need_to_be_closed = false 