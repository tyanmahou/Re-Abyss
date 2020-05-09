#include "Time.hpp"
#include <Siv3D/Time.hpp>
s3d::Microseconds abyss::Time::GetNow()
{
    return s3d::Microseconds(s3d::Time::GetMicrosec());
}

s3d::Microseconds abyss::Time::FromSec(double sec)
{
    return s3d::DurationCast<s3d::Microseconds>(s3d::Duration(sec));
}
