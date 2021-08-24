#include "FishVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Misc::Fish
{
    FishVM::FishVM(s3d::int32 fishId):
        m_texture(Resource::Assets::Main()
        ->loadTexturePacker(U"effects/Misc/Fish/Fish.json")(U"fish_{}"_fmt(fishId)))
    {}
    FishVM& FishVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    void FishVM::draw(const s3d::ColorF& color) const
    {
        m_texture
            .mirrored(m_forward == Forward::Right)
            .scaled(m_scale)
            .drawAt(m_pos, color);
    }
}
