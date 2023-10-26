#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    class AnchorUtil
    {
        static constexpr s3d::RectF AppScreen{ Constants::AppResolutionF };
        static constexpr s3d::Vec2 AxisRd{ 1,1 };
        static constexpr s3d::Vec2 AxisLd{ -1,1 };
        static constexpr s3d::Vec2 AxisRu{ 1,-1 };
        static constexpr s3d::Vec2 AxisLu{ -1,-1 };

#define DEFINE_ANCHOR_AXIS(name, method, axis) \
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, double x, double y)\
        {\
            return From##name(rect, { x, y });\
        }\
        static constexpr s3d::Vec2 From##name(const s3d::RectF& rect, const s3d::Vec2& pos)\
        {\
            if constexpr(axis == AxisRd) {\
                return rect.method() + pos;\
            } else {\
              return rect.method() + pos * axis;\
            }\
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
#define DEFINE_ANCHOR(name, method, default) \
DEFINE_ANCHOR_AXIS(name, method, default) \
DEFINE_ANCHOR_AXIS(name##AxisRd, method, AxisRd) \
DEFINE_ANCHOR_AXIS(name##AxisLd, method, AxisLd) \
DEFINE_ANCHOR_AXIS(name##AxisRu, method, AxisRu) \
DEFINE_ANCHOR_AXIS(name##AxisLu, method, AxisLu)

    public:
        /// <summary>
        /// ■━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tl, tl, AxisRd)

        /// <summary>
        /// ┏━━━━━■
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tr, tr, AxisLd)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ■━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Bl, bl, AxisRu)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━■
        /// </summary>
        DEFINE_ANCHOR(Br, br, AxisLu)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    ■    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cc, center, AxisRd)

        /// <summary>
        /// ┏━━■━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Tc, topCenter, AxisRd)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ┃
        /// ┃          ┃
        /// ┗━━■━━┛
        /// </summary>
        DEFINE_ANCHOR(Bc, bottomCenter, AxisRu)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ■          ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cl, leftCenter, AxisRd)

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃          ■
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        DEFINE_ANCHOR(Cr, rightCenter, AxisLd)
#undef DEFINE_ANCHOR
#undef DEFINE_ANCHOR_AXIS
    };
}
