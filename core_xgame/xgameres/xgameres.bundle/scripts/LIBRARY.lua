if HostOS == nil then

    --libfoundation:

    function HostOS() end -->string

    function LogInfo (file, line, text) end -->void
    function LogError(file, line, text) end -->void

    function IOSBundlePath   ()          end -->string
    function IOSResourcePath (name, ext) end -->string
    function AndroidCopyAsset(from, to ) end -->boolean

    function DocumentDirectory () end -->string
    function CachesDirectory   () end -->string
    function TemporaryDirectory() end -->string

    function DirectoryExists(path) end -->boolean
    function FileExists     (path) end -->boolean
    function RemovePath     (path) end -->void

    function CreateDirectory(path, intermediate) end -->boolean

    --libsubsystem:

    function SubsystemStart() end -->void
    function SubsystemStop () end -->void

end

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
    LogInfo(file, line, text)
end

function E(fmt, ...)
    local file = debug.getinfo(2, 'S').source
    local line = debug.getinfo(2, 'l').currentline
    local text = Format(fmt, {...})
    LogError(file, line, text)
end
