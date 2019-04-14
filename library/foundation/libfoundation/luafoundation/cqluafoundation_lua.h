--source = R"lua(

function cq_string_format(format, args)
    local okay, text = pcall(string.format, format, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function I(format, ...)
    local text = cq_string_format(format, {...})
    cq_log_info("", 0, text)
end

function E(format, ...)
    local text = cq_string_format(format, {...})
    cq_log_error("", 0, text)
end

--)lua";
