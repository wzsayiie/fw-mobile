package src.library.subsystem;

import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class PORT {

    public static void cq_subsystem_start() {
        SubsystemManager.get().startSubsystem();
    }

    public static void cq_subsystem_stop() {
        SubsystemManager.get().stopSubsystem();
    }
}
