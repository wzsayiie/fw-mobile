--log.
local function Format(fmt, args)
    local okay, text = pcall(string.format, fmt, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function I(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = Format(fmt, {...})
    cq_log_info(file, line, text)
end

function E(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = Format(fmt, {...})
    cq_log_error(file, line, text)
end
