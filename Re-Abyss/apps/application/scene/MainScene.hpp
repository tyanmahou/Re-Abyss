#pragma once
#include "SceneBase.hpp"

namespace abyss
{
	class MainScene : public AppScene::Scene
	{
		class Controller;
		std::unique_ptr<Controller> m_pImpl;
	public:
		MainScene();
		void init()override;
		void update()override;
		void draw() const override;
	};
}