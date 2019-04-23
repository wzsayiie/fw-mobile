package src.library.subsystem;

public class Subsystem {

    public static boolean cq_system_start(String name) {
        return SubsystemManager.get().startSubsystem(name);
    }

    public static void cq_system_stop(String name) {
        SubsystemManager.get().stopSubsystem(name);
    }
}
