﻿#pragma once
#include <Siv3D/Types.hpp>
#include <Siv3D/StringView.hpp>
#include <Siv3D/Char.hpp>

namespace abyss
{
    /// <summary>
    /// バージョンクラス
    /// </summary>
    struct Version
    {
        constexpr static Version Parse(s3d::StringView version)
        {
            s3d::uint32 v[4]{ 0, 0, 0, 0 };
            bool isDigit = false;
            size_t vIndex = 0;
            auto it = version.begin();
            while (it != version.end()) {
                if (s3d::IsDigit(*it))
                {
                    isDigit = true;
                    v[vIndex] = v[vIndex] * 10 + (*it - U'0');
                } else if (isDigit) {
                    isDigit = false;
                    ++vIndex;
                    if (vIndex >= 4) {
                        break;
                    }
                }

                ++it;
            }
            return Version{ v[0], v[1], v[2], v[3] };
        }

        constexpr Version() = default;
        constexpr Version(s3d::uint32 _major, s3d::uint32 _minor, s3d::uint32 _build = 0, s3d::uint32 _revision = 0) :
            major(_major),
            minor(_minor),
            build(_build),
            revision(_revision)
        {}
        constexpr Version(const Version& other) :
            major(other.major),
            minor(other.minor),
            build(other.build),
            revision(other.revision)
        {
        }

        constexpr Version(s3d::StringView version) :
            Version(Parse(version))
        {
        }

        constexpr auto operator<=>(const Version& other)const = default;

        s3d::String format(s3d::StringView fmt) const
        {
            return s3d::Fmt(fmt)(major, minor, build, revision);
        }
        s3d::uint32 major = 0;
        s3d::uint32 minor = 0;
        s3d::uint32 build = 0;
        s3d::uint32 revision = 0;
    };
}
