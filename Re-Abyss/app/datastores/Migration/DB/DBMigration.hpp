#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/datastores/Migration/base/IMigration.hpp>
#include <Siv3DSQL/SQLite3.hpp>

namespace abyss::User::Migrations
{
    class IDBMigraion : public IMigration
    {
    public:
        IDBMigraion(s3dsql::SQLite3 db) :
            m_db(db)
        {}
    protected:
        s3dsql::SQLite3 m_db;
    };

    template<s3d::int32 ID>
    class DBMigration;
}