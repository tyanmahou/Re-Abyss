#include <abyss/utils/Clock/ClockUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::ClockUtil
{
    s3d::Microseconds FromSec(double sec)
    {
        return s3d::DurationCast<s3d::Microseconds>(s3d::Duration(sec));
    }
}
