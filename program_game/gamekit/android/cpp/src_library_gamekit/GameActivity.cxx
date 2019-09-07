#include "cqjnihelper.hh"

extern "C" void _cq_game_entry();

extern "C" JNIEXPORT void JNICALL Java_src_library_gamekit_GameActivity_entry
    (JNIEnv *, jobject)
{
    _cq_game_entry();
}
