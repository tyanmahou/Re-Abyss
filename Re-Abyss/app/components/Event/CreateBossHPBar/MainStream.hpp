#pragma once

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

#include <abyss/utils/Ref/Ref.hpp>

#include <Siv3D/Audio.hpp>

namespace abyss::Event::CreateBossHPBar
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(EventObj* pEvent, const Ref<UI::UIObj>& hpBar);

        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onExecute() override;

        void setBossBgmPath(const s3d::FilePath& path)
        {
            m_bossBgmPath = path;
        }
    private:
        EventObj* m_pEvent;
        Ref<UI::UIObj> m_hpBar;
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