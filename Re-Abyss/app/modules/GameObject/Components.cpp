#include <abyss/modules/GameObject/Components.hpp>
#include <unordered_map>
#include <ranges>

#include <abyss/modules/GameObject/ExecuteSorter.hpp>

#include <abyss/debugs/Log/Log.hpp>
namespace abyss
{
    class Components::Impl
    {
        std::unordered_map<std::type_index, std::shared_ptr<IComponent>> m_table;
        std::unordered_map<std::type_index, s3d::Array<Ref<IComponent>>> m_tree;
    public:
        void setup()
        {
            detail::ExecuteSorter sorter;
            for (auto&& com : m_tree[typeid(IComponent)]) {

                Executer executer;
                com->setup(executer);

                sorter.regist(com.get(), executer);
            }
            // 依存関係からソートする
            for (auto& pair : m_tree) {
                if (pair.second.size() <= 1) {
                    // ソート不要
                    continue;
                }
                pair.second = sorter.sort(pair.first, pair.second);
            }
        }
        void start()
        {
            for (auto&& com : m_tree[typeid(IComponent)]) {
                com->onStart();
            }
        }
        void end()
        {
            for (auto&& com : m_tree[typeid(IComponent)] | std::ranges::views::reverse) {
                com->onEnd();
            }
        }
        bool add(const std::type_index& key, const std::shared_ptr<IComponent>& component)
        {
            if (m_table.find(key) != m_table.end()) [[unlikely]] {
#if ABYSS_DEBUG
                Debug::Log::Warn(U"Multi Component: {}"_fmt(s3d::Unicode::Widen(key.name())));
#endif
                return false;
            }
            // IComponentには絶対登録
            m_tree[typeid(IComponent)].push_back(component);
            m_table[key] = component;
            return true;
        }
        bool remove(const std::type_index& key)
        {
            if (m_table.find(key) == m_table.end()) [[unlikely]] {
                return false;
            }
            m_table.erase(key);

            // treeからも削除
            for (auto&& [k, coms] : m_tree) {
                coms.remove_if([](const auto& c) {
                    return !c;
                });
            }
            return true;
        }
        void registTree(const std::type_index& key, const Ref<IComponent>& component)
        {
            m_tree[key].push_back(component);
        }

        const s3d::Array<Ref<IComponent>>& finds(const std::type_index& key)
        {
            return m_tree[key];
        }
        Ref<IComponent> find(const std::type_index& key)
        {
            const auto& coms = this->finds(key);
            if (coms.isEmpty()) {
                return nullptr;
            }
            return coms[0];
        }
    };

    Components::Components():
        m_pImpl(std::make_shared<Impl>())
    {}

    bool Components::add(const std::type_index& key, const std::shared_ptr<IComponent>& component)const
    {
        return m_pImpl->add(key, component);
    }

    bool Components::remove(const std::type_index& key)const
    {
        return m_pImpl->remove(key);
    }

    Ref<IComponent> Components::find(const std::type_index& key) const
    {
        return m_pImpl->find(key);
    }

    const s3d::Array<Ref<IComponent>>& Components::finds(const std::type_index& key) const
    {
        return m_pImpl->finds(key);
    }

    void Components::setup() const
    {
        m_pImpl->setup();
    }

    void Components::start() const
    {
        m_pImpl->start();
    }

    void Components::end() const
    {
        m_pImpl->end();
    }

    void Components::registTree(const std::type_index& key, const std::shared_ptr<IComponent>& component) const
    {
        m_pImpl->registTree(key, component);
    }
}
