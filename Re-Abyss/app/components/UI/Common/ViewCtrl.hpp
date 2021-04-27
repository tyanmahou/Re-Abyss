#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::UI
{
    template<class View>
    class ViewCtrl : public IComponent
    {
    public:
        class IBinder
        {
        public:
            virtual ~IBinder() = default;

            virtual void setup([[maybe_unused]] Executer executer){}
            virtual void onStart() = 0;
            virtual View* bind() const = 0;
        };
    private:
        std::unique_ptr<IBinder> m_binder;
    public:
        ViewCtrl()
        {

        }
        void setup(Executer executer)override
        {
            if (m_binder) {
                m_binder->setup(executer);
            }
        }
        void onStart()override
        {
            if (m_binder) {
                m_binder->onStart();
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