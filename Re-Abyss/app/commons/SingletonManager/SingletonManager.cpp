#include <abyss/commons/SingletonManager/SingletonManager.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss
{
    SingletonManager::SingletonManager()
    {}

    SingletonManager::~SingletonManager()
    {
		// シングルトンリリース
		DynamicSingletonFinalizer::Finalize();

        // リソースリリース
        Resource::Assets::Main()->free();
        Resource::Assets::Norelease()->free();
    }
}
