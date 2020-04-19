#include "CodeZeroHeadVM.hpp"

#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss
{
    CodeZeroHeadVM::CodeZeroHeadVM() :
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/CodeZero/code_zero.json"))
    {}

    CodeZeroHeadVM& CodeZeroHeadVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    CodeZeroHeadVM& CodeZeroHeadVM::setForward(Forward forward)
    {
        m_forward = forward;
        return *this;
    }
    CodeZeroHeadVM& CodeZeroHeadVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void CodeZeroHeadVM::draw() const
    {
        auto tex = [&]() {
            if (m_forward == Forward::None) {
                return m_texture(U"head")(0, 0, 100, 100);
            }
            return m_texture(U"head")(100, 0, 100, 100).mirrored(m_forward == Forward::Right);
        }();

        tex.drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
}
