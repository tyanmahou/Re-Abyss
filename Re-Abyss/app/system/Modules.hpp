#pragma once
#include <tuple>
#include <memory>
#include <abyss/concepts/Module.hpp>
#include <abyss/utils/Meta/RemoveParam.hpp>

namespace abyss::Sys
{
    /// <summary>
    /// モジュール
    /// </summary>
    template<class... Mods>
    class Modules
    {
    public:
        Module(Manager* pManager)
        {
            // 初期化 / Manager設定
            (this->createMod<Mods>(pManager)...);
        }
        template<class Mod>
        Mod* get()
        {
            return std::get<Mod>(m_modules).get();
        }
    private:
        template <class Mod>
        void createMod(Manager* pManager)
        {
            auto& mod = std::get<Mod>(m_modules);
            mods = std::make_unique<Mods>();

            if constexpr (Managed<Mod>) {
                pManager->set(mod.get());
            }
            if constexpr (SetManagerable<Mod>) {
                mod->setManager(pManager);
            }
        }
    private:
        std::tuple<
            std::unique_ptr<Mods>...
        > m_modules;
    };
}