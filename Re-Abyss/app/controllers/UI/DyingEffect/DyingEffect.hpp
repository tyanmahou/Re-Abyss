#pragma once
#include <memory>
#include <abyss/controllers/UI/base/IUserInterface.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abuss
{
    class HPModel;
}
namespace abyss::ui
{
    class DyingEffectVM;
}
namespace abyss::ui
{
    /// <summary>
    /// 瀕死効果
    /// </summary>
    class DyingEffect : public IUserInterface
    {
        IActor* m_pActor;
        Ref<HPModel> m_hpModel;
        std::unique_ptr<DyingEffectVM> m_view;

        double m_hp = 0;
        double m_maxHp = 1;
    public:
        DyingEffect(IActor* pActor);
        void start() override;

        void update(double dt) override;
        void draw() const;
    };
}