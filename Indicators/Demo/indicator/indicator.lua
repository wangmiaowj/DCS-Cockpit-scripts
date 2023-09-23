dofile(LockOn_Options.script_path.."Indicators/Demo/Indicator/definitions.lua")
IGNORE_BRT = true--如果赋值true则下面页面元素不会自动添加亮度控制器，直到重新赋值为false
BRTName = 'Other BrtName'--如果这个全局变量不为空，BRTName将代替IndicatorName生成的亮度控制器名字,用于单独控制该页面的某个元素亮度，单独控制亮度的元素创建完成后请将该变量赋值为nil
PAGE_NAME = 'INDICATOR'--页面名字，要和pages_def.lua的命名一致
IS_HUD = true--显示器是否为HUD，BASE页面禁止申明或者赋值为true

-----------------------------------------------------------------------------------------------------------------------------------
--your indicator code 你的指示器代码
local baseSimple = AddSimple()

AddBox(nil,0.1*Width,0.1*Height,nil,nil,MakeMaterial(nil, { 0,60,80, 255 }),nil,nil,baseSimple)
--完整参数
--AddBox('name',0.1*Width,0.1*Height,{0,0},{0,0},MakeMaterial(nil, { 0,60,80, 255 }),DEFAULT_LEVEL,COMPARE,baseSimple,nil,nil,nil)