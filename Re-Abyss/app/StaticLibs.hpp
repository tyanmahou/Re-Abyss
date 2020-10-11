#pragma once

#include <Siv3D/Platform.hpp>

#if SIV3D_PLATFORM(WINDOWS)
#if SIV3D_BUILD_TYPE(DEBUG)
#pragma comment(lib, "S3DTiled_d")
#pragma comment(lib, "SQLite-for-Siv3D_d")
#else
#pragma comment(lib, "S3DTiled")
#pragma comment(lib, "SQLite-for-Siv3D")
#endif
#endif

