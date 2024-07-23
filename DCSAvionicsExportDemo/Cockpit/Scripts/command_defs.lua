local count = 10000
local function counter()
    count = count + 1
    return count
end
Keys = {
    BATT = counter(),
    AC_GEN1 = counter(),
    AC_GEN2 = counter(),
    UHF_PIT = counter(),
    UHF_POWER = counter(),
    UHF_VOLUME = counter(),
    VHF_PIT = counter(),
    VHF_POWER = counter(),
    VHF_VOLUME = counter(),
    ILS_POWER = counter(),
}