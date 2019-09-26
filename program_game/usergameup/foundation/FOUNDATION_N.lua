--LUA R"R(

if not cq_log_info then

    function cq_log_info (file, line, msg) end
    function cq_log_error(file, line, msg) end

end

--)R"