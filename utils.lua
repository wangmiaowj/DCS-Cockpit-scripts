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

--print(Input2OutputArgument(0.9,{-1,1},{-180,180}))