#pragma once
#include <Siv3D/Duration.hpp>

namespace abyss
{
    using Clock_t = std::function<s3d::Microseconds()>;

    namespace Clock
    {
        s3d::Microseconds GetNow();
        s3d::Microseconds FromSec(double sec);
    }
}