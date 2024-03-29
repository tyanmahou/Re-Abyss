#include <abyss/components/UI/Message/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Adv/Adventures.hpp>

#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

#include <abyss/views/UI/Message/MessageBoxVM.hpp>
#include <abyss/views/UI/Message/CursorVM.hpp>
#include <abyss/views/Adv/TagString/TagStringView.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Message
{
    Main::Main(
        UIObj* pUi,
        const Ref<Adv::SentenceCtrl>& sentence
    ) :
        m_pUi(pUi),
        m_sentence(sentence),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>()),
        m_showHideTimer(0.5)
    {
        m_showHideTimer.toEnd();
    }
    Main::~Main()
    {}
    void Main::onStart()
    {}

    void Main::onUpdate()
    {
        if (!m_sentence) {
            m_pUi->destroy();
            return;
        }
        m_showHideTimer.update(m_pUi->deltaTime());
    }

    void Main::onDraw() const
    {
        if (!m_sentence) {
            return;
        }
        if (!isVisible()) {
            return;
        }
        const auto& sentence = m_sentence->getSentence();

        const auto rate = m_isVisible ?
            s3d::EaseOutCubic(m_showHideTimer.rate()) :
            s3d::EaseInCubic(m_showHideTimer.invRate());
        const auto alpha = rate;
        const Vec2 pos = AnchorUtil::FromTc(0, 150) + Vec2{0.0, (1.0 - rate) * -40.0};
        m_boxView
            ->setIsLeft(sentence.isLookRight()) // 向きとアイコンの位置は反転するのでIsLeftにisRightを設定している
            .setPos(pos)
            .setName(sentence.getName())
            .setAlpha(alpha);

        auto* advs = m_pUi->getModule<Adventures>();
        if (auto chara = advs->findChara(sentence.getKind())) {
            if (auto face = chara->getFace(sentence.getEmote())) {
                m_boxView->setFaceIcon(face);
            } else {
                m_boxView->setFaceIcon({});
            }
            if (sentence.getName().isNoname()) {
                m_boxView->setName(chara->getName());
            }
        } else {
            m_boxView->setFaceIcon({});
        }
        m_boxView->draw();

        auto&& font = FontAsset(FontName::Sentence);
        const double messagePosX = sentence.isLookRight() ? -180 : -340;

        Adv::TagStringView::DrawPrev(
            font,
            m_sentence->getPrevMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_sentence->getTime(),
            alpha
        );

        Adv::TagStringView::Draw(
            font,
            sentence.getMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_sentence->getTime(),
            alpha
        );

        if (m_sentence->isInputWait() && !isBusyAnim()) {
            m_cursorView->setPos(pos + s3d::Vec2{ messagePosX + 500, 50 }).draw();
        }
    }
    bool Main::isBusyAnim() const
    {
        return !m_showHideTimer.isEnd();
    }
    bool Main::isVisible() const
    {
        return m_isVisible || isBusyAnim();
    }
    void Main::setVisible(bool isVisible)
    {
        if (m_isVisible == isVisible) {
            return;
        }
        m_isVisible = isVisible;
        m_showHideTimer.reset();
    }
    void Main::animToTail()
    {
        m_showHideTimer.toEnd();
    }
}
