#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss::Adv
{
    SentenceCtrl::SentenceCtrl(AdvObj* pObj):
        m_pObj(pObj)
    {
        this->setColor(s3d::Palette::White);
    }
    bool SentenceCtrl::update()
    {
        m_time += m_pObj->getModule<GlobalTime>()->deltaTime();
        return true;
    }
    void SentenceCtrl::setCharaKind(const CharaKind& kind)
    {
        m_sentence.setKind(kind);
    }
    void SentenceCtrl::setLook(const LookType& look)
    {
        m_sentence.setLook(look);
    }
    void SentenceCtrl::setEmote(const Emote& emote)
    {
        m_sentence.setEmote(emote);
    }
    void SentenceCtrl::setName(const Name& name)
    {
        m_sentence.setName(name);
    }
    void SentenceCtrl::setColor(const s3d::Optional<s3d::ColorF>& color)
    {
        if (color) {
            m_color.push(*color);
        } else if (!m_color.empty()) {
            m_color.pop();
        } else {
            m_color.push(s3d::Palette::White);
        }
        m_sentence.getMessage().append(
            Tag::Color{ m_color.top() }
        );
    }
    void SentenceCtrl::setIsShake(bool isShake)
    {
        m_isShake = isShake;
        m_sentence.getMessage().append(
            Tag::Shake{ isShake }
        );
    }
    void SentenceCtrl::append(const char32_t ch)
    {
        m_sentence.getMessage().append(ch, m_time);
    }
    void SentenceCtrl::clearMessage()
    {
        auto& message = m_sentence.getMessage();
        m_prevMessage = std::move(message);

        message.clear();
        m_time = 0;

        message.append(
            Tag::Color{ m_color.top() }
        );
        message.append(
            Tag::Shake{ m_isShake }
        );
    }
    void SentenceCtrl::clearBuffer()
    {
        if (m_sentence.getMessage().length() > 0) {
            this->clearMessage();
        }
        if (m_prevMessage.length() > 0) {
            m_prevMessage.clear();
        }
    }
}
