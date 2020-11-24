#pragma once
#include <abyss/commons/Resource/SaveUtil.hpp>

namespace abyss
{
    class DBDataStore
    {
    protected:
        s3dsql::SQLite3 m_db;
    public:
        DBDataStore();
        DBDataStore(const s3d::String& path);

        virtual ~DBDataStore() = default;
    };
}