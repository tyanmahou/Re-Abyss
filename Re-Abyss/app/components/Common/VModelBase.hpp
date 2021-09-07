#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>

namespace abyss
{
    class IVModelBinderBase
    {
    public:
        virtual ~IVModelBinderBase() = default;

        virtual void setup([[maybe_unused]] Executer executer) {}
        virtual void onStart() = 0;
        virtual void onDraw() const = 0;
    };

    template<class Type>
    class IVModelBinder : public IVModelBinderBase
    {
    public:
        virtual Type* bind() const = 0;

        void onDraw() const final
        {
            if (auto* view = this->bind()) {
                view->draw();
            }
        }
    };

    template<class IDrawType>
    class VModelBase:
        public IComponent,
        public IDrawType
    {
    public:
        void setup(Executer executer) override
        {
            if (m_binder) {
                m_binder->setup(executer);
            }
        }

        void onStart() override
        {
            if (m_binder) {
                m_binder->onStart();
            }
        }

        void onDraw() const override
        {
            if (m_binder) {
                m_binder->onDraw();
            }
        }

        template<class BinderType, class...Args>
        VModelBase& setBinder(Args&&... args)
        {
            return setBinder(std::make_shared<BinderType>(std::forward<Args>(args)...));
        }
        VModelBase& setBinder(const std::shared_ptr<IVModelBinderBase>& binder)
        {
            m_binder = binder;
            return *this;
        }
    private:
        std::shared_ptr<IVModelBinderBase> m_binder;
    };
}

namespace abyss
{
    template<class IDrawType>
    struct ComponentTree<VModelBase<IDrawType>>
    {
        using Base = IDrawType;
    };
}