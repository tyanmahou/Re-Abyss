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
    class BossHPBarVM;
}
namespace abyss::ui
{
    class BossHPBar : public IUserInterface
    {
        IActor* m_pActor;
        Ref<Actor::HP> m_hpModel;
        std::unique_ptr<BossHPBarVM> m_view;

        double m_hp = 0;
        double m_maxHp = 1;
    public:
        BossHPBar(IActor* actor);

        void update(double dt);
        void start() override;

        void draw() const;

        bool isFull() const;
    };
}