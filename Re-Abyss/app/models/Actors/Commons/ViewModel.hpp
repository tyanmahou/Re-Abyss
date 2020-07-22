#pragma once
#include <memory>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss
{
    template<class View>
    class ViewModel
    {
    public:
        class IBinder
        {
        public:
            virtual ~IBinder() = default;
            View* bind(View* view) const = 0;
        };
    private:
        IActor* m_pActor;
        std::unique_ptr<View> m_view;
        std::unique_ptr<IBinder> m_binder;
    public:
        
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
    };
}