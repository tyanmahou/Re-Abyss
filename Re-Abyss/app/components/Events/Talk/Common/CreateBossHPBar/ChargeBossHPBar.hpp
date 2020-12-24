//#pragma once
//#include <abyss/utils/Ref/Ref.hpp>
//#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
//
//#include <abyss/modules/Event/base/IEvent.hpp>
//#include <abyss/components/UI/BossHPBar/Main.hpp>
//namespace abyss::Event::Talk
//{
//    class ChargeBossHPBar : public IEvent
//    {
//        void onStart()override;
//        bool update(double dt) override;
//        void onEnd() override;
//    private:
//        Ref<ui::IUserInterface> m_hpBar;
//        IntervalTimer m_timer;
//        s3d::Optional<s3d::FilePath> m_bossBgmPath;
//        s3d::Audio m_se;
//    public:
//        ChargeBossHPBar(Ref<ui::IUserInterface> hpBar);
//
//        void setBossBgmPath(const s3d::FilePath& path)
//        {
//            m_bossBgmPath = path;
//        }
//    };
//}