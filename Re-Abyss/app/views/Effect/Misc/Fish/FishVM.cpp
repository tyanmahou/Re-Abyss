#include <abyss/views/Effect/Misc/Fish/FishVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Misc::Fish
{
    FishVM::FishVM(s3d::int32 fishId):
        m_texture(Resource::Assets::Main()
        ->loadTexturePacker(U"Effect/Misc/Fish/Fish.json")(U"fish_{}"_fmt(fishId)))
    {}
    FishVM& FishVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void FishVM::draw(const s3d::ColorF& color) const
    {
        auto scaleOffset = s3d::Periodic::Triangle0_1(2s, m_time) * 0.1;
        m_texture
            .mirrored(m_forward.isRight())
            .scaled(m_scale + scaleOffset)
            .drawAt(m_pos, color);
    }
}
