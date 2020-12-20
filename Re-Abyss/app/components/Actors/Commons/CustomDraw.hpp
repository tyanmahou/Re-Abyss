#pragma once
#include <memory>
#include <functional>
#include <Siv3D/String.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDraw.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    class CustomDraw :
        public IComponent,
        public IDraw
    {
    public:
        class IImpl
        {
        public:
            virtual ~IImpl() = default;

            virtual void onStart() = 0;
            virtual void onDraw()const = 0;
        };
    private:
        std::unique_ptr<IImpl> m_pImpl;
    public:
        void setup(Depends depends) override;

        void onStart() override;

        void onDraw() const override;

        CustomDraw& setDrawer(std::unique_ptr<IImpl>&& drawer);

        template<class Impl, class... Args>
        CustomDraw& setDrawer(Args&&... args)
        {
            return setDrawer(std::make_unique<Impl>(std::forward<Args>(args)...));
        }
        CustomDraw& setDrawer(const std::function<void()>& drawer);
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CustomDraw>
    {
        using Base = Actor::IDraw;
    };
}