#pragma once
#include <stack>
#include <abyss/scenes/Sequence/ISequence.hpp>
#include <abyss/scenes/base/ISceneBase.hpp>

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
        void changeScene(const SceneKind& state, s3d::int32 transitionTimeMillisec = 0, const s3d::CrossFade crossFade = s3d::CrossFade::No);

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

        void pushSequence(std::shared_ptr<ISequence> child);
    private:
        AppScene m_scene;
        std::stack<std::shared_ptr<ISequence>> m_sequence;
    };
}
