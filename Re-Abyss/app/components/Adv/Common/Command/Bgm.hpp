#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/values/Sound/SoundLabel.hpp>
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
            AdvObj* pObj,
            Kind kind,
            const Sound::SoundLabel& label,
            const Duration& fade
        );

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pObj = nullptr;
        Kind m_kind;
        Sound::SoundLabel m_label;
        s3d::Duration m_fade;
    };
}
