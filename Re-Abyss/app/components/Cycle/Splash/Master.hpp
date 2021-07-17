#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::Splash
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;
        virtual bool chageOpDemoScene() = 0;
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
            ChageOpDemoScene,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// エスケープ通知を予約する
        /// </summary>
        /// <returns></returns>
        bool chageOpDemoScene();

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
    struct ComponentTree<Cycle::Splash::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}