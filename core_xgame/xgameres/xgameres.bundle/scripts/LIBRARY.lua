if host_os == nil then

    --libfoundation:

    function host_os() end -->string

    function log_info (file, line, text) end -->void
    function log_error(file, line, text) end -->void

    function ios_bundle_path   ()          end -->string
    function ios_resource_path (name, ext) end -->string
    function android_copy_asset(from, to ) end -->boolean

    function document_directory () end -->string
    function caches_directory   () end -->string
    function temporary_directory() end -->string

    function directory_exists(path) end -->boolean
    function file_exists     (path) end -->boolean
    function remove_path     (path) end -->void
    function sub_files       (path) end -->{string...}

    function create_directory(path, intermediate) end -->boolean

    --libsubsystem:

    function subsystem_start() end -->void
    function subsystem_stop () end -->void

end

--log.
local function format(fmt, args)
    local okay, text = pcall(string.format, fmt, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function i(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = format(fmt, {...})
    log_info(file, line, text)
end

function e(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = format(fmt, {...})
    log_error(file, line, text)
end
