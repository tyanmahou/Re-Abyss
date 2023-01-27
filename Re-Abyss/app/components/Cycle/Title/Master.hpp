#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::Title
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;
        virtual bool onGameStart() = 0;
        virtual bool onExit() = 0;
    };

    /// <summary>
    /// 上位命令クラス
    /// </summary>
    class Master final:
        public IComponent,
        public IListener
    {
        enum class Notify : s3d::int8
        {
            None,
            GameStart,
            Exit,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// ゲームスタート
        /// </summary>
        /// <returns></returns>
        bool gameStart();

        /// <summary>
        /// 終了
        /// </summary>
        /// <returns></returns>
        bool exit();

        bool listen() override;

    private:
        bool notify(Notify notify);
    private:
        Notify m_notify = Notify::None;
        IMasterObserver* m_observer = nullptr;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Cycle::Title::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}