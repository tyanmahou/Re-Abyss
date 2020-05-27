#include "NyanVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Ooparts::Nyan
{
    void NyanVM::drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color) const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, m_time)) % 2;
        m_texture({ 0, 20 * page }, { 20, 20 }).mirrored(isRight).drawAt(pos, color);
    }

    NyanVM::NyanVM():
        m_texture(ResourceManager::Main()->loadTexture(U"actors/Ooparts/Nyan/nyan.png"))
    {}
}
