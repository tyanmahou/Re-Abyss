#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(EventObj* pEvent, const s3d::String& path);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onExecute() override;
    private:
        EventObj* m_pEvent;
        s3d::String m_path;
        Ref<Novel::TalkObj> m_talk;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Talk::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}