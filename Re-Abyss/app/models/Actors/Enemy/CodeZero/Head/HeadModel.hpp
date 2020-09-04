#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrlModel;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class HeadModel : public IComponent
    {
        Forward m_forward;

        IActor* m_pActor;
        Ref<ParentCtrlModel> m_parentCtrl;
    public:
        HeadModel(IActor* pActor);
        void setup() override;

        s3d::Vec2 getPos() const;

        void setForward(Forward forward);
        Forward getForward() const;
    };
}