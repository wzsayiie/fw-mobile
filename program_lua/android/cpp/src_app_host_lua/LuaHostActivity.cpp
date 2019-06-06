#include "cqjnihelper.hh"

extern "C" void _cq_lua_entry();

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaHostActivity_entry
/**/(JNIEnv *, jobject)
{
    _cq_lua_entry();
}
