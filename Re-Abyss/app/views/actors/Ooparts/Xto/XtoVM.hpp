#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::Actor::Ooparts::Xto
{
    class XtoVM : public OopartsVM
    {
    private:
        s3d::Texture m_texture;

        void drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color) const override;
    public:
        XtoVM();
    };
}