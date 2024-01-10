function startup_print(...)
    print(...)
end
function DebugPrint(msg)
    if msg == true then
        msg = 'true'
    elseif msg == false then
        msg = 'false'
    elseif msg == nil then
        msg = 'nil'
    end
    print_message_to_user(msg)
end

function GetIndexOfValInTbl(tbl,val)
	for i,v in ipairs(tbl) do
		if(val==tbl[i]) then
			return i
		end
	end
end

function GetTableLength(t)
    local res=0
    for k,v in pairs(t) do
        res=res+1
    end
    return res
end

function Limit(value,min,max)
    if value > max then
        return max
    elseif value < min then
        return min
    else
        return value
    end
end
function ConvertSwitch(num)
    if num == 0 then
        return 'OFF'
    else
        return 'ON'
    end
end

function Input2OutputArgument(input,in_range,out_range)
	local in_range_sum = math.abs(in_range[1])+math.abs(in_range[2])
	local out_range_sum = math.abs(out_range[1])+math.abs(out_range[2])
	input = Limit(input,in_range[1],in_range[2])
	return (input-in_range[1])/in_range_sum*out_range_sum+out_range[1]
end

function LoopPlayAnimal(inputVal,add,minVal,maxVal)
	local result = inputVal + add
    if type(maxVal) == "nil" then
        maxVal = 1
    end
	minVal = minVal or 0
	local range = maxVal - minVal
	if result>maxVal or result <minVal then
        local tmp = result/range
        if tmp<0 then
            result = minVal+result - math.ceil(tmp)*range
        else
            result = minVal+result - math.floor(tmp)*range
        end
	end
    return result
end

--dd：DD格式的坐标
--type: 坐标方向，1：维度,2：经度
function DD_to_DMS(dd,type)
    local d = math.floor(dd)
    local m = (dd-d)*60
    local s = (m-math.floor(m))*60
    local way
    if d > 0 then
        if type == 1 then
            way = 'N'
        else
            way = 'E'
        end
    else
        if type == 1 then
            way = 'S'
        else
            way = 'W'
        end
    end
    d = math.abs(d)
    if type==1 then
        return string.format('%s%02.0f-%02.0f-%05.2f',way,d,m,s)
    else
        return string.format('%s%03.0f-%02.0f-%05.2f',way,d,m,s)
    end
    
end

function DD_to_D_M_S(dd,type)
    local d = math.floor(dd)
    local m = (dd-d)*60
    local s = (m-math.floor(m))*60
    local way
    if d > 0 then
        if type == 1 then
            way = 'N'
        else
            way = 'E'
        end
    else
        if type == 1 then
            way = 'S'
        else
            way = 'W'
        end
    end
    d = math.abs(d)
    return way,d,m,s
end

function DMS_to_DD(way,dd,mm,ss)
    local DD = dd + mm/60+ ss/3600
    if way=='S' or way == 'W' then
        DD = -DD
    end
    return DD
end

function SecondsTo_ddHHmmss(seconds)
    local day = math.floor(seconds / 86400)
    local hour = math.floor((seconds - day * 86400) / 3600)
    local minute = math.floor((seconds - day * 86400 - hour * 3600) / 60)
    local ss = math.floor(seconds - day * 86400 - hour * 3600 - minute * 60)
    return day,hour,minute,ss
end

function SecondsFormat_mmss(seconds)
    local day,hour,mm,ss = SecondsTo_ddHHmmss(seconds)
    return string.format('%02.0f:%02.0f',mm,ss)
end

function StringContains(str, item)
    local t = {}
    local l = {}
    local index = 0
    for i = 1, string.len(str) do
        table.insert(t, string.byte(string.sub(str, i, i)))
    end

    for i = 1, string.len(item) do
        table.insert(l, string.byte(string.sub(item, i, i)))
    end
    if #l > #t then
        return false
    end

    for k, v1 in pairs(t) do
        index = index + 1
        if v1 == l[1] then
            local iscontens = true
            for i = 1, #l do
                if t[index + i - 1] ~= l[i] then
                    iscontens = false
                end
            end
            if iscontens then
                return iscontens
            end
        end
    end
    return false
end

--print(Input2OutputArgument(0.9,{-1,1},{-180,180}))