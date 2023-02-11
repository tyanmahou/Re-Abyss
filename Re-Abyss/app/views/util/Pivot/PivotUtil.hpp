#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    class PivotUtil
    {
        static constexpr s3d::RectF AppScreen{ Constants::AppResolutionF };

#define DEFINE_ANCHOR(name, method) \
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, double x, double y)\
        {\
            return From##name(rect, { x, y });\
        }\
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, const s3d::Vec2& pos)\
        {\
            return rect.method() + pos;\
        }\
        static constexpr s3d::Vec2 From##name(double x, double y)\
        {\
            return From##name({ x, y });\
        }\
        static constexpr s3d::Vec2 From##name(const s3d::Vec2& pos)\
        {\
            return From##name(AppScreen, pos);\
        }\
        static s3d::Vec2 FromScene##name(double x, double y)\
        {\
            return FromScene##name({ x, y });\
        }\
        static s3d::Vec2 FromScene##name(const s3d::Vec2& pos)\
        {\
            return From##name(s3d::Scene::Rect(), pos);\
        }
    public:
        /// <summary>
        /// ■━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tl, tl)

        /// <summary>
        /// ┏━━━━━■
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tr, tr)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ■━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Bl, bl)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━■
        /// </summary>
        DEFINE_ANCHOR(Br, br)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    ■    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cc, center)

        /// <summary>
        /// ┏━━■━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tc, topCenter)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━■━━┛
        /// </summary>
        DEFINE_ANCHOR(Bc, bottomCenter)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ■          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cl, leftCenter)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ■
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cr, rightCenter)
#undef DEFINE_ANCHOR
    };
}
