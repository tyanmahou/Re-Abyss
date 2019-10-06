#pragma once
# include<Siv3D.hpp>

namespace abyss
{
	//共有データ
	struct GameData
	{
		String m_fromScene;
		String m_toScene;
	};

	using AppScene = SceneManager<String, GameData>;

	class ISceneBase : public AppScene::Scene
	{
	protected:
		virtual void finally() {};
		void changeScene(const String& state, int transitionTimeMillisec = 1000, bool crossFade = false)
		{
			this->getData().m_fromScene = std::move(this->getData().m_toScene);
			this->getData().m_toScene = state;
			this->finally();
			this->AppScene::Scene::changeScene(state, transitionTimeMillisec, crossFade);
		}
	public:
		using AppScene::Scene::Scene;
	};

	namespace SceneName
	{
#define ABYSS_SCENE_NAME(name) constexpr auto name = U#name

		ABYSS_SCENE_NAME(Main);

#undef ABYSS_SCENE_NAME
	}
}