dofile(LockOn_Options.common_script_path .. "elements_defs.lua")
SetScale(FOV)

DEFAULT_LEVEL = 2
DEFAULT_NOCLIP_LEVEL = DEFAULT_LEVEL - 1
DEFAULT_MASK_LEVEL = DEFAULT_LEVEL + 1

Aspect = GetAspect()
Width = 1
Height = Width * Aspect

REWRITE_LEVEL = h_clip_relations.REWRITE_LEVEL
INCREASE_LEVEL = h_clip_relations.INCREASE_LEVEL
COMPARE = h_clip_relations.COMPARE
INCREASE_IF_LEVEL = h_clip_relations.INCREASE_IF_LEVEL
DECREASE_LEVEL = h_clip_relations.DECREASE_LEVEL
DECREASE_IF_LEVEL = h_clip_relations.DECREASE_IF_LEVEL

AnimalControllor = {
	changeColorWhenParameterEqualToNumber = "change_color_when_parameter_equal_to_number",
	textUsingParameter = "text_using_parameter",
	moveLeftRightUsingParameter = "move_left_right_using_parameter",
	moveUpDownUsingParameter = "move_up_down_using_parameter",
	opacityUsingParameter = "opacity_using_parameter",
	rotateUsingParameter = "rotate_using_parameter",
	compareParameters = "compare_parameters",
	parameterInRange = "parameter_in_range",
	parameterCompareWithNumber = "parameter_compare_with_number",
	lineObjectSetPointUsingParameters = "line_object_set_point_using_parameters",
	scale = "scale",
	--changeTextureStateUsingParameter = "change_texture_state_using_parameter",
	--changeColorUsingParameter = "change_color_using_parameter",
	--fovControl = "fov_control",
	--increaseRenderTargetCounter = "increase_render_target_counter",
}

Alignments={
	CB='CenterBottom',
	CC='CenterCenter',
	CT='CenterTop',
	LB='LeftBottom',
	LC='LeftCenter',
	LT='LeftTop',
	RB='RightBottom',
	RC='RightCenter',
	RT='RightTop'
}

local default_font_size = 0.01
DEFAULT_FONT_SIZE = {}
DEFAULT_FONT_SIZE_2 = {}
for i = 1, 10, 1 do
    DEFAULT_FONT_SIZE[i] = { default_font_size - default_font_size * 0.1 * i, default_font_size - default_font_size * 0.1 * i, 0, 0 }
	DEFAULT_FONT_SIZE_2[i] = { default_font_size - default_font_size * 0.1 * i, (default_font_size - default_font_size * 0.1 * i)*0.5, 0, 0 }
end

function Texure_coord_gen(x_dis,y_dis,width,height,size_X,size_Y)
    -- 参数说明，裁减点X,y 要裁减的宽高，原图尺寸
    return {{x_dis / size_X , y_dis / size_Y},
			{(x_dis + width) / size_X , y_dis / size_Y},
			{(x_dis + width) / size_X , (y_dis + height) / size_Y},
			{x_dis / size_X , (y_dis + height) / size_Y},}
end

