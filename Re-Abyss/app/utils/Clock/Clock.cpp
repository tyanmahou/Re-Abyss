#include "Clock.hpp"
#include <Siv3D/Time.hpp>

namespace abyss::Clock
{
    s3d::Microseconds GetNow()
    {
        return s3d::Microseconds(s3d::Time::GetMicrosec());
    }

    s3d::Microseconds FromSec(double sec)
    {
        return s3d::DurationCast<s3d::Microseconds>(s3d::Duration(sec));
    }

}
