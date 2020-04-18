#pragma once
#include <memory>
#include <functional>
#include <any>
#include <unordered_map>
#include <typeindex>

namespace abyss
{
    class DIContainer
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;

        template<class Type>
        using Ref = std::shared_ptr<Type>;
        template<class Type>
        using CreateFunc = std::function<Ref<Type>(const DIContainer*)>;
    public:
        DIContainer();

        template<class Type>
        void regist(const CreateFunc<Type>& func) const;

        template<class Type>
        std::shared_ptr<Type> build() const;

        template<class Type>
        std::shared_ptr<Type> get() const;
    };

    class DIContainer::Impl
    {
        std::unordered_map<std::type_index, std::any> m_createFuncs;
        std::unordered_map<std::type_index, std::any> m_instanceCache;
    public:
        template<class Type>
        void regist(const CreateFunc<Type>& func)
        {
            if (m_createFuncs.find(typeid(Type)) != m_createFuncs.end()) {
                return;
            }
            m_createFuncs[typeid(Type)] = func;
        }

        template<class Type>
        std::shared_ptr<Type> build(const DIContainer* c) const
        {
            const auto& id = typeid(Type);
            if (m_createFuncs.find(id) == m_createFuncs.end()) {
                return nullptr;
            }
            auto func = std::any_cast<CreateFunc<Type>>(m_createFuncs.at(id));
            return func(c);
        }

        template<class Type>
        std::shared_ptr<Type> get(const DIContainer* c)
        {
            const auto& id = typeid(Type);
            if (m_instanceCache.find(id) != m_instanceCache.end()) {
                return std::any_cast<Ref<Type>>(m_instanceCache[id]);
            }
            auto ret = this->build<Type>(c);
            m_instanceCache[id] = ret;
            return ret;
        }
    };

    template<class Type>
    void DIContainer::regist(const CreateFunc<Type>& func) const
    {
        m_pImpl->regist<Type>(func);
    }

    template<class Type>
    std::shared_ptr<Type> DIContainer::build() const
    {
        return m_pImpl->build<Type>(this);
    }

    template<class Type>
    std::shared_ptr<Type> DIContainer::get() const
    {
        return m_pImpl->get<Type>(this);
    }
}