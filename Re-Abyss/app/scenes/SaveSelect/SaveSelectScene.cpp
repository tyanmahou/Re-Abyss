#include "SaveSelectScene.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
namespace abyss
{
    class SaveSelectScene::Impl
    {
        enum class Mode
        {
            GameStart,
            Delete,
        };
        int32 m_selectId = 0;
        Mode m_mode = Mode::GameStart;
    public:
        Impl([[maybe_unused]] const InitData& init)
        {
        }

        void update()
        {
            if (InputManager::Left.down()) {
                --m_selectId;
            }
            if (InputManager::Right.down()) {
                ++m_selectId;
            }
            if (m_selectId < -1) {
                m_selectId = Constants::UserNum - 1;
            } else if(m_selectId >= Constants::UserNum) {
                m_selectId = -1;
            }
        }

        void draw() const
        {
            constexpr Vec2 size{ 800, 300 };
            constexpr Vec2 framePos = Constants::GameScreenSize / 2.0;
            constexpr Vec2 tl = framePos - size / 2.0 + Vec2{0, 50};
            constexpr Vec2 selectSize{ 50.0 , 50.0 };

            // ユーザー番号
            for (int32 userId = 0; userId < Constants::UserNum; ++userId) {
                Vec2 pos = tl + Vec2{ selectSize.x * userId, -selectSize.y };
                RectF(pos, selectSize).drawFrame(1.0);
                FontAsset(U"titleSelect")(U"{}"_fmt(userId + 1)).drawAt(pos + selectSize/2.0);
            }
            // ゴミ箱
            {
                RectF(tl + Vec2{ size.x, 0 } - selectSize, selectSize).drawFrame(1.0);
                RectF(tl, size).drawFrame(1.0);
            }
            if (m_mode == Mode::GameStart) {
                FontAsset(U"titleSelect")(U"- データ選択 -").drawAt(480, 50, Color(0, 255, 255));
            } else {
                FontAsset(U"titleSelect")(U"- データ削除 -").drawAt(480, 50, Color(255, 0, 0));
            }
        }

        void finally()
        {
        }
    };
    SaveSelectScene::SaveSelectScene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
    }

    void SaveSelectScene::update()
    {
        m_pImpl->update();
    }

    void SaveSelectScene::draw() const
    {
        m_pImpl->draw();
    }
    void SaveSelectScene::finally()
    {
        m_pImpl->finally();
    }
}
