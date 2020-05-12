#include "MainScene.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/factories/ActionSystem/ActionSystemFactory.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/ShotParam.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/params/Actors/Enemy/Slime/Param.hpp>
#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/params/Actors/Enemy/Schield/ShotParam.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

#include <abyss/debugs/HotReload/HotReload.hpp>

namespace
{
	using namespace abyss;
	void PreloadResourece(const ResourceManager& resource)
	{
		resource.loadToml<CaptainTako::Param>(U"Actors/CaptainTako/param.toml");
		resource.loadToml<CaptainTako::ShotParam>(U"Actors/CaptainTako/shot_param.toml");

		resource.loadToml<Ikalien::Param>(U"Actors/Ikalien/param.toml");

		resource.loadToml<Player::Param>(U"Actors/Player/param.toml");
		resource.loadToml<Player::ShotParam>(U"Actors/Player/shot_param.toml");

		resource.loadToml<LaunShark::Param>(U"Actors/LaunShark/param.toml");
		resource.loadToml<LaunShark::ShotParam>(U"Actors/LaunShark/shot_param.toml");

		resource.loadToml<RollingTako::Param>(U"Actors/RollingTako/param.toml");

		resource.loadToml<Slime::Param>(U"Actors/Slime/param.toml");

		resource.loadToml<Schield::Param>(U"Actors/Schield/param.toml");
		resource.loadToml<Schield::ShotParam>(U"Actors/Schield/shot_param.toml");

		resource.loadToml<CodeZero::Param>(U"Actors/CodeZero/param.toml");
		resource.loadToml<CodeZero::HandParam>(U"Actors/CodeZero/hand_param.toml");
		resource.loadToml<CodeZero::ShotParam>(U"Actors/CodeZero/shot_param.toml");
	}
}
namespace abyss
{
	class MainScene::Controller
	{
		std::shared_ptr<ActionSystem> m_actionSystem;
		ResourceManager m_resources;

		String mapName;

#if ABYSS_DEBUG
		Debug::HotReload m_reloader;
#endif
	public:
		Controller([[maybe_unused]] const MainScene::InitData& init)
		{
			mapName = U"stage0";
#if ABYSS_DEBUG
			m_reloader
				.setMessage(mapName)
				.setCallback([this]() {
				this->reload();
			});
#endif
			this->init();
		}

		void reload()
		{
			this->m_resources.release();
			{
				// リロード時はリソースを直で
				m_resources.setIsBuilded(false);
				this->init(true);
			}
		}
		void init(bool isLockPlayer = false)
		{
			std::shared_ptr<Player::PlayerActor> player = nullptr;
			if (isLockPlayer) {
				player = m_actionSystem->lockPlayer();
			}
			m_actionSystem = ActionSystemFactory::CreateFromTmx(mapName);

			::PreloadResourece(m_resources);
			if (player) {
				m_actionSystem->init(player);
			} else {
				m_actionSystem->init();
			}
		}

		void update()
		{
#if ABYSS_DEBUG
			m_reloader.detection();
#endif
			m_actionSystem->update();
		}

		void draw() const
		{
			m_actionSystem->draw();
		}
	};

	MainScene::MainScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Controller>(init))
	{}

	void MainScene::update()
	{
		m_pImpl->update();
	}
	void MainScene::draw() const
	{
		m_pImpl->draw();
	}
}