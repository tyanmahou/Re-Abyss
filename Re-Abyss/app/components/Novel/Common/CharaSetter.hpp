#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/Side.hpp>

namespace abyss::Novel
{
    class CharaSetter :
        public ICommand
    {
    public:
        CharaSetter(TalkObj* pTalk, CharaKind kind, Side side, const Face& face);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        CharaKind m_kind;
        Side m_side;
        Face m_face;
    };
}
