log = {}

local function format(fmt, args)
    local okay, text = pcall(string.format, fmt, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function log:i(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = format(fmt, {...})
    cq_log_info(file, line, text)
end

function log:e(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = format(fmt, {...})
    cq_log_error(file, line, text)
end
