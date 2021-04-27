#include "MessageBoxVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Serif
{
    MessageBoxVM::MessageBoxVM() :
        m_boxTexture(Resource::Assets::Main()->loadTexture(U"ui/common/message_box.png"))
    {}
    MessageBoxVM& MessageBoxVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    MessageBoxVM& MessageBoxVM::setName(const s3d::Optional<s3d::String>& name)
    {
        m_name = name;
        return *this;
    }
    MessageBoxVM& MessageBoxVM::setIsLeft(bool isLeft)
    {
        m_isLeft = isLeft;
        return *this;
    }
    MessageBoxVM& MessageBoxVM::setFaceIcon(const s3d::Texture& face)
    {
        m_faceIcon = face;
        return *this;
    }
    void MessageBoxVM::draw()const
    {

        double iconOffset = m_isLeft ? -380 : 220;
        RectF(m_pos + Vec2{ iconOffset, -80 }, Vec2{ 160, 160 }).draw(Color(0, 190));
        if (m_faceIcon) {
            m_faceIcon.draw(m_pos + Vec2{ iconOffset, -80 });
        }
        m_boxTexture.mirrored(!m_isLeft).drawAt(m_pos);

        if (m_name) {
            double nameOffset = m_isLeft ? -140 : 140;
            FontAsset(U"serifName")(*m_name).drawAt(m_pos + Vec2{ nameOffset, -65 });
        }
    }
}
