dofile(LockOn_Options.script_path.."command_defs.lua")
dofile(LockOn_Options.script_path.."devices.lua")
dofile(LockOn_Options.script_path.."utils.lua")

if not StringContains(package.cpath,';'..LockOn_Options.script_path.. '../../bin/?.dll') then
    package.cpath 			= package.cpath..";".. LockOn_Options.script_path.. "../../bin/?.dll"
end
local av = require('DCSAvionicsExport')
local uhfPowerStatus = 0
local vhfPowerStatus = 0

local update_time_step = 1  --每秒50次刷新
make_default_activity(update_time_step)

local dev = GetSelf()
local UHF_dev = GetDevice(devices.UHF_RADIO)
local VHF_AM_dev = GetDevice(devices.VHF_RADIO_AM)
local VHF_FM_dev = GetDevice(devices.VHF_RADIO_FM)

function post_initialize()
    av.init.electric(devices.ELECTRIC)
    av.init.uhf(devices.UHF_RADIO)
    av.init.vhf(devices.VHF_RADIO_AM,0)--AM
    av.init.vhf(devices.VHF_RADIO_FM,1)--FM
    av.init.intercom(devices.INTERCOM)
    if birth=="GROUND_HOT" or birth=="AIR_HOT" then --"GROUND_COLD","GROUND_HOT","AIR_HOT"
        uhfPowerStatus = 1
        vhfPowerStatus = 1
    elseif birth=="GROUND_COLD" then

    end
    av.UHF.setElectPower(uhfPowerStatus)
    av.VHF.setElectPower(vhfPowerStatus)
end

function SetCommand(command,value)
	if command==Keys.UHF_PIT then
        av.UHF.pushTalk()
    elseif command==Keys.VHF_PIT then
        av.VHF.pushTalk()
    end
end

local function setUHF_Freq(freq)
    av.UHF.setFreq(freq)
    --or 或者
    UHF_dev:set_frequency(freq)
end
local function setVHF_Freq(freq)
    av.VHF.setFreq(freq)
    --or 或者
    if av.VHF.isFM() then
        VHF_FM_dev:set_frequency(freq)
    else
        VHF_AM_dev:set_frequency(freq)
    end
end
local function setUHF_Volume(volume)
    av.UHF.setVolume(volume)
end
local function setVHF_Volume(volume)
    av.VHF.setVolume(volume)
end

function update()
    local isFM = av.VHF.isFM()
    ----------------------------------------
    local uhfFreq = av.UHF.getFreq()
    -- or 或者
    local uhfFreq = UHF_dev:get_frequency()
    ----------------------------------------
    local vhfFreq = av.VHF.getFreq()
    -- or 或者
    local vhfFreq
    if isFM then
        vhfFreq = VHF_FM_dev:get_frequency()
    else
        vhfFreq = VHF_AM_dev:get_frequency()
    end
    ----------------------------------------
end

need_to_be_closed = false
