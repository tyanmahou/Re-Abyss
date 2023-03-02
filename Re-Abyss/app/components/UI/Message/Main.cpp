#include <abyss/components/UI/Message/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Adv/Adventures.hpp>

#include <abyss/modules/Adv/base/Engine.hpp>

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
        const Ref<Adv::Engine>& engine
    ) :
        m_pUi(pUi),
        m_engine(engine),
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
        if (!m_engine) {
            m_pUi->destroy();
            return;
        }
        m_showHideTimer.update(m_pUi->deltaTime());
    }

    void Main::onDraw() const
    {
        if (!m_engine) {
            return;
        }
        if (!isVisible()) {
            return;
        }
        const auto& serif = m_engine->getSerif();

        const auto rate = m_isVisible ?
            s3d::EaseOutCubic(m_showHideTimer.rate()) :
            s3d::EaseInCubic(m_showHideTimer.invRate());
        const auto alpha = rate;
        const Vec2 pos = AnchorUtil::FromTc(0, 150) + Vec2{0.0, (1.0 - rate) * -40.0};
        m_boxView
            ->setIsLeft(serif.isLookRight()) // 向きとアイコンの位置は反転するのでIsLeftにisRightを設定している
            .setPos(pos)
            .setName(serif.getName())
            .setAlpha(alpha);

        auto* advs = m_pUi->getModule<Adventures>();
        if (auto chara = advs->findChara(serif.getKind())) {
            if (auto face = chara->getFace(serif.getEmote())) {
                m_boxView->setFaceIcon(face);
            } else {
                m_boxView->setFaceIcon({});
            }
        } else {
            m_boxView->setFaceIcon({});
        }
        m_boxView->draw();

        auto&& font = FontAsset(FontName::Serif);
        const double messagePosX = serif.isLookRight() ? -180 : -340;

        Adv::TagStringView::DrawPrev(
            font,
            m_engine->getPrevMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_engine->getTime(),
            alpha
        );

        Adv::TagStringView::Draw(
            font,
            serif.getMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_engine->getTime(),
            alpha
        );

        if (m_engine->isInputWait() && !isBusyAnim()) {
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
