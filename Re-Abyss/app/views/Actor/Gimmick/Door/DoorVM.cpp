#include <abyss/views/Actor/Gimmick/Door/DoorVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Gimmick::Door
{
    DoorVM::DoorVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Gimmick/Door/Door.json"))
    {}
    void DoorVM::drawCommon() const
    {
        m_texture(U"common").drawAt(m_pos);

        double alpha = Periodic::Sine0_1(4s, m_time) * 0.5;
        ColorF color[4]{
            {0.0, 0, 0, 0},
            {0.0, 0, 0, 0},
            {0, 0.5, 1.0, alpha},
            {0, 0.5, 1.0, alpha},
        };
        RectF(m_pos - Vec2{ 23, 0 }, { 46, 60 }).draw(color);
    }
    void DoorVM::drawBoss() const
    {
        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(1.0s, m_time) * 2);
        m_texture(U"boss")(80 * page, 0, 80, 120).drawAt(m_pos);

        double alpha = Periodic::Sine0_1(4s, m_time) * 0.5;
        ColorF color[4]{
            {0.0, 0, 0, 0},
            {0.0, 0, 0, 0},
            {1.0, 0.25, 0.25, alpha},
            {1.0, 0.25, 0.25, alpha},
        };
        RectF(m_pos - Vec2{ 23, 0 }, { 46, 60 }).draw(color);
    }

    void DoorVM::draw() const
    {
        switch (m_kind) {
        case DoorKind::Common:
        {
            this->drawCommon();
        }break;
        case DoorKind::Boss:{
            this->drawBoss();
        }break;
        default:
            break;
        }
    }
}
