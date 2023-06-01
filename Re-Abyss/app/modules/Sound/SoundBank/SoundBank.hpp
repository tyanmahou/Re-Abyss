#pragma once
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>
#include <Emaject.hpp>

namespace abyss::Sound
{
    class ISoundService;

    class SoundBank : public ISoundBank
    {
    public:
        INJECT_CTOR(SoundBank(std::shared_ptr<ISoundService> service));

        AudioSetting setting(const SoundLabel& label) const override;
    private:
        std::shared_ptr<ISoundService> m_service;
    };
}
