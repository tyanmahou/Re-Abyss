#pragma once
#include <memory>
#include <abyss/utils/Singleton.hpp>
#include <abyss/commons/Path.hpp>

namespace s3dsql
{
    class SQLite3;
}

namespace abyss::Resource::UserData
{
    class Manager final: protected Singleton<Manager>
    {
        friend class Singleton<Manager>;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        Manager();
    public:
        static s3dsql::SQLite3 LoadDB(const s3d::FilePath& path, const s3d::FilePath& prefix = Path::UserDaraPath);
    };
}