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
    local text = format(fmt, {...})
    cq_log_info("lua", 1, text)
end

function log:e(fmt, ...)
    local text = format(fmt, {...})
    cq_log_error("lua", 1, text)
end
