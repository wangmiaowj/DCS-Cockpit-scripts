dofile(LockOn_Options.script_path .. "devices.lua")
creators                           = {}
creators[devices.ELECTRIC]  = { "avSimpleElectricSystem", LockOn_Options.script_path .."Systems/electric_system.lua" }
creators[devices.ILS]              = { "avILS", LockOn_Options.script_path .. "Systems/ils.lua", { devices.ELECTRIC } }
creators[devices.UHF_RADIO]        = { "avUHF_ARC_164v2", LockOn_Options.script_path .. "radio/uhf_radio.lua",{devices.ELECTRIC} }
creators[devices.VHF_AM_RADIO]     = { "avVHF_ARC_186",LockOn_Options.script_path .. "radio/vhf_am_radio.lua",{devices.ELECTRIC},
    LockOn_Options.script_path .. "radio/Radio_commands.lua"
}
creators[devices.VHF_FM_RADIO]     = { "avVHF_ARC_186",LockOn_Options.script_path .. "radio/vhf_fm_radio.lua",{'elec_system', devices.ELECTRIC_SYSTEM},
    LockOn_Options.script_path .. "radio/Radio_commands.lua" }
creators[devices.INTERCOM]         = { "avIntercomV2",LockOn_Options.script_path .. "radio/Intercom.lua",
    {
        devices.ELECTRIC,
        devices.UHF_RADIO,
        devices.VHF_AM_RADIO,
        devices.VHF_FM_RADIO,
        devices.ILS
    }
}
creators[devices.RADIO_HACKER]     = { "avLuaDevice", LockOn_Options.script_path .. "radio/radioHacker.lua" }
creators[devices.ILS_HACKER]       = { "avLuaDevice", LockOn_Options.script_path .. "Systems/ilsHacker.lua" }
creators[devices.CLOCK]            = { "avA11Clock" }
creators[devices.SND]              = { "avLuaDevice", LockOn_Options.script_path .. "Systems/sounder.lua" }