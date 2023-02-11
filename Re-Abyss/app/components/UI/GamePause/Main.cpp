#include <abyss/components/UI/GamePause/Main.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::GamePause
{
    void Main::Build(UIObj* pUi)
    {
        pUi->setFilter(UI::Filter::Always);
        pUi->attach<Main>(pUi)
            ->setOrder(DrawOrder::UI::Pause);

    }
    Main::Main(UIObj* pUi):
        m_pUi(pUi),
        m_bg(std::make_unique<UI::GamePause::BackGround::BackGroundVM>()),
        m_cursor(std::make_unique<UI::Message::CursorVM>())
    {
        m_state.reset(std::bind(&Main::stateSelect, this));
    }
    Main::~Main()
    {
    }
    void Main::onStart()
    {
    }
    void Main::onUpdate()
    {
        m_state.resume();
    }
    void Main::onDraw() const
    {
        m_bg->setBgColor(ColorF(0.5, 0.7)).draw();
        {
            FontAsset(FontName::SceneName)(U"- Pause -").drawAt(AnchorUtil::FromTc(0, 50), Color(0, 255, 255));

            const Vec2 basePos = AnchorUtil::FromCc({0, 0});
            const Vec2 boardSize = { 500, 270};
            const auto board = RectF{ basePos - boardSize / 2, boardSize };
            board.draw(Palette::Black);

            auto choicePos = board.center() + Vec2{ 0, -30 };
            FontAsset(FontName::UserInfo)(U"ゲームをつづける").drawAt(choicePos);
            FontAsset(FontName::UserInfo)(U"ゲームをやめる").drawAt(choicePos + Vec2{ 0, 40 });

            {
                Vec2 pos = choicePos +
                    Vec2{
                    -100,
                    m_isSelectContinue ? 0 : 40
                };

                m_cursor->setVertical(false)
                    .setPos(pos)
                    .draw();
            }

        }
    }
    Coro::Fiber<> Main::stateSelect()
    {
        while (true) {
            // カーソル移動
            if (InputManager::Up.down()) {
                m_isSelectContinue = true;
            } else if (InputManager::Down.down()) {
                m_isSelectContinue = false;
            }

            // 決定
            if (InputManager::Start.down()) {
                DialogResult::set({
                    .isContinue = true
                });
                co_return;
            } else if (InputManager::A.down()) {
                DialogResult::set({
                    .isContinue = m_isSelectContinue
                });
                co_return;
            }

            co_yield{};
        }
    }
}
