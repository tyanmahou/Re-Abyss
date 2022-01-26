#include <abyss/views/UI/SpeechBalloon/SpeechBalloonVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SpeechBalloon
{
    SpeechBalloonVM::SpeechBalloonVM():
        m_texture(Resource::Assets::Main()->load(U"ui/SpeechBalloon/speech_balloon.png"))
    {}

    void SpeechBalloonVM::draw() const
    {
        double yOffset = s3d::Periodic::Sine0_1(3s, m_time);
        auto pos = m_pos + s3d::Vec2{0, yOffset * 8 };
        m_texture(0, 0, 60, 30).drawAt(pos);

        int32 dot = static_cast<int32>(s3d::Periodic::Sawtooth0_1(3s, m_time) * 4.0) % 4;
        m_texture(14, 30, 12 * dot, 10).draw(pos - s3d::Vec2{18, 6});
    }
}
