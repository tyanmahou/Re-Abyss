#pragma once
#include <Emaject.hpp>

// Modules
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/ColSys/CollisionManager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/Devs/Project/Project.hpp>
#include <abyss/modules/Devs/WorldComment/WorldComment.hpp>
#include <abyss/modules/Distortion/Distortion.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/FieldEnv/Environment.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Adv/Adventures.hpp>
#include <abyss/modules/Pause/PauseManager.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/UI/UIs.hpp>

namespace abyss::Sys2
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
        template<class... T>
        using Packages = std::tuple<std::shared_ptr<T>...>;
    public:
        Modules() = default;

        template<class Mod>
        inline Mod* get() const
        {
            return std::get<std::shared_ptr<Mod>>(m_modules).get();
        }

        void setManager(Manager* pManager)
        {
            std::apply([=](const auto&... m) {
                (setManager(pManager, m), ...);
            }, m_modules);
        }
    private:
        template<class T>
        void setManager(Manager* pManager, const std::shared_ptr<T>& mod)
        {
            if constexpr (Managed<T>) {
                pManager->set(mod.get());
            }
            if constexpr (SetManagerable<T>) {
                mod->setManager(pManager);
            }
        }
    private:
        Packages<
            Actor::Actors,
            Actor::Player::PlayerManager,
            Camera,
            CollisionManager,
            Crons,
            CycleMaster,
            Decors,
#if ABYSS_DEVELOP
            Project,
#endif
#if ABYSS_DEBUG
            WorldComment,
#endif
            Distortion,
            DrawManager,
            Effects,
            Environment,
            Events,
            GlobalTime,
            Light,
            Adventures,
            Pause::PauseManager,
            PhysicsManager,
            RoomManager,
            SpecialEffects,
            PostEffects,
            Sound,
            Stage,
            Temporary,
            UIs
        > m_modules;
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
