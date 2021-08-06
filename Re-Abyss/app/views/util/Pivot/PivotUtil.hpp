#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    class PivotUtil
    {
    public:
        /// <summary>
        /// ■━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromTl(const s3d::Vec2& pos)
        {
            return pos;
        }
        static constexpr s3d::Vec2 FromTl(double x, double y)
        {
            return FromTl(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━■
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromTr(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ Constants::AppResolution.x, 0.0 };
        }
        static constexpr s3d::Vec2 FromTr(double x, double y)
        {
            return FromTr(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ■━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromBl(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ 0.0, Constants::AppResolution.y };
        }
        static constexpr s3d::Vec2 FromBl(double x, double y)
        {
            return FromBl(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━■
        /// </summary>
        static constexpr s3d::Vec2 FromBr(const s3d::Vec2& pos)
        {
            return pos + Constants::AppResolution;
        }
        static constexpr s3d::Vec2 FromBr(double x, double y)
        {
            return FromBr(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    ■    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromCenter(const s3d::Vec2& pos)
        {
            return pos + Constants::AppResolution / 2.0;
        }
        static constexpr s3d::Vec2 FromCenter(double x, double y)
        {
            return FromCenter(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━■━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromTc(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ Constants::AppResolution.x / 2.0, 0.0 };
        }
        static constexpr s3d::Vec2 FromTc(double x, double y)
        {
            return FromTc(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ┃
        /// ┃          ┃
        /// ┗━━■━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromBc(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ Constants::AppResolution.x / 2.0, Constants::AppResolution.y };
        }
        static constexpr s3d::Vec2 FromBc(double x, double y)
        {
            return FromBc(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ■    　    ┃
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromCl(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ 0.0, Constants::AppResolution.y / 2.0 };
        }
        static constexpr s3d::Vec2 FromCl(double x, double y)
        {
            return FromCl(s3d::Vec2{ x, y });
        }

        /// <summary>
        /// ┏━━━━━┓
        /// ┃          ┃
        /// ┃    　    ■
        /// ┃          ┃
        /// ┗━━━━━┛
        /// </summary>
        static constexpr s3d::Vec2 FromCr(const s3d::Vec2& pos)
        {
            return pos + s3d::Vec2{ Constants::AppResolution.x, Constants::AppResolution.y / 2.0};
        }
        static constexpr s3d::Vec2 FromCr(double x, double y)
        {
            return FromCr(s3d::Vec2{ x, y });
        }
    };
}