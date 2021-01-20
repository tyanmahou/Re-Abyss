#pragma once
# include <Siv3D.hpp>

namespace abyss
{
    /// <summary>
    /// 階層管理
    /// </summary>
    class HierarchyManager;

    class IHierarchy : Uncopyable
    {
    private:
        HierarchyManager* m_manager;
    protected:
        template<class Hierarchy, class... Args>
        void push(Args&&... args) const;

    public:
        IHierarchy() = default;
        virtual ~IHierarchy() = default;

        void init(HierarchyManager* manager)
        {
            m_manager = manager;
        }

        virtual void start() {}
        virtual bool update() = 0;
        virtual void draw() const {}
        virtual void onBack(){}
    };

    class HierarchyManager
    {
    private:

        using Hierarchy_t = std::shared_ptr<IHierarchy>;

        std::list<Hierarchy_t> m_list;
        Hierarchy_t m_next;
    public:
        HierarchyManager()
        {}

        void hierarchyUpdate()
        {
            if (m_next) {
                m_next->init(this);
                m_list.push_back(m_next);
                m_next = nullptr;
            }
        }
        void update()
        {
            hierarchyUpdate();

            if (m_list.empty()) {
                return;
            }
            if (!m_list.back()->update()) {
                m_list.pop_back();

                if (!m_list.empty()) {
                    m_list.back()->onBack();
                }
            }
        }
        void draw() const
        {
            for (auto&& h : m_list) {
                h->draw();
            }
        }
        void push(const Hierarchy_t& next)
        {
            m_next = next;
        }

        template<class Hierarchy, class... Args>
        void push(Args&&... args)
        {
            push(std::make_shared<Hierarchy>(std::forward<Args>(args)...));
        }
    };

    template<class Hierarchy, class... Args>
    void IHierarchy::push(Args&&... args) const
    {
        m_manager->push<Hierarchy>(std::forward<Args>(args)...);
    }
}