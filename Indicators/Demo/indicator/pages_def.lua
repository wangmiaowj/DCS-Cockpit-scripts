local _count = 0
Pages = {}
local function counter()
    _count = _count + 1
    return _count
end
Pages["BASE"]=counter()
Pages["INDICATOR"] = counter()