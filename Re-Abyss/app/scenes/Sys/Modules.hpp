#pragma once
#include <abyss/scenes/Sys/ModulePackage.hpp>
#include <Emaject.hpp>

namespace abyss::Sys
{
    template<class Mod>
    concept Managed = requires(Mod * pMod, Manager * pManager)
    {
        pManager->set(pMod);
    };

    template<class Mod>
    concept SetManagerable = requires(Mod * pMod, Manager * pManager)
    {
        pMod->setManager(pManager);
    };

    /// <summary>
    /// モジュール
    /// </summary>
    class Modules
    {
        friend struct emaject::InjectTraits<Modules>;
    public:
        Modules() = default;

        template<class Mod>
        inline Mod* get() const
        {
            return std::get<std::shared_ptr<Mod>>(m_modules).get();
        }

        void setManager(Manager* pManager)
        {
            auto set = [pManager]<class Mod>(std::shared_ptr<Mod>&mod) {
                if (mod) {
                    if constexpr (Managed<Mod>) {
                        pManager->set(mod.get());
                    }
                    if constexpr (SetManagerable<Mod>) {
                        mod->setManager(pManager);
                    }
                }
            };
            std::apply([=]<class... T>(T&... m) {
                (set(m), ...);
            }, m_modules);
        }
    private:
        ModulePackage m_modules;
    };
}
namespace emaject
{
    template<>
    struct InjectTraits<abyss::Sys::Modules>
    {
        void onInject(abyss::Sys::Modules* value, Container* c)
        {
            std::apply([=]<class... T>(T&... m) {
                ((m = c->resolve<typename T::element_type>()), ...);
            }, value->m_modules);
        }
    };
}
