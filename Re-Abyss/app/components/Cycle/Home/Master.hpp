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
        };
    public:
        Master(IMasterObserver* observer);

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