function AddPageControll(element_params,controllers,element_param_name,pageValue)
	if element_params and type(element_params)=='table' and #element_params>0 then
		element_params[#element_params+1] = element_param_name
		controllers[#controllers+1] = {"parameter_in_range",#element_params - 1,pageValue-0.1,pageValue+0.1}
	else
		element_params = {element_param_name}
		controllers = {{"parameter_in_range",0,pageValue-0.1,pageValue+0.1}}
	end
	return {element_params,controllers}
end

function AddLightnessControll(element_params,controllers,element_param_name)
	local ret_obj = nil
	if element_params and type(element_params)=='table' and #element_params>0 then
		if type(element_param_name)=="string" and not IGNORE_BRT then
			element_params[#element_params+1] = element_param_name..'_BRT'
			controllers[#controllers+1] = {"opacity_using_parameter",#element_params - 1}
		end
		ret_obj = {element_params,controllers}
	elseif type(element_param_name)=="string" and not IGNORE_BRT then
		element_params = {element_param_name..'_BRT'}
		controllers = {{"opacity_using_parameter",0}}
		ret_obj = {element_params,controllers}
	end
	return ret_obj
end

function AddSimple(name,pos,rot,parent_element,element_params,controllers)
	local simple    = CreateElement "ceSimple"
	simple.name     = name or create_guid_string()
	simple.init_pos = pos or { 0, 0 }
	simple.init_rot = rot or { 0, 0 }
	if parent_element then
		if type(parent_element) == 'userdata' and parent_element.name then
			simple.parent_element = parent_element.name
		elseif type(parent_element) == 'string' then
			simple.parent_element = parent_element
		end
	end
	if element_params and controllers then
		simple.element_params = element_params
		simple.controllers = controllers
	end
	if type(IS_HUD) == "boolean" then
		simple.collimated = IS_HUD
	end
	Add(simple)
	return simple
end

function AddText(name, val, material, pos, alignment, stringdefs,_h_clip_relation,
				 level, parent, formats, element_params, controllers)
	if material == nil then
		material = "font_kneeboard"
	end
	if pos == nil then
		pos = { 0, 0 }
	end
	if alignment == nil then
		alignment = "CenterCenter"
	end
	if stringdefs == nil then
		stringdefs = { 0.008, 0.008, 0, 0 }
	end
	if _h_clip_relation == nil then
		_h_clip_relation = COMPARE -- INCREASE_IF_LEVEL-- --REWRITE_LEVEL
	end
	if level == nil then
		level = DEFAULT_LEVEL
	end
	local text      = CreateElement "ceStringPoly"   --创建一个字符输出元素 "ceTexPoly"表示创建一个贴图模型
	text.name       = name or create_guid_string()
	text.material   = material                       --FONT_             --材质类型（注意上面创建的字体材质）
	text.init_pos   = pos                            -- 这是设置对齐点的坐标【这是当前模型的最大限制(在边角对齐时不要超出)】
	text.alignment  = alignment                      --对齐方式设置：Left/Right/Center; Top/Down/Center
	text.stringdefs = stringdefs                     --{ecrase vertical si inf a 0.01,ecrase lateral * streccth, 0, 0} 第一个值控制宽度，第二个值控制高度
	if val then
		text.value = val
	end
	if formats then
		text.formats = formats   -- 这里设置输出，类似于C的printf模型 %开头的是输出类型，后面的%s是输入类型
	end
	local element_ctrl
	if PAGE_NAME and Pages then
		element_ctrl=AddPageControll(element_params,controllers, IndicatorName..'_PAGE',Pages[PAGE_NAME])
	end
	if element_ctrl then
		element_ctrl = AddLightnessControll(element_ctrl[1],element_ctrl[2],BRTName or IndicatorName)
	else
		element_ctrl = AddLightnessControll(element_params,controllers,BRTName or IndicatorName)
	end
	if element_ctrl then
		text.element_params = element_ctrl[1]
		text.controllers = element_ctrl[2]
	end
	if parent then
		if type(parent) == 'userdata' and parent.name then
			text.parent_element = parent.name
		elseif type(parent) == 'string' then
			text.parent_element = parent
		end
	end
	text.use_mipfilter   = true
	text.isvisible       = true
	text.h_clip_relation = _h_clip_relation
	text.level           = level
	if type(IS_HUD) == "boolean" then
		text.collimated = IS_HUD
	end
	text.additive_alpha = true
	Add(text)
	return text
end

function AddText_NotPageCtrl(name, val, material, pos, alignment, stringdefs, formats, element_params, controllers, _h_clip_relation,
				 level, parent)
	if material == nil then
		material = "font_kneeboard"
	end
	if pos == nil then
		pos = { 0, 0 }
	end
	if alignment == nil then
		alignment = "CenterCenter"
	end
	if stringdefs == nil then
		stringdefs = { 0.008, 0.008, 0, 0 }
	end
	if _h_clip_relation == nil then
		_h_clip_relation = COMPARE -- INCREASE_IF_LEVEL-- --REWRITE_LEVEL
	end
	if level == nil then
		level = DEFAULT_LEVEL
	end
	local text      = CreateElement "ceStringPoly"   --创建一个字符输出元素
	text.name       = name or create_guid_string()
	text.material   = material                       --材质类型（注意上面创建的字体材质）
	text.init_pos   = pos                            -- 这是设置对齐点的坐标【这是当前模型的最大限制(在边角对齐时不要超出)】
	text.alignment  = alignment                      --对齐方式设置：Left/Right/Center; Top/Down/Center
	text.stringdefs = stringdefs                     --{ecrase vertical si inf a 0.01,ecrase lateral * streccth, 0, 0} 第一个值控制宽度，第二个值控制高度
	if val then
		text.value = val
	end
	if formats then
		text.formats = formats   -- 这里设置输出，类似于C的printf模型 %开头的是输出类型，后面的%s是输入类型
	end
	local element_ctrl = AddLightnessControll(element_params,controllers,BRTName or IndicatorName)
	if element_ctrl then
		text.element_params = element_ctrl[1]
		text.controllers = element_ctrl[2]
	end
	if parent then
		if type(parent) == 'userdata' and parent.name then
			text.parent_element = parent.name
		elseif type(parent) == 'string' then
			text.parent_element = parent
		end
	end
	text.use_mipfilter   = true
	text.isvisible       = true
	text.h_clip_relation = _h_clip_relation
	text.level           = level
	if type(IS_HUD) == "boolean" then
		text.collimated = IS_HUD
	end
	text.additive_alpha = true
	Add(text)
	return text
end

function AddCircle(name,radius_outer, radius_inner, arc, sides,pos,rot,material,h_clip_relation,level,parent,element_param_name,controllers,isMask)
	local circle = {}
	set_circle(circle,radius_outer, radius_inner, arc, sides)
	return AddMeshPoly(name,circle.vertices,circle.indices,pos,rot,material,h_clip_relation,level,parent,element_param_name,controllers,isMask)
end

function AddBoxBorder(name,width,height,thick,pos,rot,material,level,h_clip_relation,parent,element_param_name,controllers,isMask)
	thick            = thick or 0.01
	width = width or Width
	height = height or Height
	local vertices        = {
		{ -width,       height }, { width, height }, { width, -height }, { -width, -height },
		{ -width + thick, height - thick }, { width - thick, height - thick }, { width - thick, -height + thick },
		{ -width + thick, -height + thick },
	}
	local indices         = {
		0, 1, 5, 5, 4, 0, --up
		1, 2, 6, 6, 5, 1, --right
		2, 3, 7, 7, 6, 2, --down
		3, 0, 4, 4, 7, 3 --left
	}
	return AddMeshPoly(name,vertices,indices,pos,rot,material,h_clip_relation,level,parent,element_param_name,controllers,isMask)
end

function AddBox(name,width,height,pos,rot,material,level,h_clip_relation,parent,element_param_name,controllers,isMask)
	width = width or Width
	height = height or Height
	local vertices        = {
		{ -width,       height }, { width, height }, { width, -height }, { -width, -height },
	}
	local indices         = {
		0,1,2,2,3,0
	}
	return AddMeshPoly(name,vertices,indices,pos,rot,material,h_clip_relation,level,parent,element_param_name,controllers,isMask)
end

function AddCrossHair(name,width,height,thickness,pos,rot,material,h_clip_relation,level,parent_name,element_params,controllers)
	local simple = AddSimple(name,pos,rot,parent_name)
	width = width or Width
	height = height or Height
	AddSimpleLine(nil,thickness,{{-width,0},{width,0}},nil,nil,material,h_clip_relation,level,simple,element_params,controllers)
	AddSimpleLine(nil,thickness,{{0,-height},{0,height}},nil,nil,material,h_clip_relation,level,simple,element_params,controllers)
	return simple
end

function AddMeshCircleBox(name, radius, pos, rot,parent,element_params, controllers, arc, material,h_clip_relation,level,isMask)
	local segmentsN = 64

    local verts = {}
    local arc_s = arc[1]
    local arc_step = (arc[2]-arc[1])/(segmentsN-1)
    local inds = {}

    for i=1, segmentsN do
        verts[i] = {radius * math.cos(arc_s), radius * math.sin(arc_s)}

        arc_s = arc_s + arc_step
        if i>=3 and i <= segmentsN then 
            inds[3*(i-3)+1] = 0
            inds[3*(i-3)+2] = i-2
            inds[3*(i-3)+3] = i-1
        end
    end
    radius = radius * math.sqrt(2) /2

    inds[#inds+1] = 0
    inds[#inds+1] = #verts-1
    inds[#inds+1] = #verts
    verts[#verts+1] = {-radius, -radius}
    inds[#inds+1] = 0
    inds[#inds+1] = #verts-1
    inds[#inds+1] = #verts
    verts[#verts+1] = {radius, -radius}
	return AddMeshPoly(name,verts,inds,pos,rot,material,h_clip_relation,level,parent,element_params,controllers,isMask)
end

function AddSimpleLine(name,width,vertices,pos,rot,material,h_clip_relation,level,parent,element_params,controllers)
	local line_shape           = CreateElement "ceSimpleLineObject"
	line_shape.name            = name or create_guid_string()
	line_shape.width           = width or (0.004*Width)
	line_shape.vertices        = vertices or { { 0, 0 }, { 1, 0 } }
	line_shape.init_pos        = pos or { 0, 0 }
	line_shape.init_rot        = rot or { 0, 0 }
	--line_shape.tex_params      = { { 0, 0.5 }, { 1, 0.5 }, { 1 / (1024 * 100 / 275), 1 } }
	line_shape.isdraw          = true
	line_shape.material        = material or MakeMaterial(nil, { 0, 255, 0, 255 })
	line_shape.additive_alpha  = false
	line_shape.use_mipfilter   = true
	if parent then
		if type(parent) == 'userdata' and parent.name then
			line_shape.parent_element = parent.name
		elseif type(parent) == 'string' then
			line_shape.parent_element = parent
		end
	end
	line_shape.h_clip_relation = h_clip_relation or COMPARE
	line_shape.level           = level or DEFAULT_LEVEL
	line_shape.isdraw          = true
	local element_ctrl
	if PAGE_NAME and Pages then
		element_ctrl=AddPageControll(element_params,controllers,IndicatorName..'_PAGE',Pages[PAGE_NAME])
	end
	if element_ctrl then
		element_ctrl = AddLightnessControll(element_ctrl[1],element_ctrl[2],BRTName or IndicatorName)
	else
		element_ctrl = AddLightnessControll(element_params,controllers,BRTName or IndicatorName)
	end
	if element_ctrl then
		line_shape.element_params = element_ctrl[1]
		line_shape.controllers = element_ctrl[2]
	end
	if type(IS_HUD) == "boolean" then
		line_shape.collimated = IS_HUD
	end
	Add(line_shape)
	return line_shape
end

function AddMultiLine(name,thickness,fuzziness,vertices,indices,pos,rot,material,alignment,h_clip_relation,level,parent,element_params,controllers)
	local line_shape           = CreateElement "ceSMultiLine"
	line_shape.name            = name or create_guid_string()
	line_shape.vertices        = vertices
	line_shape.indices         = indices
	line_shape.init_pos        = pos or {0,0}
	line_shape.init_rot        = rot or {0,0}
	line_shape.material        = material or ''
	line_shape.h_clip_relation = h_clip_relation or COMPARE
	line_shape.level           = level or DEFAULT_LEVEL
	line_shape.isdraw          = true
	if alignment then
		line_shape.alignment       = alignment
	end
	line_shape.use_mipfilter   = true
	line_shape.additive_alpha  = false
	local element_ctrl
	if PAGE_NAME and Pages then
		element_ctrl=AddPageControll(element_params,controllers,IndicatorName..'_PAGE',Pages[PAGE_NAME])
	end
	if element_ctrl then
		element_ctrl = AddLightnessControll(element_ctrl[1],element_ctrl[2],IndicatorName)
	else
		element_ctrl = AddLightnessControll(element_params,controllers,IndicatorName)
	end
	if element_ctrl then
		line_shape.element_params = element_ctrl[1]
		line_shape.controllers = element_ctrl[2]
	end
	if parent then
		if type(parent) == 'userdata' and parent.name then
			line_shape.parent_element = parent.name
		elseif type(parent) == 'string' then
			line_shape.parent_element = parent
		end
	end
	if type(thickness)=="nil" then
		thickness = 0.5
	end
	if type(fuzziness)=="nil" then
		fuzziness = 0.5
	end
	line_shape.thickness			= thickness
	line_shape.fuzziness			= fuzziness
	line_shape.draw_as_wire			= dbg_drawStrokesAsWire
	--line_shape.use_specular_pass	= false -- ommitted for now as is set for the entire indicator
	if type(IS_HUD) == "boolean" then
		line_shape.collimated = IS_HUD
	end
	Add(line_shape)
	return line_shape
end

function AddMeshPoly(name,vertices,indices,pos,rot,material,h_clip_relation,level,parent,element_params,controllers,isMask)
	local meshPoly           = CreateElement "ceMeshPoly"
	meshPoly.name            = name or create_guid_string()
	meshPoly.primitivetype   = "triangles"
	meshPoly.vertices        = vertices
	meshPoly.indices         = indices
	meshPoly.init_pos        = pos or {0,0}
	meshPoly.init_rot        = rot or {0,0}
	meshPoly.material        = material or ''
	meshPoly.h_clip_relation = h_clip_relation or COMPARE
	meshPoly.level           = level or DEFAULT_LEVEL
	meshPoly.isdraw          = true
	meshPoly.change_opacity  = false
	if parent then
		if type(parent) == 'userdata' and parent.name then
			meshPoly.parent_element = parent.name
		elseif type(parent) == 'string' then
			meshPoly.parent_element = parent
		end
	end
	local element_ctrl
	if PAGE_NAME and Pages then
		element_ctrl=AddPageControll(element_params,controllers,IndicatorName..'_PAGE',Pages[PAGE_NAME])
	end
	if element_ctrl then
		element_ctrl = AddLightnessControll(element_ctrl[1],element_ctrl[2],IndicatorName)
	else
		element_ctrl = AddLightnessControll(element_params,controllers,IndicatorName)
	end
	if element_ctrl then
		meshPoly.element_params = element_ctrl[1]
		meshPoly.controllers = element_ctrl[2]
	end
	meshPoly.isvisible       = not isMask
	if type(IS_HUD) == "boolean" then
		meshPoly.collimated = IS_HUD
	end
	Add(meshPoly)
	return meshPoly
end

function AddTexture(name, vertices, indices,tex_coords, material, pos, rot, h_clip_relation, level, parent, element_params,controllers)
	local texture = CreateElement "ceTexPoly"
	texture.name = name or create_guid_string()
	texture.vertices = vertices or {{-Width,Height},{Width,Height},{Width,-Height},{-Width,-Height},}
	texture.indices = indices or {0,1,2,2,3,0}
	texture.tex_coords = tex_coords or { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } }
	texture.material = material or ''
	texture.init_pos = pos or { 0, 0}
	texture.init_rot = rot or { 0, 0}
	local element_ctrl
	if PAGE_NAME and Pages then
		element_ctrl=AddPageControll(element_params,controllers,IndicatorName..'_PAGE',Pages[PAGE_NAME])
	end
	if element_ctrl then
		element_ctrl = AddLightnessControll(element_ctrl[1],element_ctrl[2],BRTName or IndicatorName)
	else
		element_ctrl = AddLightnessControll(element_params,controllers,BRTName or IndicatorName)
	end
	if element_ctrl then
		texture.element_params = element_ctrl[1]
		texture.controllers = element_ctrl[2]
	end
	if parent then
		if type(parent) == 'userdata' and parent.name then
			texture.parent_element = parent.name
		elseif type(parent) == 'string' then
			texture.parent_element = parent
		end
	end
	texture.collimated = true
	texture.use_mipfilter = true
	texture.additive_alpha = true
	texture.h_clip_relation = h_clip_relation or COMPARE
	texture.level = level or DEFAULT_LEVEL
	Add(texture)
	return texture
end
