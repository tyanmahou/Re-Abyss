#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IPostUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Hierarchy/Hierarchy.hpp>

namespace abyss::UI
{
    class HierarchyCtrl :
        public IComponent,
        public IPostUpdate,
        public IDraw
    {
    public:
        HierarchyCtrl(UIObj* pUi);

        void setup(Executer executer) override;
        void onStart() override;
        void onPostUpdate() override;
        void onDraw() const override;

        HierarchyCtrl& setupCallback(const std::function<void(Executer)>& callback)
        {
            m_setupCallback = callback;
            return *this;
        }
        void push(const HierarchyManager::Hierarchy_t& next);

        template<class Hierarchy, class... Args>
        void push(Args&&... args)
        {
            push(std::make_shared<Hierarchy>(std::forward<Args>(args)...));
        }
    private:
        UIObj* m_pUi;
        HierarchyManager m_manager;

        std::function<void(Executer)> m_setupCallback;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::HierarchyCtrl>
    {
        using Base = MultiComponents<UI::IPostUpdate, UI::IDraw>;
    };
}