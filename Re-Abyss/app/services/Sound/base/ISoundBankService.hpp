#pragma once
#include <abyss/modules/Sound/SoundBank/SoundLabel.hpp>
#include <abyss/utils/AudioSetting/AudioSetting.hpp>

namespace abyss::Sound
{
    class ISoundBankService
    {
    public:
        virtual ~ISoundBankService() = default;

        virtual AudioSetting setting(const SoundLabel& label) const = 0;
    };
}
