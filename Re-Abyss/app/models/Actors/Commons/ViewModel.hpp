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
            virtual View* bind(View* view) const = 0;
        };
    private:
        std::unique_ptr<View> m_view;
        std::unique_ptr<IBinder> m_binder;
    public:
        template<class...Args>
        ViewModel(Args&&... args) :
            m_view(std::make_unique<View>(std::forward<Args>(args)...))
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
            if (!m_view) {
                return nullptr;
            }
            if (!m_binder) {
                return m_view.get();
            }
            return m_binder->bind(m_view.get());
        }

        View* operator ->() const
        {
            return this->getBindedView();
        }
    };
}