#pragma once
#include <memory>
#include <functional>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    template<class IDrawType>
    class CustomDrawBase :
        public IComponent,
        public IDrawType
    {
    public:
        class IImpl
        {
        public:
            virtual ~IImpl() = default;

            virtual void setup([[maybe_unused]]Executer executer) {}
            virtual void onStart() = 0;
            virtual void onDraw()const = 0;
        };
    private:
        std::unique_ptr<IImpl> m_pImpl;
    public:
        void setup(Executer executer) override
        {
            if (m_pImpl) {
                m_pImpl->setup(executer);
            }
        }

        void onStart() override
        {
            if (m_pImpl) {
                m_pImpl->onStart();
            }
        }

        void onDraw() const override
        {
            if (m_pImpl) {
                m_pImpl->onDraw();
            }
        }

        CustomDrawBase& setDrawer(std::unique_ptr<IImpl>&& drawer)
        {
            m_pImpl = std::move(drawer);
            return *this;
        }

        template<class Impl, class... Args>
        CustomDrawBase& setDrawer(Args&&... args)
        {
            return setDrawer(std::make_unique<Impl>(std::forward<Args>(args)...));
        }
        CustomDrawBase& setDrawer(const std::function<void()>& drawer)
        {
            class Impl : public IImpl
            {
                std::function<void()> m_drawer;
            public:

                Impl(const std::function<void()>& drawer) :
                    m_drawer(drawer)
                {}
                void onStart() override
                {}
                void onDraw() const override
                {
                    if (m_drawer) {
                        m_drawer();
                    }
                }
            };
            m_pImpl = std::make_unique<Impl>(drawer);
            return *this;
        }
    };
}

namespace abyss
{
    template<class IDrawType>
    struct ComponentTree<CustomDrawBase<IDrawType>>
    {
        using Base = IDrawType;
    };
}