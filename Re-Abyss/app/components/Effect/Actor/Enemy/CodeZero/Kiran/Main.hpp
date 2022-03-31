#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::Kiran
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);

        void onUpdate() override;
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos{ 0, 0 };
        TexturePacker m_texture;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::Kiran::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDraw
        >;
    };
}