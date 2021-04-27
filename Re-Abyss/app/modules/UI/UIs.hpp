#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/modules/UI/base/UIHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class UIs
    {
    private:
        UI::UIHolder m_userInterfaces;

        Manager* m_pManager = nullptr;
    public:
        UIs& setManager(Manager* pManager)
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
        Ref<UI::UIObj> create();

        /// <summary>
        /// ビルダーからUIの作成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<UI::UIObj> create(Args&& ... args)
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
        Ref<UI::UIObj> regist(const std::shared_ptr<UI::UIObj>& ui);

        void setActiveAll(bool isActive);
    };
}