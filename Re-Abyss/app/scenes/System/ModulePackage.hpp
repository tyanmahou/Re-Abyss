#pragma once

#include <abyss/scenes/System/Config.hpp>
#include <abyss/scenes/System/Modules.hpp>

// Modules
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/BackGround/BackGround.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/ColSys/CollisionManager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/Devs/WorldComment/WorldComment.hpp>
#include <abyss/modules/Distortion/Distortion.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Env/Environment.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Novel/Novels.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/World/World.hpp>


namespace abyss::Sys
{
    template<bool condition, class Mod>
    using mod_if = std::conditional_t<condition, Mod, void>;

    template<Config config>
    using ModulePackage = ModuleSet<
        mod_if<config.isStage, Actor::Player::PlayerManager>,
        mod_if<config.isStage, BackGround>,
        Camera,
        mod_if<config.isStage, CollisionManager>,
        Crons,
        CycleMaster,
        mod_if<config.isStage, Decors>,
#if ABYSS_DEBUG
        WorldComment,
#endif
        mod_if<config.isStage, Distortion>,
        DrawManager,
        Effects,
        Environment,
        Events,
        GlobalTime,
        mod_if<config.isStage, Light>,
        mod_if<config.isStage, Novels>,
        mod_if<config.isStage, PhysicsManager>,
        mod_if<config.isStage, RoomManager>,
        SpecialEffects,
        PostEffects,
        Sound,
        mod_if<config.isStage, Stage>,
        mod_if<config.isStage, Temporary>,
        UIs,
        mod_if<config.isStage, World>
    >;
}
