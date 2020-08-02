#pragma once
#include <memory>
#include <typeindex>
#include <concepts>
#include <Siv3D/Array.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
    class Components;

    namespace detail
    {
        
        template<class T>
        struct MappingComponentTree
        {
            void mapping(const Components* c, const std::shared_ptr<IComponent>& component);
        };

        template<class ...Args>
        struct MappingComponentTree<MultiComponents<Args...>>
        {
            void mapping(const Components* c, const std::shared_ptr<IComponent>& component)
            {
                (MappingComponentTree<Args>{}.mapping(c, component), ...);
            }
        };
    }

    class Components
    {
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;

        bool add(const std::type_index& key, const std::shared_ptr<IComponent>& component) const;
        bool remove(const std::type_index& key) const;

        Ref<IComponent> find(const std::type_index& key) const;
        const s3d::Array<Ref<IComponent>>& finds(const std::type_index& key) const;
    public:
        Components();

        void setup() const;

        void start() const;

        void registTree(const std::type_index& key, const Ref<IComponent>& component) const;

        template<class Component>
        Ref<Component> add(const std::shared_ptr<Component>& component) const
            requires IsComponent<Component>
        {
            if (!add(typeid(Component), component)) {
                return this->find<Component>();
            }
            detail::MappingComponentTree<Component>{}.mapping(this, component);
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
    };

    namespace detail
    {
        template<class T>
        void MappingComponentTree<T>::mapping(const Components* c, const std::shared_ptr<IComponent>& component)
        {
            c->registTree(typeid(T), component);
            if constexpr (HasBaseComponent<T>) {
                MappingComponentTree<typename ComponentTree<T>::Base>{}.mapping(c, component);
            }
        }
    }
}