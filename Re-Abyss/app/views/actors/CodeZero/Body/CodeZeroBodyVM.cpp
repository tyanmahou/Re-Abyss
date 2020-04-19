#include "CodeZeroBodyVM.hpp"

#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
namespace abyss
{
    CodeZeroBodyVM::CodeZeroBodyVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/CodeZero/code_zero.json"))
    {}

    CodeZeroBodyVM& CodeZeroBodyVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    void CodeZeroBodyVM::draw() const
    {
        m_texture(U"body").drawAt(m_pos);
    }

}
