#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/LocationCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    class Flashs :
        public IComponent,
        public IDrawParts
    {
        struct Flash
        {
        public:
            Flash();

            bool update(const s3d::Vec2& pos, double dt);
        private:
            s3d::Vec2 m_localPos;
            double m_lifeTime = 0.0;
        };
    public:
        Flashs(EffectObj* pObj);

        Coro::Fiber<void> task();
    public:
        void onStart() override;

        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        Ref<LocationCtrl> m_location;
        s3d::Array<Flash> m_flashs;
        Coro::FiberHolder<void> m_task;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Item::Recovery::Flashs>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}