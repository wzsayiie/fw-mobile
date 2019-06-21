package src.library.subsystem;

@SuppressWarnings("unused") /* the methods will be called by native */
public class Subsystem {

    public static void cq_subsystem_start() {
        CQSubsystemManager.get().startSubsystem();
    }

    public static void cq_subsystem_stop() {
        CQSubsystemManager.get().stopSubsystem();
    }
}
