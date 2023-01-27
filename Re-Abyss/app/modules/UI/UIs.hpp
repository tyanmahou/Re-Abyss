#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/UI/base/UIHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI
{
    template<class Type, class... Args>
    concept UIBuildable = requires(UI::UIObj * pUi, Args&&... args)
    {
        Type::Build(pUi, std::forward<Args>(args)...);
    };

    class UIs
    {
    private:
        UIHolder m_userInterfaces;

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
        Ref<UIObj> create();

        /// <summary>
        /// ビルダーからUIの作成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<UIObj> create(Args&& ... args)
            requires UIBuildable<BuilerType, Args...>
        {
            auto ui = this->create();
            BuilerType::Build(ui.get(), std::forward<Args>(args)...);
            return ui;
        }

        /// <summary>
        /// UIを登録
        /// </summary>
        /// <param name="ui">ui</param>
        Ref<UIObj> regist(const std::shared_ptr<UIObj>& ui);

        /// <summary>
        /// フィルタをセットする
        /// </summary>
        /// <param name="filter"></param>
        void setFilter(const Filter& filter);
    };
}
