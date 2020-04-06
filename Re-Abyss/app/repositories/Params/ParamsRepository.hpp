#pragma once
#include <memory>
#include <Siv3D/Optional.hpp>
#include <abyss/repositories/Params/base/IParamsRepository.hpp>

namespace abyss
{
    template<class Entity>
    class ParamsRepository : public IParamsRepository<Entity>
    {
        using DataStorePtr = std::unique_ptr<IParamsDataStore<Entity>>;

        DataStorePtr m_dataStore;
        s3d::Optional<Entity> m_cache;
    public:
        ParamsRepository(DataStorePtr&& dataStore):
            m_dataStore(std::move(dataStore))
        {}
        const Entity& select() override
        {
            if (m_cache) {
                return *m_cache;
            }
            m_cache = m_dataStore->select();
            return *m_cache;
        }        
    };
}