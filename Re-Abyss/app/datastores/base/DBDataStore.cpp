#include "DBDataStore.hpp"

namespace abyss
{
    DBDataStore::DBDataStore():
        m_db(Resource::SaveUtil::DB())
    {}

    DBDataStore::DBDataStore(const s3d::String& path) :
        m_db(path)
    {}

}
