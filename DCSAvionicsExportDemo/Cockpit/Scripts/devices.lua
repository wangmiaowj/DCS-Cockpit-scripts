local count = 0
local function counter()
    count = count + 1
    return count
end
devices={}
devices.ELECTRIC = counter()--ils和无线电设备都需要电力系统的支持
devices.INTERCOM = counter()
devices.UHF_RADIO = counter()
devices.VHF_RADIO_AM = counter()
devices.VHF_RADIO_FM = counter()
devices.RADIO_HACKER = counter()--无线电呼叫在这里操作
devices.ILS = counter()
devices.ILS_HACKER = counter()--ILS逻辑在这里
devices.CLOCK = counter()--创建clock是为了snd的相关函数不传递timestamp参数的时候自动使用当前任务时间
devices.SND = counter()