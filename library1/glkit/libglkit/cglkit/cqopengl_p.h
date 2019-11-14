#pragma once

#include "cqcbasis.h"

# if CQ_ON_ANDROID
#   include <GLES3/gl3.h>
# elif CQ_ON_IOS
#   include <OpenGLES/ES3/gl.h>
# else
#   error "unexpected target"
# endif
