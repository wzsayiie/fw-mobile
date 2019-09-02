L = extends(CQObject, {
})

local function stringFormat(format, args)
    local okay, text = pcall(string.format, format, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function L:i(format, ...)
    local text = stringFormat(format, {...})
    cq_log_info("", 0, text)
end

function L:e(format, ...)
    local text = stringFormat(format, {...})
    cq_log_error("", 0, text)
end
