#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/modules/Novel/Name.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Novel
{
    class NameSetter :
        public ICommand
    {
    public:
        NameSetter(TalkObj* pTalk, const Name& name);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        Name m_name;
    };
}
