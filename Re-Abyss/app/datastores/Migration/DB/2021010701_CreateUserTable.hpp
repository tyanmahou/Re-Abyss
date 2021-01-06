#pragma once
#include <abyss/datastores/Migration/DB/DBMigration.hpp>

namespace abyss::User::Migrations
{
    template<>
    class DBMigration<2021010701> : public IDBMigraion
    {
    public:
        using IDBMigraion::IDBMigraion;
        void up() const override
        {

        }
        void down() const override
        {

        }
    };
}