#pragma once
#include <memory>
#include <abyss/controllers/UI/base/IUserInterface.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abuss
{
    class HP;
}
namespace abyss::ui
{
}
namespace abyss::ui
{
    class PlayerInfo : public IUserInterface
    {
        IActor* m_pActor;
        Ref<Actor::HP> m_hpModel;
    public:
        PlayerInfo(IActor* actor);

        void update(double dt);
        void start() override;

        void draw() const;
    };
}