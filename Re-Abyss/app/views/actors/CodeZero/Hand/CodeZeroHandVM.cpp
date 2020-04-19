#include "CodeZeroHandVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
namespace abyss
{
    CodeZeroHandVM::CodeZeroHandVM(Forward forward) :
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/CodeZero/code_zero.json")),
        m_forward(forward)
    {}
    CodeZeroHandVM& CodeZeroHandVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    CodeZeroHandVM& CodeZeroHandVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    void CodeZeroHandVM::draw(const s3d::Color & color) const
    {
        m_texture(U"hand")
            .mirrored(m_forward == Forward::Right)
            .rotated(m_rotate)
            .drawAt(m_pos, color);
    }
    void CodeZeroHandVM::drawAttackWait()
    {
        double t = Periodic::Sawtooth0_1(0.2s, WorldTime::Time());
        HSV hsv(360 * t, 0.5, 1.0);
        this->draw(hsv.toColor());
    }
}
