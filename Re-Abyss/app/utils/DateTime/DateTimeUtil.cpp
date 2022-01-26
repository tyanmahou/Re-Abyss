#include <abyss/utils/DateTime/DateTimeUtil.hpp>

#include <locale>
#include <iomanip>

#include <Siv3D/Parse.hpp>
#include <Siv3D/FormatLiteral.hpp>

namespace abyss::DateTimeUtil
{
    s3d::DateTime ToDateTime(const s3d::String& str, s3d::StringView format)
    {
        using namespace s3d::Literals::FormatLiterals;

        std::tm t = {};
        std::basic_istringstream<char32_t> ss(str.c_str());
        ss >> std::get_time(&t, format.data());
        if (ss.fail()) {
            throw s3d::ParseError(U"ToDateTime({}) failed"_fmt(str));
        }
        return s3d::DateTime(
            t.tm_year + 1900, 
            t.tm_mon + 1,
            t.tm_mday,
            t.tm_hour,
            t.tm_min,
            t.tm_sec
        );
    }
    s3d::Date ToDate(const s3d::String& str, s3d::StringView format)
    {
        using namespace s3d::Literals::FormatLiterals;

        std::tm t = {};
        std::basic_istringstream<char32_t> ss(str.c_str());
        ss >> std::get_time(&t, format.data());
        if (ss.fail()) {
            throw s3d::ParseError(U"ToDate({}) failed"_fmt(str));
        }
        return s3d::Date(
            t.tm_year + 1900,
            t.tm_mon + 1,
            t.tm_mday
        );
    }

    s3d::Duration ToTimeDuration(const s3d::String& str, s3d::StringView format)
    {
        using namespace s3d::Literals::FormatLiterals;

        std::tm t = {};
        std::basic_istringstream<char32_t> ss(str.c_str());
        ss >> std::get_time(&t, format.data());
        if (ss.fail()) {
            throw s3d::ParseError(U"ToDuration({}) failed"_fmt(str));
        }

        auto time = s3d::Hours(t.tm_hour) + s3d::Minutes(t.tm_min) + s3d::Seconds(t.tm_sec);
        return s3d::DurationCast<s3d::Duration>(time);
    }
}
