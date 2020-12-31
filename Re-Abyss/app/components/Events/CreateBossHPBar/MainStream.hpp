#pragma once

#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>

#include <abyss/utils/Ref/Ref.hpp>

#include <Siv3D/Audio.hpp>

namespace abyss::Event::CreateBossHPBar
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(IEvent* pEvent, const Ref<ui::IUserInterface>& hpBar);

        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;

        void setBossBgmPath(const s3d::FilePath& path)
        {
            m_bossBgmPath = path;
        }
    private:
        IEvent* m_pEvent;
        Ref<ui::IUserInterface> m_hpBar;
        s3d::Optional<s3d::FilePath> m_bossBgmPath;
        s3d::Audio m_se;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::CreateBossHPBar::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}