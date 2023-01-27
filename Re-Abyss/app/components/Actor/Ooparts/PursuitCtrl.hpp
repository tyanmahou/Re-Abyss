#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPreDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Ooparts
{
    class PursuitCtrl:
        public IComponent,
        public IPreDraw
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body = nullptr;
        Ref<Body> m_pParent = nullptr;

        s3d::Vec2 m_localPos;
        bool m_isPursuit = true;
    public:
        PursuitCtrl(ActorObj* pActor, const Ref<Body>& pParent);

        void onStart() override;
        void onPreDraw() override;

        PursuitCtrl& setLocalPos(const s3d::Vec2& pos)
        {
            m_localPos = pos;
            return *this;
        }
        PursuitCtrl& setIsPursuit(bool active)
        {
            m_isPursuit = active;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::PursuitCtrl>
    {
        using Base = Actor::IPreDraw;
    };
}