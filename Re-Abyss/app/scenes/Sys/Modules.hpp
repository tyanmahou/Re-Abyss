#pragma once
#include <abyss/scenes/Sys/ModulePackage.hpp>
#include <Emaject.hpp>

namespace abyss::Sys2
{
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
    private:
        ModulePackage m_modules;
    };
}
namespace emaject
{
    template<>
    struct InjectTraits<abyss::Sys2::Modules>
    {
        void onInject(abyss::Sys2::Modules* value, Container* c)
        {
            std::apply([=]<class... T>(T&... m) {
                ((m = c->resolve<typename T::element_type>()), ...);
            }, value->m_modules);
        }
    };
}
