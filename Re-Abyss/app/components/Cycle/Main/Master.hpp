#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::Main
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;
        virtual bool onRestart() = 0;
        virtual bool onMoveStage(const s3d::String& link, s3d::int32 startId) = 0;
        virtual bool onEscape() = 0;
        virtual bool onClear() = 0;
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
            Escape,
            Restart,
            Clear,
            MoveStage,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// エスケープ通知を予約する
        /// </summary>
        /// <returns></returns>
        bool escape();

        /// <summary>
        /// リスタート通知を予約する
        /// </summary>
        /// <returns></returns>
        bool restart();

        /// <summary>
        /// クリア通知を予約する
        /// </summary>
        /// <returns></returns>
        bool clear();

        /// <summary>
        /// マップ移動を予約する
        /// </summary>
        /// <returns></returns>
        bool moveStage(const s3d::String& link, s3d::int32 startId);

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
    struct ComponentTree<Cycle::Main::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}
