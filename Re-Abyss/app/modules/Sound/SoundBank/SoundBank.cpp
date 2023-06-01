#include <abyss/modules/Sound/SoundBank/SoundBank.hpp>

namespace abyss::Sound
{
    SoundBank::SoundBank(std::shared_ptr<ISoundService>service):
        m_service(service)
    {
    }
    AudioSetting SoundBank::setting(const SoundLabel& label) const
    {
        return {};
    }
}
