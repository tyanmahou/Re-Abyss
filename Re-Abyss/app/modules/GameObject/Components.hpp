#pragma once
#include <memory>
#include <typeindex>
#include <concepts>
#include <Siv3D/Array.hpp>

#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/GameObject/ComponentMapping.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
    class Components
    {
    public:
        class Impl;
    private:
        bool add(const std::type_index& key, const std::shared_ptr<IComponent>& component) const;
        bool remove(const std::type_index& key) const;

        Ref<IComponent> find(const std::type_index& key) const;
        const s3d::Array<Ref<IComponent>>& finds(const std::type_index& key) const;
        void registTree(const std::type_index& key, const std::shared_ptr<IComponent>& component) const;
    public:
        Components();

        void setup() const;

        void start() const;

        void end() const;

        template<class Component>
        Ref<Component> add(const std::shared_ptr<Component>& component) const
            requires IsComponent<Component>
        {
            if (!add(typeid(Component), component)) {
                return this->find<Component>();
            }
            for (auto index : CompoentMappingIdexes<Component>()) {
                registTree(index, component);
            }
            return Ref<Component>(component);
        }

        template<class Component, class... Args>
        Ref<Component> add(Args&&... args) const
            requires
            IsComponent<Component> &&
            std::constructible_from<Component, Args...>
        {
            return add(std::make_shared<Component>(std::forward<Args>(args)...));
        }

        template<class Component>
        bool remove() const
            requires IsComponent<Component>
        {
            return remove(typeid(Component));
        }

        template<class Component>
        [[nodiscard]] Ref<Component> find() const
        {
            if (auto c = find(typeid(Component))) {
                return RefCast<Component>(c);
            }
            return nullptr;
        }

        template<class Component>
        [[nodiscard]] s3d::Array<Ref<Component>> finds() const
        {
            s3d::Array<Ref<Component>> ret;
            for (const auto& c : this->finds(typeid(Component))) {
                if (!c) {
                    continue;
                }
                ret.push_back(RefCast<Component>(c));
            }
            return ret;
        }

        Ref<Impl> getHandle() const
        {
            return m_pImpl;
        }
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}