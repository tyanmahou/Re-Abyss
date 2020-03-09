#pragma once
#include <Siv3D/Texture.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/models/actors/Slime/SlimeActor.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/views/actors/base/IActorView.hpp>

namespace abyss
{
    struct SlimeViewModel
    {
        SlimeActor::Motion motion;
        Forward forward;
        s3d::Vec2 pos;
        s3d::Vec2 vellocity;
    };

    class SlimeView : public IActorView
    {
    private:
        s3d::Texture m_texture;
        SlimeViewModel m_viewModel;
    public:
        SlimeView();

        void setViewModel(const SlimeViewModel& viewModel);
        void draw()const override;
    };
}