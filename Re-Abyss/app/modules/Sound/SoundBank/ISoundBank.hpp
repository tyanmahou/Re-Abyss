#pragma once
#include <abyss/modules/Sound/SoundBank/SoundLabel.hpp>
#include <abyss/utils/AudioSetting/AudioSetting.hpp>

namespace abyss::Sound
{
    class ISoundBank
    {
    public:
        virtual ~ISoundBank() = default;

        virtual AudioSetting setting(const SoundLabel& label) const = 0;
    };
}
