#pragma once
#include <abyss/utils/DB/DBBindDef.hpp>

namespace abyss::DBUtil
{
    template<DBBindable Type>
    s3d::Optional<Type> FetchOne(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueArray& param = {})
    {
        s3d::Optional<Type> ret;
        db.fetchOne(sql, param).then([&](s3dsql::DBRow& row) {
            ret = FromRow<Type>(row);
        });
        return ret;
    }

    template<DBBindable Type>
    s3d::Optional<Type> FetchOne(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueMap& param)
    {
        s3d::Optional<Type> ret;
        db.fetchOne(sql, param).then([&](s3dsql::DBRow& row) {
            ret = FromRow<Type>(row);
        });
        return ret;
    }

    template<DBBindable Type>
    s3d::Array<Type> Fetch(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueArray& param = {})
    {
        s3d::Array<Type> ret;
        for (auto&& row : db.fetch(sql, param)) {
            ret << FromRow<Type>(row);
        }
        return ret;
    }

    template<DBBindable Type>
    s3d::Array<Type> Fetch(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueMap& param)
    {
        s3d::Array<Type> ret;
        for (auto&& row : db.fetch(sql, param)) {
            ret << FromRow<Type>(row);
        }
        return ret;
    }
}