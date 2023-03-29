#pragma once
#include <memory>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/scenes/Sys/Modules.hpp>
#include <Emaject.hpp>

namespace abyss::Sys2
{
    class System
    {
    public:
        INJECT_CTOR(System(std::shared_ptr<Modules> mods));

        template<class Booter, class... Args>
        bool boot(Args&&... args) const
            requires std::derived_from<Booter, IBooter> && std::constructible_from<Booter, Args...>
        {
            return this->boot(Booter(std::forward<Args>(args)...));
        }
        bool boot(const IBooter& booter) const;

        void update();

        void draw() const;

        template<class Mod>
        inline Mod* mod() const
        {
            return m_mods->get<Mod>();
        }
    private:
        template<class Mod, class R, class... Args>
        void call(R(Mod::* func)(Args ...), Args...args) const
        {
            if (auto* m = mod<Mod>()) {
                (m->*func)(args...);
            }
        }
        template<class Mod, class R, class... Args>
        void call(R(Mod::* func)(Args ...) const, Args...args) const
        {
            if (auto* m = mod<Mod>()) {
                (m->*func)(args...);
            }
        }
        template<class Mod, class R, class... Args>
        void call(R(func)(Mod&, Args ...), Args...args) const
        {
            if (auto* m = mod<Mod>()) {
                func(*m, args...);
            }
        }
        template<class Mod, class R, class... Args>
        void call(R(func)(const Mod&, Args ...), Args...args) const
        {
            if (auto* m = mod<Mod>()) {
                func(*m, args...);
            }
        }
    private:
        Manager m_manager;

        std::shared_ptr<Modules> m_mods;
    };
}
