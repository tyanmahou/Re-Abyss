#include "CursorVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>
namespace abyss::ui
{
    CursorVM::CursorVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"ui/common/cursor.png"))
    {}

    CursorVM& CursorVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }

    void CursorVM::draw() const
    {
        m_texture.scaled(Sin(Scene::Time() * 2.0), 1.0).drawAt(m_pos);
    }

}
