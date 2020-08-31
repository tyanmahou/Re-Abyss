#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Cycle::Title::BackGround
{
    /// <summary>
    /// 背景：アトランティス
    /// </summary>
    class AtlantisVM
    {
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
    public:
        AtlantisVM();

        AtlantisVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        void draw() const;
    };
}