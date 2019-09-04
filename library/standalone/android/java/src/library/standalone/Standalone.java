package src.library.standalone;

import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class Standalone {

    public static void update() {
        PORT.cqStandaloneUpdate();
    }

    public static void launch(String[] args) {
        PORT.cqStandaloneLaunch(args);
    }
}
