#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class DitherShader
    {
        class Impl;
    public:
        enum class Kind : s3d::int32
        {
            Bayer2x2,
            Bayer3x3,
            Bayer4x4,
            Bayer8x8,

            Default = Bayer4x4,
        };
    public:
        DitherShader();
        ~DitherShader();
        const DitherShader& setIsShape(bool isShape) const;
        const DitherShader& setKind(Kind kind) const;

        [[nodiscard]] s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
