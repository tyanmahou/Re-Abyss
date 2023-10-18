#pragma once
#include <memory>
#include <Siv3D/ScopedCustomShader2D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    /// <summary>
    /// ボス到着
    /// </summary>
    class BossArrivalShader
    {
        class Impl;
    public:
        BossArrivalShader(Resource::Assets* pAsset = Resource::Assets::Main());
        ~BossArrivalShader();

        const BossArrivalShader& setPos(const s3d::Vec2& pos) const;
        const BossArrivalShader& setTime(double time) const;
        s3d::ScopedCustomShader2D start() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
