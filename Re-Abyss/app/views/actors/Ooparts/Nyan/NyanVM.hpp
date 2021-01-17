#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/views/Actors/Ooparts/base/BaseVM.hpp>

namespace abyss::Actor::Ooparts::Nyan
{
    class NyanVM : public BaseVM
    {
    private:
        s3d::Texture m_texture;

    public:
        NyanVM();

        void draw(const s3d::ColorF& color) const override;
        s3d::TextureRegion icon() const override;
    };
}