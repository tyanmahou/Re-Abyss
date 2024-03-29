#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Cycle/base/IListener.hpp>
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

        virtual bool onNewGame(s3d::int32 userId) = 0;
        virtual bool onLoadGame(s3d::int32 userId) = 0;
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
        bool newGame(s3d::int32 userId);

        /// <summary>
        /// ロードゲーム
        /// </summary>
        /// <returns></returns>
        bool loadGame(s3d::int32 userId);

        /// <summary>
        /// 戻る
        /// </summary>
        /// <returns></returns>
        bool back();

        bool listen() override;

    private:
        bool notify(Notify notify, s3d::int32 userId);
    private:
        Notify m_notify = Notify::None;
        s3d::int32 m_userId = 0;
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
