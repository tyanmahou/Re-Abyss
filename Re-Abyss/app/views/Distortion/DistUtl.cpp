#include "DistUtl.hpp"

# include <Siv3D.hpp> // OpenSiv3D v0.4.3

namespace
{
    using IndexType = s3d::Vertex2D::IndexType;

    namespace detail
    {
        static constexpr IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

        static constexpr IndexType RectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };

        static constexpr IndexType MaxSinCosTableQuality = 40;

        static constexpr IndexType SinCosTableSize = ((MaxSinCosTableQuality - 5) * (6 + (MaxSinCosTableQuality))) / 2;

        static const std::array<Float2, SinCosTableSize> CircleSinCosTable = []() {
            std::array<Float2, SinCosTableSize> results;
            Float2* pDst = results.data();

            for (int32 quality = 6; quality <= MaxSinCosTableQuality; ++quality) {
                const float radDelta = Math::Constants::TwoPiF / quality;

                for (IndexType i = 0; i < quality; ++i) {
                    const float rad = radDelta * i;
                    (pDst++)->set(std::cos(rad), -std::sin(rad));
                }
            }

            return results;
        }();

        inline const Float2* GetSinCosTableStartPtr(const uint16 quality) noexcept
        {
            return &CircleSinCosTable[((quality - 6) * (6 + (quality - 1))) / 2];
        }

        inline constexpr IndexType CalculateCircleQuality(const float size) noexcept
        {
            if (size <= 5.0f) {
                return static_cast<IndexType>(size + 3) * 2;
            } else {
                return static_cast<IndexType>(std::min(18 + (size - 5.0f) / 2.2f, 255.0f));
            }
        }

        inline constexpr IndexType CalculateCircleFrameQuality(const float size) noexcept
        {
            if (size <= 1.0f) {
                return 6;
            } else if (size <= 8.0f) {
                return std::max(static_cast<IndexType>(2.0 * size), IndexType(8));
            } else {
                return static_cast<IndexType>(std::min(16 + (size - 8.0f) / 2.2f, 255.0f));
            }
        }

        inline IndexType CalculateCirclePieQuality(const float size, const float angle)
        {
            const float rate = std::min(Math::Abs(angle) / (Math::Constants::TwoPiF) * 2.0f, 1.0f);

            IndexType quality;

            if (size <= 1.0f) {
                quality = 4;
            } else if (size <= 6.0f) {
                quality = 7;
            } else if (size <= 8.0f) {
                quality = 11;
            } else {
                quality = static_cast<IndexType>(std::min(size * 0.225f + 18.0f, 255.0f));
            }

            return static_cast<IndexType>(std::max(quality * rate, 3.0f));
        }

