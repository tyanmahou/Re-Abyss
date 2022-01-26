#include <abyss/commons/Resource/Preload/Param.hpp>

// Actors
#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/params/Actor/Player/CameraParam.hpp>

#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/ShotParam.hpp>
#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>
#include <abyss/params/Actor/Enemy/RollingTako/Param.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>
#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/params/Actor/Enemy/Schield/ShotParam.hpp>

#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>

#include <abyss/params/Actor/Gimmick/Bush/Param.hpp>

#include <abyss/params/Actor/Item/Recovery/Param.hpp>

// UI
#include <abyss/params/UI/PlayerInfo/Param.hpp>
#include <abyss/params/UI/BossHPBar/Param.hpp>


// Cycle関連
// Common
#include <abyss/params/UI/Common/FooterParam.hpp>
#include <abyss/params/UI/Common/LoadingParam.hpp>

// Splash
#include <abyss/params/UI/Splash/Param.hpp>

// Title
#include <abyss/params/UI/Title/LogoParam.hpp>
#include <abyss/params/UI/Title/BgParam.hpp>

// SaveSelect
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <abyss/params/UI/SaveSelect/UserInfoParam.hpp>

namespace abyss::Resource::Preload
{
	void LoadTomlAll(const Assets* resource)
	{
		// Cycle
		LoadCycleCommon(resource);
		LoadSplashToml(resource);
		LoadTitleToml(resource);
		LoadSaveSelectToml(resource);

		// Actor
		LoadActorToml(resource);
		// UI
		LoadUIToml(resource);
	}
	void LoadCycleCommon(const Assets* resource)
	{
		resource->loadToml<UI::FooterParam>(U"UI/Common/FooterParam.toml");
		resource->loadToml<UI::LoadingParam>(U"UI/Common/LoadingParam.toml");
	}
	void LoadSplashToml(const Assets* resource)
	{
		resource->loadToml<UI::Splash::Param>(U"UI/Splash/Param.toml");
	}

	void LoadTitleToml(const Assets* resource)
	{
		resource->loadToml<UI::Title::LogoParam>(U"UI/Title/LogoParam.toml");
		resource->loadToml<UI::Title::BgParam>(U"UI/Title/BgParam.toml");
	}
	void LoadSaveSelectToml(const Assets* resource)
	{
		resource->loadToml<UI::SaveSelect::Param>(U"UI/SaveSelect/Param.toml");
		resource->loadToml<UI::SaveSelect::UserInfoParam>(U"UI/SaveSelect/UserInfoParam.toml");
	}
	void LoadActorToml(const Assets* resource)
    {
		using namespace Actor;

		// Player
		{
			resource->loadToml<Player::Param>(U"Actors/Player/Param.toml");
			resource->loadToml<Player::ShotParam>(U"Actors/Player/ShotParam.toml");
			resource->loadToml<Player::CameraParam>(U"Actors/Player/CameraParam.toml");
		}

		// Enemy
		{
			using namespace Actor::Enemy;

			resource->loadToml<CaptainTako::Param>(U"Actors/Enemy/CaptainTako/Param.toml");
			resource->loadToml<CaptainTako::ShotParam>(U"Actors/Enemy/CaptainTako/ShotParam.toml");

			resource->loadToml<Ikalien::Param>(U"Actors/Enemy/Ikalien/Param.toml");

			resource->loadToml<LaunShark::Param>(U"Actors/Enemy/LaunShark/Param.toml");
			resource->loadToml<LaunShark::ShotParam>(U"Actors/Enemy/LaunShark/ShotParam.toml");

			resource->loadToml<RollingTako::Param>(U"Actors/Enemy/RollingTako/Param.toml");

			resource->loadToml<Slime::Param>(U"Actors/Enemy/Slime/Param.toml");

			resource->loadToml<Schield::Param>(U"Actors/Enemy/Schield/Param.toml");
			resource->loadToml<Schield::ShotParam>(U"Actors/Enemy/Schield/ShotParam.toml");

			// MidBoss
			resource->loadToml<KingDux::Param>(U"Actors/Enemy/KingDux/Param.toml");
			resource->loadToml<KingDux::TentacleParam>(U"Actors/Enemy/KingDux/TentacleParam.toml");
			resource->loadToml<KingDux::BabyDuxParam>(U"Actors/Enemy/KingDux/BabyDuxParam.toml");

			// Boss
			resource->loadToml<CodeZero::Param>(U"Actors/Enemy/CodeZero/Param.toml");
			resource->loadToml<CodeZero::HandParam>(U"Actors/Enemy/CodeZero/HandParam.toml");
			resource->loadToml<CodeZero::ShotParam>(U"Actors/Enemy/CodeZero/ShotParam.toml");
		}

		// Gimmick
		{
			using namespace Actor::Gimmick;
			resource->loadToml<Bush::Param>(U"Actors/Gimmick/Bush/Param.toml");
		}

		// Item
		{
			using namespace Actor::Item;
			resource->loadToml<Recovery::Param>(U"Actors/Item/Recovery/Param.toml");
		}
    }

	void LoadUIToml(const Assets* resource)
	{
		using namespace UI;
		resource->loadToml<PlayerInfo::Param>(U"UI/PlayerInfo/Param.toml");
		resource->loadToml<BossHPBar::Param>(U"UI/BossHPBar/Param.toml");
	}
}
