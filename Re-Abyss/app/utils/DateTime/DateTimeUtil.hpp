#pragma once
#include <Siv3D/DateTime.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::DateTimeUtil
{
    s3d::DateTime ToDateTime(const s3d::String& str, s3d::StringView format = U"%Y-%m-%d %H:%M:%S");

    s3d::Date ToDate(const s3d::String& str, s3d::StringView format = U"%Y-%m-%d");

    s3d::Duration ToTimeDuration(const s3d::String& str, s3d::StringView format = U"%H:%M:%S");
}