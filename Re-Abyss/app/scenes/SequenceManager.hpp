#pragma once
#include <stack>
#include <abyss/scenes/Sequence/ISequence.hpp>
#include <abyss/scenes/Scene/SceneManager.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss
{
    /// <summary>
    /// シーケンス管理
    /// </summary>
    class SequenceManager
    {
    public:
        SequenceManager();

        bool update();

        /// <summary>
        /// 終了
        /// </summary>
        void exit();

        void changeScene(const SceneKind& state);

        template<class SequenceType, class... Args>
        void changeSequence(Args&&... args)
        {
            this->changeSequence(std::make_shared<SequenceType>(std::forward<Args>(args)...));
        }
        template<class SequenceType, class... Args>
        void pushSequence(Args&&... args)
        {
            this->pushSequence(std::make_shared<SequenceType>(std::forward<Args>(args)...));
        }

        const SceneResultHolder& getResult() const;
        template<class Result>
        Result getResult() const
        {
            return std::get<Result>(this->getResult());
        }

        SequecneData* data();
        const SequecneData* data() const;

        template<class Context, class Result>
        Coro::Fiber<Result> changeScene(const SceneKind& state, Context&& context)
        {
            data()->context = std::forward<Context>(context);

            return this->changeScene<Result>(state);
        }

        template<class Result>
        Coro::Fiber<Result> changeScene(const SceneKind& state)
        {
            this->changeScene(state);
            co_yield{};
            if constexpr (std::is_void_v<Result>) {
                co_return;
            } else {
                co_return this->getResult<Result>();
            }
        }
    private:
        bool updateScene();
        void drawScene() const;
        bool changeNext();

        void changeSequence(std::shared_ptr<ISequence> child);
        void pushSequence(std::shared_ptr<ISequence> child);
    private:
        SceneManager m_scene;
        std::stack<std::shared_ptr<ISequence>> m_sequence;
        bool m_isExit = false;
    };
}
