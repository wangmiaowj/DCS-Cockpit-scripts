dofile(LockOn_Options.script_path.."devices.lua")
dofile(LockOn_Options.script_path.."command_defs.lua")
dofile(LockOn_Options.script_path.."utils.lua")
local dev 	    = GetSelf()

local update_time_step = 1 --update will be called once per second

if make_default_activity then
    make_default_activity(update_time_step)
end

GUI = {
	interphone = {
		interphone = true,
		displayName = "Interphone"
	}
}

function update()
end
local classPtr_h = get_param_handle('INTERCOM_PTR')
function post_initialize()
    --dev:set_communicator(devices.UHF_RADIO)
    --dev:set_communicator(devices.VHF_AM_RADIO)
    --dev:make_setup_for_communicator()
    classPtr_h:set(string.sub(tostring(dev.link),10))
end

function SetCommand(command,value)
    print_message_to_user("SetCommand in intercom: "..tostring(command).."="..tostring(value))
end
  

need_to_be_closed = true -- close lua state after initialization
