#include "ParamPreloader.hpp"

// Splash
#include <abyss/params/Cycle/Splash/Param.hpp>

// Title
#include <abyss/params/Cycle/Title/LogoParam.hpp>
#include <abyss/params/Cycle/Title/BgParam.hpp>

// Actors
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/ShotParam.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>

#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

// UI
#include <abyss/params/UI/PlayerInfo/Param.hpp>

namespace abyss::Resource::Prelaod
{
	void LoadTomlAll(const Assets& resource)
	{
		LoadSplashToml(resource);
		LoadTitleToml(resource);
		LoadActorToml(resource);
		LoadUIToml(resource);
	}
	void LoadSplashToml(const Assets& resource)
	{
		resource.loadToml<Cycle::Splash::Param>(U"Cycle/Splash/param.toml");
	}

	void LoadTitleToml(const Assets& resource)
	{
		resource.loadToml<Cycle::Title::LogoParam>(U"Cycle/Title/logo_param.toml");
		resource.loadToml<Cycle::Title::BgParam>(U"Cycle/Title/bg_param.toml");
	}
	void LoadActorToml(const Assets& resource)
    {
		using namespace Actor;
		using namespace Actor::Enemy;

		// Player
		resource.loadToml<Player::Param>(U"Actors/Player/param.toml");
		resource.loadToml<Player::ShotParam>(U"Actors/Player/shot_param.toml");

		// Enemy
		resource.loadToml<CaptainTako::Param>(U"Actors/CaptainTako/param.toml");
		resource.loadToml<CaptainTako::ShotParam>(U"Actors/CaptainTako/shot_param.toml");

		resource.loadToml<Ikalien::Param>(U"Actors/Ikalien/param.toml");

		resource.loadToml<LaunShark::Param>(U"Actors/LaunShark/param.toml");
		resource.loadToml<LaunShark::ShotParam>(U"Actors/LaunShark/shot_param.toml");

		resource.loadToml<RollingTako::Param>(U"Actors/RollingTako/param.toml");

		resource.loadToml<Slime::Param>(U"Actors/Slime/param.toml");

		resource.loadToml<Schield::Param>(U"Actors/Schield/param.toml");
		resource.loadToml<Schield::ShotParam>(U"Actors/Schield/shot_param.toml");

		// Boss
		resource.loadToml<CodeZero::Param>(U"Actors/CodeZero/param.toml");
		resource.loadToml<CodeZero::HandParam>(U"Actors/CodeZero/hand_param.toml");
		resource.loadToml<CodeZero::ShotParam>(U"Actors/CodeZero/shot_param.toml");
    }

	void LoadUIToml(const Assets& resource)
	{
		using namespace ui;
		resource.loadToml<PlayerInfo::Param>(U"UI/PlayerInfo/param.toml");
	}
}
