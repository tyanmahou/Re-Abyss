#include "MainApp.hpp"

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/String.hpp>

#include <abyss/commons/Constants.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Preload/Manager.hpp>
#include <abyss/commons/Resource/UserData/Manager/Manager.hpp>
#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

namespace abyss
{
	bool MainApp::update()
	{
		return m_game.update();
	}

    MainApp::MainApp() :
		IApplication(Constants::AppName, Constants::AppResolution)
	{
	
	
	}

    MainApp::~MainApp()
	{
		// シングルトンリリース
		InputManager::Release();
		Resource::Assets::Main()->free();
		Resource::Assets::Norelease()->free();
		Resource::Preload::Manager::Release();
		Resource::UserData::Storage::Release(); // DBにアクセスするので先にリリース
		Resource::UserData::Migration::Release();
		Resource::UserData::Manager::Release();
#if ABYSS_DEBUG
		Debug::DebugManager::Release();
		Debug::Menu::Release();
		Debug::Log::Release();
#endif
	}
}