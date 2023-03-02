#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/values/Adv/CharaKind.hpp>
#include <abyss/values/Adv/Emote.hpp>
#include <abyss/values/Adv/LookType.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Adv
{
    class CharaSetter :
        public ICommand
    {
    public:
        CharaSetter(
            AdvObj* pObj,
            const s3d::Optional<CharaKind>& kind,
            const s3d::Optional<LookType>& look,
            const s3d::Optional<Emote>& emote
        );

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        s3d::Optional<CharaKind> m_kind;
        s3d::Optional<LookType> m_look;
        s3d::Optional<Emote> m_emote;
    };
}
