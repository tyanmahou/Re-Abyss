#include <abyss/views/UI/Message/MessageBoxVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Message
{
    MessageBoxVM::MessageBoxVM() :
        m_boxTexture(Resource::Assets::Main()->load(U"UI/Common/MessageBox.png"))
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
    MessageBoxVM& MessageBoxVM::setAlpha(double alpha)
    {
        m_alpha = alpha;
        return *this;
    }
    void MessageBoxVM::draw()const
    {

        double iconOffset = m_isLeft ? -380 : 220;
        RectF(m_pos + Vec2{ iconOffset, -80 }, Vec2{ 160, 160 }).draw(ColorF(0, m_alpha * 190.0 / 250.0));
        if (m_faceIcon) {
            m_faceIcon.draw(m_pos + Vec2{ iconOffset, -80 }, ColorF(1, m_alpha));
        }
        m_boxTexture.mirrored(!m_isLeft).drawAt(m_pos, ColorF(1, m_alpha));

        if (m_name) {
            double nameOffset = m_isLeft ? -140 : 140;
            FontAsset(FontName::SentenceName)(*m_name).drawAt(m_pos + Vec2{ nameOffset, -65 }, ColorF(1, m_alpha));
        }
    }
}
