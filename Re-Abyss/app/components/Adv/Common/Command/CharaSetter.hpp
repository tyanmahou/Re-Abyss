#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/Adv/CharaKind.hpp>
#include <abyss/modules/Adv/Face.hpp>
#include <abyss/modules/Adv/Side.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Adv
{
    class CharaSetter :
        public ICommand
    {
    public:
        CharaSetter(
            AdvObj* pTalk,
            const s3d::Optional<CharaKind>& kind,
            const s3d::Optional<Side>& side,
            const s3d::Optional<Face>& face
        );

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        s3d::Optional<CharaKind> m_kind;
        s3d::Optional<Side> m_side;
        s3d::Optional<Face> m_face;
    };
}
