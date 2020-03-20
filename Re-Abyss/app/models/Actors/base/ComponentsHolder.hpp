#pragma once
#include<memory>
#include<Siv3D/Array.hpp>
#include<abyss/models/Actors/base/IComponent.hpp>

namespace abyss
{
    class ComponentsHolder
    {
        s3d::Array<std::shared_ptr<IComponent>> m_components;
    public:

        void setup()
        {
            for (auto&& com : m_components) {
                com->setup();
            }
        }

        template<class T, class ... Args>
        std::shared_ptr<T> add(Args&&... args)
        {
            auto com = std::make_shared<T>(std::forward<Args>(args)...);
            m_components.push_back(com);
            return com;
        }

        template<class T>
        std::shared_ptr<T> getRef() const
        {
            for (auto&& com : m_components) {
                if (auto dCom = std::dynamic_pointer_cast<T>(com)) {
                    return dCom;
                }
            }
            return nullptr;
        }
        template<class T>
        T* get() const
        {
            for (auto&& com : m_components) {
                if (auto dCom = dynamic_cast<T*>(com.get())) {
                    return dCom;
                }
            }
            return nullptr;
        }
    };
}