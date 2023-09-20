dofile(LockOn_Options.common_script_path.."devices_defs.lua")
dofile(LockOn_Options.common_script_path.."ViewportHandling.lua")

indicator_type       = indicator_types.COMMON--指示器类型
init_pageID     = 1--初始化的页码ID
purposes 	   = {render_purpose.GENERAL,render_purpose.HUD_ONLY_VIEW}--在哪里显示
--可用的值
--[[
    GENERAL,常规在座舱空间显示
    HUD_ONLY_VIEW，仅HUD视角显示，LAlt+F1的视角
    SCREENSPACE_INSIDE_COCKPIT，座舱视角显示，以屏幕定位
    SCREENSPACE_OUTSIDE_COCKPIT，座舱外显示，以屏幕定位
    GROUND_UNIT_OPERATOR，地面单位视角显示？
    GROUND_UNIT_OPERATOR_SCREENSPACE，地面单位操作员视角显示？屏幕空间定位
    AUXILLARY_SIGHT，未知
    AUXILLARY_SIGHT_SCREENSPACE，未知
    GENERAL_AFTER_POSTEFFECTS，未知
    HUD_ONLY_VIEW_AFTER_POSTEFFECTS
    BAKE
--]]
--subset ids
BASE    = 1
INDICATOR = 2

page_subsets  = {
[BASE]    		= LockOn_Options.script_path.."Indicators/Demo/Indicator/base_page.lua",
[INDICATOR]    		= LockOn_Options.script_path.."Indicators/Demo/Indicator/indicator.lua",
}
pages = 
{
	{
	 BASE,
	 INDICATOR,
	 },
}
