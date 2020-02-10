# pragma once
# include<Siv3D.hpp>

namespace abyss
{
	/// <summary>
	/// game shared data
	/// </summary>
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
#define FORSS_SCENE_NAME(name) inline constexpr auto name = U#name

		FORSS_SCENE_NAME(Main);

#undef FORSS_SCENE_NAME
	}
}