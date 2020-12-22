#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/modules/UI/base/UserInterfaceHolder.hpp>
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

        void update();

        void draw() const;

        /// <summary>
        /// UIの生成
        /// </summary>
        /// <returns></returns>
        Ref<ui::IUserInterface> create();

        /// <summary>
        /// ビルダーからUIの作成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<ui::IUserInterface> create(Args&& ... args)
            requires UIBuildy<BuilerType, Args...>
        {
            auto ui = this->create();
            BuilerType::Build(ui.get(), std::forward<Args>(args)...);
            return ui;
        }

        /// <summary>
        /// UIを登録
        /// </summary>
        /// <param name="ui">ui</param>
        Ref<ui::IUserInterface> regist(const std::shared_ptr<ui::IUserInterface>& ui);

        void setActiveAll(bool isActive);
    };
}