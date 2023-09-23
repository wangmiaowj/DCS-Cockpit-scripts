dofile(LockOn_Options.script_path.."Indicators/Demo/Indicator/definitions.lua")
IGNORE_BRT = true--如果赋值true则下面页面元素不会自动添加亮度控制器，直到重新赋值为false
BRTName = 'Other BrtName'--如果这个全局变量不为空，BRTName将代替IndicatorName生成的亮度控制器名字,用于单独控制该页面的某个元素亮度，单独控制亮度的元素创建完成后请将该变量赋值为nil
PAGE_NAME = 'BASE'--页面名字，要和pages_def.lua的Pages的键名一致
IS_HUD = false--显示器是否为HUD，BASE页面禁止申明或者赋值为true
dofile(LockOn_Options.script_path.."Indicators/common_base_page.lua")

-----------------------------------------------------------------------------------------------------------------------------------
--your indicator code 你的指示器代码