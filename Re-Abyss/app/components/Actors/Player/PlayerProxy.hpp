#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Player
{
    class PlayerProxy : 
        public IComponent
    {
    public:
        PlayerProxy(IActor* pActor);

        void onStart() override;

        const s3d::Vec2& getPos() const;

        Forward getForward() const;
    private:
        IActor* m_pActor;
        Ref<Body> m_body;
    };
}