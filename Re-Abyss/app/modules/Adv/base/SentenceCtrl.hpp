#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/models/Adv/Sentence.hpp>

namespace abyss::Adv
{
    class SentenceCtrl final : public IComponent
    {
    public:
        SentenceCtrl(AdvObj* pObj);

    public:
        bool update();

        const Sentence& getSentence() const
        {
            return m_sentence;
        }
        const TagString& getPrevMessage() const
        {
            return m_prevMessage;
        }
        double getTime() const
        {
            return m_time;
        }
        void setCharaKind(const CharaKind& kind);
        void setLook(const LookType& look);
        void setEmote(const Emote& emote);

        void setName(const Name& name);

        void setColor(const s3d::Optional<s3d::ColorF>& color);
        void setIsShake(bool isShake);

        bool isInputWait() const
        {
            return m_isInputWait;
        }
        void setIsInputWait(bool isInputWait)
        {
            m_isInputWait = isInputWait;
        }

        void append(const char32_t ch);

        /// <summary>
        /// メッセージをクリア
        /// </summary>
        void clearMessage();

        /// <summary>
        /// メッセージを完全にクリア
        /// </summary>
        void clearBuffer();
    private:
        AdvObj* m_pObj;

        Sentence m_sentence;
        TagString m_prevMessage;
        std::stack<s3d::ColorF> m_color;
        bool m_isShake = false;
        bool m_isInputWait = false;

        double m_time = 0;
    };
}
