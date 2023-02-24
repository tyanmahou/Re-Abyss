#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Adv
{
    class Bgm :
        public ICommand
    {
    public:
        enum class Kind
        {
            Play,
            Stop,
            Stash,
            StashPop,
        };
    public:
        Bgm(
            AdvObj* pTalk,
            Kind kind,
            const s3d::String& path,
            const Duration& fade
        );

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        Kind m_kind;
        s3d::String m_path;
        s3d::Duration m_fade;
    };
}
