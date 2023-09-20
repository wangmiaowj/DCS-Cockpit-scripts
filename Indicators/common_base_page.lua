local base_sim          = AddSimple()

AddBox(nil,Width,Height,nil,nil,MakeMaterial(nil, { 128, 0, 0, 32 }),DEFAULT_NOCLIP_LEVEL,REWRITE_LEVEL,base_sim,nil,nil,true)
AddBox(nil,Width,Height,nil,nil,MakeMaterial(nil, { 0, 0, 0, 255 }),DEFAULT_NOCLIP_LEVEL,INCREASE_IF_LEVEL,base_sim)