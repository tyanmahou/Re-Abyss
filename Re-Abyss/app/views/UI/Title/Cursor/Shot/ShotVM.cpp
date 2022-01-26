#include <abyss/views/UI/Title/Cursor/Shot/ShotVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Title::Cursor
{
    ShotVM::ShotVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Player/player_shot.png"))
    {}

    ShotVM& ShotVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    ShotVM& ShotVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    void ShotVM::draw()
    {
        double timer = Periodic::Sawtooth0_1(0.3s, m_time);
        double x = 60 * static_cast<int>(timer * 4);
        double y = 40;
        double size = 60;

        m_texture(x, y, size, size).drawAt(m_pos);
    }
}
