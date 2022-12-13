#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Novel
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
            TalkObj* pTalk,
            Kind kind,
            const s3d::String& path,
            const Duration& fade
        );

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        Kind m_kind;
        s3d::String m_path;
        s3d::Duration m_fade;
    };
}
