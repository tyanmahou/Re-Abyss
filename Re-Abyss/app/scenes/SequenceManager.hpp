#pragma once
#include <stack>
#include <abyss/scenes/Sequence/ISequence.hpp>
#include <abyss/scenes/Scene/SceneManager.hpp>

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

        void changeScene(const SceneKind& state, s3d::int32 transitionTimeMillisec = 0, const s3d::CrossFade crossFade = s3d::CrossFade::No);

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
    private:
        bool changeNext();

        void changeSequence(std::shared_ptr<ISequence> child);
        void pushSequence(std::shared_ptr<ISequence> child);
    private:
        SceneManager m_scene;
        std::stack<std::shared_ptr<ISequence>> m_sequence;
        bool m_isExit = false;
    };
}
