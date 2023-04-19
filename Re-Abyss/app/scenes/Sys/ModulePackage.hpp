#pragma once
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
#include <abyss/modules/User/Storage.hpp>
#include <abyss/modules/Fade/Fader.hpp>

namespace abyss::Sys
{
    template<class... T>
    using ModuleSet = std::tuple<std::shared_ptr<T>...>;

    using ModulePackage = ModuleSet <
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
        UIs,
        Storage,
        Fader
    > ;
}
