package src.library.standalone;

public class Standalone {

    public static void update() {
        PORT.cqStandaloneUpdate();
    }

    public static void launch(String[] args) {
        PORT.cqStandaloneLaunch(args);
    }
}
