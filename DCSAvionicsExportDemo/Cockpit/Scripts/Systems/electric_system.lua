dofile(LockOn_Options.script_path.."command_defs.lua")
dofile(LockOn_Options.script_path.."Systems/device_header.lua")
dofile(LockOn_Options.script_path.."utils.lua")

local electric_system = GetSelf()
local battStatus = 0
local ac1GenStatus = 0
local ac2GenStatus = 0

local update_time_step = 0.02 --每秒50次调用update()函数
make_default_activity(update_time_step)

electric_system:listen_event(CptEvntNames.gndPwrOn)
electric_system:listen_event(CptEvntNames.gndPwrOff)

function post_initialize() --默认初始化函数
    local birth = LockOn_Options.init_conditions.birth_place
    if birth=="GROUND_HOT" or birth=="AIR_HOT" then --"GROUND_COLD","GROUND_HOT","AIR_HOT"
        battStatus = 1
        ac1GenStatus = 1
        ac2GenStatus = 1
    elseif birth=="GROUND_COLD" then
        
    end
    electric_system:DC_Battery_on(battStatus)
    electric_system:AC_Generator_1_on(ac1GenStatus)
    electric_system:AC_Generator_2_on(ac2GenStatus)
end

function SetCommand(command,value)
    -- 最基础的航电功能监听
    if command == Keys.BATT then
        battStatus = 1 - battStatus
        electric_system:DC_Battery_on(battStatus)
    elseif command == Keys.AC_GEN1 then
        ac1GenStatus = 1 - ac1GenStatus
        electric_system:AC_Generator_1_on(ac1GenStatus)
    elseif command == Keys.AC_GEN2 then
        ac2GenStatus = 1 - ac2GenStatus
        electric_system:AC_Generator_2_on(ac2GenStatus)
    end
end

function update() --刷新状态
    
end

function CockpitEvent(event, val)
    if event == "GroundPowerOn" then
        
    elseif event == "GroundPowerOff" then
        
    end
end

need_to_be_closed = false 