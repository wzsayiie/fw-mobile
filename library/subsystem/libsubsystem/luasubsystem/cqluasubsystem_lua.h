--source = R"lua(

CQSubsystemManager = cq_extends(CQObject, {
    sharedObject = nil,
})

function CQSubsystemManager:get()
    if CQSubsystemManager.sharedObject == nil then
        CQSubsystemManager.sharedObject = CQSubsystemManager:new()
    end
    return CQSubsystemManager.sharedObject
end

function CQSubsystemManager:startSubsystem(name)
    cq_subsystem_start(name)
end

function CQSubsystemManager:stopSubsystem(name)
    cq_subsystem_stop(name)
end

--)lua";
