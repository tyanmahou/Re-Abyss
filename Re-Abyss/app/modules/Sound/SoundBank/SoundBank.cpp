#include <abyss/modules/Sound/SoundBank/SoundBank.hpp>
#include <abyss/services/Sound/base/ISoundBankService.hpp>

namespace abyss::Sound
{
    SoundBank::SoundBank(std::shared_ptr<ISoundBankService>service):
        m_service(service)
    {
    }
    AudioSetting SoundBank::setting(const SoundLabel& label) const
    {
        return m_service->setting(label);
    }
}
