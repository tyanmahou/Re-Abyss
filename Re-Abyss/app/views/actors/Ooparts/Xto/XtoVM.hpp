#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/views/Actors/Ooparts/base/BaseVM.hpp>

namespace abyss::Actor::Ooparts::Xto
{
    class XtoVM : public BaseVM
    {
    private:
        s3d::Texture m_texture;

    public:
        XtoVM();


        void draw(const s3d::ColorF& color) const override;
        s3d::TextureRegion icon() const override;
    };
}