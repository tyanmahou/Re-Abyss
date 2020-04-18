#include "MainScene.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/factories/ActionSystem/ActionSystemFactory.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include <abyss/params/Actors/CaptainTako/CaptainTakoParam.hpp>
#include <abyss/params/Actors/CaptainTako/CaptainTakoShotParam.hpp>
#include <abyss/params/Actors/Ikalien/IkalienParam.hpp>
#include <abyss/params/Actors/LaunShark/LaunSharkParam.hpp>
#include <abyss/params/Actors/LaunShark/LaunSharkShotParam.hpp>
#include <abyss/params/Actors/Player/PlayerParam.hpp>
#include <abyss/params/Actors/Player/PlayerShotParam.hpp>
#include <abyss/params/Actors/RollingTako/RollingTakoParam.hpp>
#include <abyss/params/Actors/Slime/SlimeParam.hpp>
#include <abyss/params/Actors/Schield/SchieldParam.hpp>
#include <abyss/params/Actors/Schield/SchieldShotParam.hpp>

namespace
{
	using namespace abyss;
	void PreloadResourece(const ResourceManager& resource)
	{
		resource.loadToml<CaptainTakoParam>(U"Actors/CaptainTako/param.toml");
		resource.loadToml<CaptainTakoShotParam>(U"Actors/CaptainTako/shot_param.toml");

		resource.loadToml<IkalienParam>(U"Actors/Ikalien/param.toml");

		resource.loadToml<PlayerParam>(U"Actors/Player/param.toml");
		resource.loadToml<PlayerShotParam>(U"Actors/Player/shot_param.toml");

		resource.loadToml<LaunSharkParam>(U"Actors/LaunShark/param.toml");
		resource.loadToml<LaunSharkShotParam>(U"Actors/LaunShark/shot_param.toml");

		resource.loadToml<RollingTakoParam>(U"Actors/RollingTako/param.toml");

		resource.loadToml<SlimeParam>(U"Actors/Slime/param.toml");

		resource.loadToml<SchieldParam>(U"Actors/Schield/param.toml");
		resource.loadToml<SchieldShotParam>(U"Actors/Schield/shot_param.toml");
	}
}
namespace abyss
{
	class MainScene::Controller
	{
		std::shared_ptr<ActionSystem> m_actionSystem;
		ResourceManager m_resources;
	public:
		Controller([[maybe_unused]] const MainScene::InitData& init)
		{
			m_actionSystem = ActionSystemFactory::CreateFromTmx(U"stage0");
			this->init();
		}

		void init()
		{
			::PreloadResourece(m_resources);
			m_actionSystem->init();
		}

		void update()
		{
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