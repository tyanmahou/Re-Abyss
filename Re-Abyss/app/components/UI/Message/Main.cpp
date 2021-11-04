#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Novel/Novels.hpp>

#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/views/UI/Message/MessageBoxVM.hpp>
#include <abyss/views/UI/Message/CursorVM.hpp>
#include <abyss/views/Novel/TagString/TagStringView.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Message
{
    Main::Main(
        UIObj* pUi,
        const Ref<Novel::Engine>& engine
    ) :
        m_pUi(pUi),
        m_engine(engine),
        m_boxView(std::make_unique<MessageBoxVM>()),
        m_cursorView(std::make_unique<CursorVM>())
    {}

    void Main::onStart()
    {}

    void Main::onUpdate()
    {
        if (!m_engine) {
            m_pUi->destroy();
            return;
        }
    }

    void Main::onDraw() const
    {
        if (!m_engine) {
            return;
        }
        const auto& serif = m_engine->getSerif();

        const Vec2 pos = PivotUtil::FromTc(0, 150);
        m_boxView
            ->setIsLeft(serif.isLeft())
            .setPos(pos)
            .setName(serif.getName());

        auto* novels = m_pUi->getModule<Novels>();
        if (auto chara = novels->findChara(serif.getKind())) {
            if (auto face = chara->getFace(serif.getFace())) {
                m_boxView->setFaceIcon(face);
            } else {
                m_boxView->setFaceIcon({});
            }
        } else {
            m_boxView->setFaceIcon({});
        }
        m_boxView->draw();

        auto&& font = FontAsset(FontName::Serif);
        const double messagePosX = serif.isLeft() ? -180 : -340;

        Novel::TagStringView::DrawPrev(
            font,
            m_engine->getPrevMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_engine->getTime()
        );

        Novel::TagStringView::Draw(
            font,
            serif.getMessage(),
            pos + s3d::Vec2{ messagePosX, -25 },
            m_engine->getTime()
        );

        if (m_engine->isInputWait()) {
            m_cursorView->setPos(pos + s3d::Vec2{ messagePosX + 500, 50 }).draw();
        }
    }
}