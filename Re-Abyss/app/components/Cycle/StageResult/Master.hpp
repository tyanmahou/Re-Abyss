#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::StageResult
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;
        virtual bool onNextScene() = 0;
    };

    /// <summary>
    /// 上位命令クラス
    /// </summary>
    class Master final:
        public IComponent,
        public IListener
    {
        // 優先度昇順で通知種類
        enum class Notify : s3d::int8
        {
            None,
            NextScene,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// 次のシーンへの遷移を予約する
        /// </summary>
        /// <returns></returns>
        bool nextScene();

        bool listen() override;

    private:
        bool notify(Notify notify);
    private:
        Notify m_notify = Notify::None;
        IMasterObserver* m_observer = nullptr;
        std::function<bool()> m_notifyEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Cycle::StageResult::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}
