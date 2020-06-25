#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/controllers/UI/base/UserInterfaceHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class UI
    {
    private:
        ui::UserInterfaceHolder m_userInterfaces;

        Manager* m_pManager = nullptr;
    public:
        UI& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        void flush();
        void update(double dt);

        void draw() const;

        /// <summary>
        /// UIを登録
        /// </summary>
        /// <param name="ui">ui</param>
        void regist(const std::shared_ptr<ui::IUserInterface>& ui);

        /// <summary>
        /// UIを作成
        /// </summary>
        template<class Type, class... Args>
        Ref<Type> create(Args&& ... args)
            //requires IsUserInterface<Type> && std::constructible_from<Type, Args...>
        {
            auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
            this->regist(obj);
            return obj;
        }

        void setActiveAll(bool isActive);
    };
}