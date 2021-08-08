#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    class PivotUtil
    {
#define DEFINE_PIVOT(name, ...) \
        static constexpr s3d::Vec2 name{ __VA_ARGS__ };\
        static constexpr s3d::Vec2 From##name(const s3d::Vec2& pos)\
        {\
            return pos + name;\
        }\
        static constexpr s3d::Vec2 From##name(double x, double y)\
        {\
            return From##name(s3d::Vec2{ x, y });\
        }
    public:
        /// <summary>
        /// ■━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Tl, 0, 0)

        /// <summary>
        /// ┏━━━━━■
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Tr, Constants::AppResolution.x, 0)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ■━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Bl, 0, Constants::AppResolution.y)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━■
        /// </summary>
        DEFINE_PIVOT(Br, Constants::AppResolution)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    ■    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Cc, Constants::AppResolution / 2.0)

        /// <summary>
        /// ┏━━■━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Tc, Constants::AppResolution.x / 2.0, 0)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━■━━┛
        /// </summary>
        DEFINE_PIVOT(Bc, Constants::AppResolution.x / 2.0, Constants::AppResolution.y)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ■    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Cl, 0, Constants::AppResolution.y / 2.0)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ■
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_PIVOT(Cr, Constants::AppResolution.x, Constants::AppResolution.y / 2.0)
#undef DEFINE_PIVOT
    };
}