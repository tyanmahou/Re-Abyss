#include "Manager.hpp"

#include <Siv3DSQL.hpp>
#include <Siv3D.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace abyss::Resource::UserData
{
    class Manager::Impl
    {
        s3d::HashTable<String, s3dsql::SQLite3> m_dbCache;
    public:
        Impl()
        {}

        template<class Type, class ReadType = Type, class ... Args>
        const Type& load(s3d::HashTable<String, Type>& cache, const s3d::FilePath& path, Args&&... args)
        {
            if (cache.find(path) != cache.end()) {
                return cache[path];
            }
            ReadType rc(path, std::forward<Args>(args)...);
#if ABYSS_DEBUG
            if (!rc) {
                Debug::LogWarn << U"Failed Load:" << path;
            }
#endif
            return cache[path] = rc;
        }

        s3dsql::SQLite3 loadDB(const s3d::FilePath& path)
        {
            return this->load(m_dbCache, path);
        }
    };

    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}
    s3dsql::SQLite3 Manager::LoadDB(const s3d::FilePath& path, const s3d::FilePath& prefix)
    {
        return Instance()->m_pImpl->loadDB(prefix + path);
    }
}
