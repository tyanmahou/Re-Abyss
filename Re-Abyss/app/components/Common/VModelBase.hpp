#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss
{
    class IVModelPresenterBase
    {
    public:
        virtual ~IVModelPresenterBase() = default;

        virtual void setup([[maybe_unused]] Executer executer) {}
        virtual void onStart() = 0;
        virtual void onDraw() const = 0;
    };

    template<class Type>
    class IVModelPresenter : public IVModelPresenterBase
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

    template<class IDrawType, s3d::uint16 Slot = 0>
    class VModelBase:
        public IComponent,
        public IDrawType
    {
    public:
        void setup(Executer executer) override
        {
            if (m_presenter) {
                m_presenter->setup(executer);
            }
        }

        void onStart() override
        {
            if (m_presenter) {
                m_presenter->onStart();
            }
        }

        void onDraw() const override
        {
            if (!m_isVisible) {
                return;
            }
            if (m_presenter) {
                m_presenter->onDraw();
            }
        }

        VModelBase& setVisible(bool isVisible)
        {
            m_isVisible = isVisible;
            return *this;
        }
        template<class PresenterType, class...Args>
        VModelBase& setPresenter(Args&&... args)
        {
            return setPresenter(std::make_shared<PresenterType>(std::forward<Args>(args)...));
        }
        VModelBase& setPresenter(const std::shared_ptr<IVModelPresenterBase>& presenter)
        {
            m_presenter = presenter;
            return *this;
        }
    private:
        std::shared_ptr<IVModelPresenterBase> m_presenter;
        bool m_isVisible = true;
    };
}

namespace abyss
{
    template<class IDrawType, s3d::uint16 Slot>
    struct ComponentTree<VModelBase<IDrawType, Slot>>
    {
        using Base = IDrawType;
    };
}
