#pragma once
#include <Siv3D/Texture.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/views/Actors/base/IActorView.hpp>

namespace abyss
{
    class SlimeView : public IActorView
    {
    private:
        const SlimeActor* const m_pModel;
        s3d::Texture m_texture;
    public:
        SlimeView(const SlimeActor* const pModel);

        void draw()const override;
    };
}