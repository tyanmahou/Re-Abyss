#pragma once
#include <memory>
#include <abyss/models/Actors/base/IComponent.hpp>

namespace abyss
{
    template<class View>
    class ViewModel : public IComponent
    {
    public:
        class IBinder
        {
        public:
            virtual ~IBinder() = default;

            virtual void setup() = 0;
            virtual View* bind() const = 0;
        };
    private:
        std::unique_ptr<IBinder> m_binder;
    public:
        ViewModel()
        {

        }
        void setup()override
        {
            if (m_binder) {
                m_binder->setup();
            }
        }
        template<class BinderType, class...Args>
        void createBinder(Args&&... args)
        {
            m_binder = std::make_unique<BinderType>(std::forward<Args>(args)...);
        }
        void setBinder(std::unique_ptr<IBinder>&& binder)
        {
            m_binder = std::move(binder);
        }

        View* getBindedView() const
        {
            if (!m_binder) {
                return nullptr;
            }
            return m_binder->bind();
        }

        View* operator ->() const
        {
            return this->getBindedView();
        }
    };
}