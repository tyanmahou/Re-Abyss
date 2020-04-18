#include "DoorDecorVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    void DoorDecorVM::drawCommon() const
    {
        double t = WorldTime::Time();
        const auto& pos = m_model.getPos();
        m_texture(U"common").drawAt(pos);

        double alpha = Periodic::Sine0_1(4s, t) * 0.5;
        ColorF color[4]{
            {0.0, 0, 0, 0},
            {0.0, 0, 0, 0},
            {0, 0.5, 1.0, alpha},
            {0, 0.5, 1.0, alpha},
        };
        RectF(pos - Vec2{ 23, 0 }, { 46, 60 }).draw(color);
    }
    void DoorDecorVM::drawBoss() const
    {
        double t = WorldTime::Time();
        const auto& pos = m_model.getPos();
        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(1.0s, t) * 2);
        m_texture(U"boss")(80 * page, 0, 80, 120).drawAt(pos);

        double alpha = Periodic::Sine0_1(4s, t) * 0.5;
        ColorF color[4]{
            {0.0, 0, 0, 0},
            {0.0, 0, 0, 0},
            {1.0, 0.25, 0.25, alpha},
            {1.0, 0.25, 0.25, alpha},
        };
        RectF(pos - Vec2{ 23, 0 }, { 46, 60 }).draw(color);
    }
    DoorDecorVM::DoorDecorVM(const DoorDecorModel& model):
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Door/door.json")),
        m_model(model)
    {}
    void DoorDecorVM::draw(const s3d::RectF & screen) const
    {
        if (!screen.intersects(m_model.region())) {
            return;
        }
        switch (m_model.getKind()) {
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
