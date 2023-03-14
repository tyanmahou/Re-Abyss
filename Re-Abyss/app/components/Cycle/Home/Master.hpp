#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Cycle/base/IListener.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Cycle::Home
{
    /// <summary>
    /// マスター観測者
    /// </summary>
    class IMasterObserver
    {
    public:
        virtual ~IMasterObserver() = default;

        virtual bool onStageStart(const s3d::String& mapPath) = 0;
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
            StageStart,
            Back,
        };
    public:
        Master(IMasterObserver* observer);

        /// <summary>
        /// ステージ開始
        /// </summary>
        /// <returns></returns>
        bool stageStart(const s3d::String& mapPath);

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
        std::function<bool()> m_notifyEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Cycle::Home::Master>
    {
        using Base = MultiComponents<Cycle::IListener>;
    };
}
