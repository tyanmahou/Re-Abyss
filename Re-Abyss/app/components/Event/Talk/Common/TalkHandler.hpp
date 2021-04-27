#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/Talk/base/ITalker.hpp>

namespace abyss::Event::Talk
{
    class TalkHandler : public IComponent
    {
    public:
        TalkHandler(TalkObj* pTalk);

        void setup(Executer executer) override;

        void onStart() override;

        bool update();
    private:
        TalkObj* m_pTalk;
        std::unique_ptr<Coro::Task<>> m_stream;
    };
}