        inline IndexType CaluculateFanQuality(const float r) noexcept
        {
            return r <= 1.0f ? 3
                : r <= 6.0f ? 5
                : r <= 12.0f ? 8
                : static_cast<uint16>(std::min(64.0f, r * 0.2f + 6));
        }
    }

    void DrawCircle(const Float2& center, float r, const float innerPower, const float outerPower, const float scale)
    {
        const float absR = Math::Abs(r);
        const IndexType quality = detail::CalculateCircleQuality(absR * scale);
        const IndexType vertexSize = quality + 1, indexSize = quality * 3;

        // TODO 後で確認
        //Sprite sprite(vertexSize, indexSize);
        //Vertex2D* pVertex = sprite.vertices.data();
        //IndexType* pIndex = sprite.indices.data();

        //// 中心
        //const float centerX = center.x;
        //const float centerY = center.y;
        //pVertex[0].pos.set(centerX, centerY);

        //// 周
        //if (quality <= detail::MaxSinCosTableQuality) {
        //    const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
        //    Vertex2D* pDst = &pVertex[1];

        //    for (IndexType i = 0; i < quality; ++i) {
        //        Float2 dir = (Float2{ pCS->x, pCS->y }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;
        //        (pDst)->pos.set(r * pCS->x + centerX, r * pCS->y + centerY);
        //        (pDst++)->color.set(dir.x, dir.y, 0, 0.5f);
        //        ++pCS;
        //    }
        //} else {
        //    const float radDelta = s3d::Math::TwoPiF / quality;
        //    Vertex2D* pDst = &pVertex[1];

        //    for (IndexType i = 0; i < quality; ++i) {
        //        const float rad = radDelta * i;
        //        const float c = std::cos(rad);
        //        const float s = std::sin(rad);

        //        Float2 dir = (Float2{ c, -s }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;

        //        (pDst)->pos.set(centerX + r * c, centerY - r * s);
        //        (pDst++)->color.set(dir.x, dir.y, 0, 0.5f);
        //    }
        //}

        //{
        //    (pVertex++)->color = Float4(0.5f, 0.5f, innerPower / 128.0f, 0.5f);

        //    for (size_t i = 1; i < vertexSize; ++i) {
        //        (pVertex++)->color.z = outerPower / 128.0f;
        //    }
        //}

        //{
        //    for (IndexType i = 0; i < quality - 1; ++i) {
        //        *pIndex++ = (i + 1);
        //        *pIndex++ = 0;
        //        *pIndex++ = (i + 2);
        //    }

        //    *pIndex++ = quality;
        //    *pIndex++ = 0;
        //    *pIndex++ = 1;
        //}

        //sprite.draw();
    }

    void DrawCircleFrame(const Float2& center, const float rInner, const float thickness, const float innerPower, const float outerPower, const float scale)
    {
        const float rOuter = rInner + thickness;
        const IndexType quality = detail::CalculateCircleFrameQuality(rOuter * scale);
        const IndexType vertexSize = quality * 2, indexSize = quality * 6;

        // TODO 後で確認
        //Sprite sprite(vertexSize, indexSize);
        //Vertex2D* pVertex = sprite.vertices.data();
        //IndexType* pIndex = sprite.indices.data();

        //const float centerX = center.x;
        //const float centerY = center.y;

        //if (quality <= detail::MaxSinCosTableQuality) {
        //    const Float2* pCS = detail::GetSinCosTableStartPtr(quality);
        //    Vertex2D* pDst = pVertex;

        //    for (IndexType i = 0; i < quality; ++i) {
        //        Float2 dir = (Float2{ pCS->x, pCS->y }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;

        //        (pDst)->pos.set(rOuter * pCS->x + centerX, rOuter * pCS->y + centerY);
        //        (pDst++)->color.set(dir.x, dir.y, outerPower / 128.0f, 0.5f);

        //        (pDst)->pos.set(rInner * pCS->x + centerX, rInner * pCS->y + centerY);
        //        (pDst++)->color.set(dir.x, dir.y, innerPower / 128.0f, 0.5f);

        //        ++pCS;
        //    }
        //} else {
        //    const float radDelta = s3d::Math::TwoPiF / quality;
        //    Vertex2D* pDst = pVertex;

        //    for (IndexType i = 0; i < quality; ++i) {
        //        const float rad = radDelta * i;
        //        const float c = std::cos(rad);
        //        const float s = std::sin(rad);

        //        Float2 dir = (Float2{ c, -s }.normalized() + Float2(1.0f, 1.0f)) / 2.0f;

        //        (pDst)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
        //        (pDst++)->color.set(dir.x, dir.y, outerPower / 128.0f, 0.5f);

        //        (pDst)->pos.set(centerX + rInner * c, centerY - rInner * s);
        //        (pDst++)->color.set(dir.x, dir.y, innerPower / 128.0f, 0.5f);

        //    }
        //}

        //for (IndexType i = 0; i < quality; ++i) {
        //    for (IndexType k = 0; k < 6; ++k) {
        //        *pIndex++ = (i * 2 + detail::RectIndexTable[k]) % (quality * 2);
        //    }
        //}

        //sprite.draw();
    }
}

namespace abyss::DistUtil
{
    void Draw(const s3d::Circle& circle, double innerPower, double outerPower)
    {
        DrawCircle(
            circle.center,
            static_cast<float>(circle.r),
            static_cast<float>(innerPower),
            static_cast<float>(outerPower),
            1.0f
        );
    }
    void Draw(const s3d::Circle & circle, double power)
    {
        Draw(circle, power, power);
    }
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower)
    {
        DrawCircleFrame(
            circle.center,
            static_cast<float>(circle.r - innerThickness),
            static_cast<float>(innerThickness + outerThickness),
            static_cast<float>(innerPower),
            static_cast<float>(outerPower),
            1.0f
        );
    }
    void DrawFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double power)
    {
        DrawFrame(circle, innerThickness, outerThickness, power, power);
    }
    void DrawFrame(const s3d::Circle & circle, double thickness, double power)
    {
        DrawFrame(circle, thickness * 0.5, thickness * 0.5, power);
    }
}
