#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/types/Novel/Side.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Novel
{
    class CharaSetter :
        public ICommand
    {
    public:
        CharaSetter(
            TalkObj* pTalk,
            const s3d::Optional<CharaKind>& kind,
            const s3d::Optional<Side>& side,
            const s3d::Optional<Face>& face
        );

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        s3d::Optional<CharaKind> m_kind;
        s3d::Optional<Side> m_side;
        s3d::Optional<Face> m_face;
    };
}
