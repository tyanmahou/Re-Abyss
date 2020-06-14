#include "AudioSetting.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss
{
    void AudioSetting::apply(s3d::Audio& audio)
    {
        std::visit(overloaded{
            [&](bool l) {
                audio.setLoop(l);
            },
            [&](const s3d::Vec2& l) {
                audio.setLoop(Duration(l.x), Duration(l.y));
            }
        }, loop);
    }
}
