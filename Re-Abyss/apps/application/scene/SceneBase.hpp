#pragma once
# include<Siv3D.hpp>
# include<HamFramework.hpp>

namespace abyss
{
	//共有データ
	struct GameData
	{
		String m_fromScene;
		String m_toScene = L"load";
	};

	using AppScene = SceneManager<String, GameData>;

	class ISceneBase : public AppScene::Scene
	{
	protected:
		virtual void finally() {};
		void changeScene(const String& state, int transitionTimeMillisec = 1000, bool crossFade = false)
		{
			m_data->m_fromScene = std::move(m_data->m_toScene);
			m_data->m_toScene = state;
			this->finally();
			this->AppScene::Scene::changeScene(state, transitionTimeMillisec, crossFade);
		}
	};

	namespace SceneName
	{
#define ABYSS_SCENE_NAME(name) constexpr auto name = L#name

		ABYSS_SCENE_NAME(Main);

#undef ABYSS_SCENE_NAME
	}
}