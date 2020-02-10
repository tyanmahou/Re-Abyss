#pragma once

#include <Siv3D/Platform.hpp>

#if SIV3D_PLATFORM(WINDOWS)
#if SIV3D_BUILD_TYPE(DEBUG)
#pragma comment(lib, "S3DTiled_d")
#else
#pragma comment(lib, "S3DTiled")
#endif
#endif

