#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual bool onRestart() = 0;
        virtual bool onEscape() = 0;
        virtual bool onClear() = 0;
    };

    /// <summary>
    /// 上位命令クラス
    /// </summary>
    class Master
    {
        // 優先度昇順で通知種類
        enum class Notify : s3d::int8
        {
            None,
            Escape,
            Restart,
            Clear,
        };
    private:
        Notify m_notify = Notify::None;
        IMasterObserver* m_observer = nullptr;
    public:
        Master(IMasterObserver* observer);

        bool notify(Notify notify);
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
        /// 通知を発行する
        /// </summary>
        /// <returns></returns>
        bool sendNotify();
    };
}