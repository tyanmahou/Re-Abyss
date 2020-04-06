#include "ParamsFactory.hpp"

#include <abyss/datastores/Params/TomlParamsDataStore.hpp>
#include <abyss/repositories/Params/ParamsRepository.hpp>
#include <abyss/commons/Params.hpp>

#include <abyss/entities/Params/Actors/LaunSharkParam.hpp>

namespace abyss
{
    template <class Entity>
    std::unique_ptr<IParamsRepository<Entity>> MakeTomlRepository(const s3d::FilePath& toml)
    {
        auto dataStore = std::make_unique<TomlParamsDataStore<Entity>>(toml);
        return std::make_unique <ParamsRepository<Entity>>(std::move(dataStore));
    }
    template <class Entity>
    void BindTomlRepository(const s3d::FilePath& toml)
    {
        Params::Bind<Entity>(MakeTomlRepository<Entity>(toml));
    }
    void ParamsFactory::Bind()
    {
        BindTomlRepository<LaunSharkParam>(U"resources/params/Actors/LaunShark/param.toml");
    }
}
