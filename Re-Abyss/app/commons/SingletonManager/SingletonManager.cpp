#include "SingletonManager.hpp"

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
    SingletonManager::SingletonManager()
    {}

    SingletonManager::~SingletonManager()
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
		Debug::Log::Release();
#endif    
		DynamicSingletonFinalizer::Finalize();
    }
}
