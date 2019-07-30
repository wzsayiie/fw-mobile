package src.library.subsystem;

@SuppressWarnings("unused") /* the methods will be called by native */
public class PORT {

    public static void cq_subsystem_start() {
        SubsystemManager.get().startSubsystem();
    }

    public static void cq_subsystem_stop() {
        SubsystemManager.get().stopSubsystem();
    }
}
