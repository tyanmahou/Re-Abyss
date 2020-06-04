#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/controllers/UI/BossHPBar/BossHPBar.hpp>
namespace abyss::Event::Talk
{
    class ChargeBossHPBar : public IEvent
    {
        void init()override;
        bool update(double dt) override;
    private:
        Ref<ui::BossHPBar> m_hpBar;
        IntervalTimer m_timer;
        s3d::Optional<s3d::FilePath> m_bossBgmPath;
    public:
        ChargeBossHPBar(Ref<ui::BossHPBar> hpBar);
        ~ChargeBossHPBar();

        void setBossBgmPath(const s3d::FilePath& path)
        {
            m_bossBgmPath = path;
        }
    };
}