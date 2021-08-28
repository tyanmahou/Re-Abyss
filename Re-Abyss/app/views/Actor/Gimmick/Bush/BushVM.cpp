#include "BushVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>

#include <Siv3D.hpp>
namespace abyss::Actor::Gimmick::Bush
{
    BushVM::BushVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Gimmick/Bush/bush.png"))
    {}
    BushVM& BushVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void BushVM::draw() const
    {
        s3d::Vec2 xy{};
        if (m_kind == BushKind::Left) {
            xy.x = 0;
        } else if (m_kind == BushKind::Center) {
            xy.x = 40.0;
        } else if (m_kind == BushKind::Right) {
            xy.x = 80.0;
        }
        auto rate = Periodic::Triangle0_1(Param::AnimTimeSec, m_time);
        xy.y = static_cast<int32>(rate * 3) % 3 * 40.0;
        m_texture(xy, Vec2{ 40.0, 40.0 })
            .resized({ 40.0, 40 - m_resizeRate * Param::ResizeOffset })
            .draw(Arg::bottomCenter = m_pos + Vec2{0, 20});
    }
}
