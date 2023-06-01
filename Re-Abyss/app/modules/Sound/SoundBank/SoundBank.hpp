#pragma once
#include <abyss/modules/Sound/SoundBank/ISoundBank.hpp>
#include <Emaject.hpp>

namespace abyss::Sound
{
    class ISoundBankService;

    class SoundBank : public ISoundBank
    {
    public:
        INJECT_CTOR(SoundBank(std::shared_ptr<ISoundBankService> service));

        AudioSetting setting(const SoundLabel& label) const override;
    private:
        std::shared_ptr<ISoundBankService> m_service;
    };
}
