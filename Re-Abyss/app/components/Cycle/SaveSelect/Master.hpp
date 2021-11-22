#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::SaveSelect
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;

        virtual bool onNewGame() = 0;
        virtual bool onLoadGame() = 0;
        virtual bool onBack() = 0;
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
            NewGame,
            LoadGame,
            Back,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// ニューゲーム
        /// </summary>
        /// <returns></returns>
        bool newGame();

        /// <summary>
        /// ロードゲーム
        /// </summary>
        /// <returns></returns>
        bool loadGame();

        /// <summary>
        /// 戻る
        /// </summary>
        /// <returns></returns>
        bool back();

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
    struct ComponentTree<Cycle::SaveSelect::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}