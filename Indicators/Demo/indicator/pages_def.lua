local _count = 0
local function counter()
    _count = _count + 1
    return _count
end
Pages = {
    BASE = counter(),
    INDICATOR = counter(),
}
Pages[Pages.INDICATOR] = {
    BASE = 0,
    CONFIG = 10,
    PROP = 20
}
