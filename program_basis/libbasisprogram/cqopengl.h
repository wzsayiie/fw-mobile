#pragma once

#include "cqcbasis.h"

# if CQ_ON_ANDROID
#   include <GLES2/gl2.h>
# elif CQ_ON_IOS
#   include <OpenGLES/ES2/gl.h>
# else
#   error "unexpected target"
# endif
