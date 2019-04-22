package src.library.subsystem;

public interface SubsystemManagerProxy {

    boolean onSubsystemManagerStartSubsystem(String subsystemName);
    void onSubsystemManagerStopSubsystem(String subsystemName);
}
