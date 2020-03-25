#pragma once
#include <Siv3D/Duration.hpp>

namespace abyss
{
    using TimeGetFunction_t = std::function<s3d::Microseconds()>;

    namespace Time
    {
        s3d::Microseconds GetNow();
    }
}