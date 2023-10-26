#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    struct AnchorAxis
    {
        static constexpr s3d::Vec2 Rd{ 1,1 };
        static constexpr s3d::Vec2 Ld{ -1,1 };
        static constexpr s3d::Vec2 Ru{ 1,-1 };
        static constexpr s3d::Vec2 Lu{ -1,-1 };
    };
    class AnchorUtil
    {
        static constexpr s3d::RectF AppScreen{ Constants::AppResolutionF };
#define DEFINE_ANCHOR_BASE(name, method, defaultAxis) \
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, double x, double y, const s3d::Vec2& axis = defaultAxis)\
        {\
            return From##name(rect, { x, y }, axis);\
        }\
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, const s3d::Vec2& pos, const s3d::Vec2& axis = defaultAxis)\
        {\
            return rect.method() + pos * axis; \
        }\
        static constexpr s3d::Vec2 From##name(double x, double y, const s3d::Vec2& axis = defaultAxis)\
        {\
            return From##name(s3d::Vec2{ x, y }, axis);\
        }\
        static constexpr s3d::Vec2 From##name(const s3d::Vec2& pos, const s3d::Vec2& axis = defaultAxis)\
        {\
            return From##name(AppScreen, pos, axis);\
        }\
        static s3d::Vec2 FromScene##name(double x, double y, const s3d::Vec2& axis = defaultAxis)\
        {\
            return FromScene##name({ x, y }, axis);\
        }\
        static s3d::Vec2 FromScene##name(const s3d::Vec2& pos, const s3d::Vec2& axis = defaultAxis)\
        {\
            return From##name(s3d::Scene::Rect(), pos, axis);\
        }
#define DEFINE_ANCHOR_AXIS(name, axisName, axis)\
        static constexpr s3d::Vec2 From##name##axisName(const s3d::RectF& rect, double x, double y)\
        {\
            return From##name(rect, { x, y }, axis); \
        }\
        static constexpr s3d::Vec2 From##name##axisName(const s3d::RectF& rect, const s3d::Vec2& pos)\
        {\
            return From##name(rect, pos, axis); \
        }\
        static constexpr s3d::Vec2 From##name##axisName(double x, double y)\
        {\
            return From##name(s3d::Vec2{ x, y }, axis); \
        }\
        static constexpr s3d::Vec2 From##name##axisName(const s3d::Vec2& pos)\
        {\
            return From##name(AppScreen, pos, axis); \
        }\
        static s3d::Vec2 FromScene##name##axisName(double x, double y)\
        {\
            return FromScene##name({ x, y }, axis); \
        }\
        static s3d::Vec2 FromScene##name##axisName(const s3d::Vec2& pos)\
        {\
            return From##name(s3d::Scene::Rect(), pos, axis); \
        }
#define DEFINE_ANCHOR(name, method, defaultAxis) \
DEFINE_ANCHOR_BASE(name, method, defaultAxis)\
DEFINE_ANCHOR_AXIS(name, AxisRd, AnchorAxis::Rd)\
DEFINE_ANCHOR_AXIS(name, AxisLd, AnchorAxis::Ld)\
DEFINE_ANCHOR_AXIS(name, AxisRu, AnchorAxis::Ru)\
DEFINE_ANCHOR_AXIS(name, AxisLu, AnchorAxis::Lu)

    public:
        /// <summary>
        /// ■━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tl, tl, AnchorAxis::Rd)

        /// <summary>
        /// ┏━━━━━■
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tr, tr, AnchorAxis::Ld)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ■━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Bl, bl, AnchorAxis::Ru)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━■
        /// </summary>
        DEFINE_ANCHOR(Br, br, AnchorAxis::Lu)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    ■    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cc, center, AnchorAxis::Rd)

        /// <summary>
        /// ┏━━■━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tc, topCenter, AnchorAxis::Rd)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━■━━┛
        /// </summary>
        DEFINE_ANCHOR(Bc, bottomCenter, AnchorAxis::Ru)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ■          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cl, leftCenter, AnchorAxis::Rd)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ■
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cr, rightCenter, AnchorAxis::Ld)
#undef DEFINE_ANCHOR
#undef DEFINE_ANCHOR_BASE
#undef DEFINE_ANCHOR_AXIS
    };
}
