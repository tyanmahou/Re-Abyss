#include "DBUserDataStore.hpp"
#include <abyss/utils/DB/DBUtil.hpp>

namespace abyss::User
{
    s3d::Array<UserEntity> DBUserDataStore::selectAll() const
    {
        s3d::String sql = U""
            "SELECT * FROM"
            "    users"
            ";"
            ;
        return DBUtil::Fetch<UserEntity>(m_db, sql);
    }

    s3d::Optional<UserEntity> DBUserDataStore::select(s3d::int32 userId) const
    {
        s3d::String sql = U""
            "SELECT * FROM"
            "    users"
            "WHERE"
            "    user_id = ?"
            ";"
            ;
        return DBUtil::FetchOne<UserEntity>(m_db, sql, s3dsql::DBValueArray{ userId });
    }

    bool DBUserDataStore::update(const UserEntity& entity) const
    {
        s3d::String sql = U""
            "INSERT INTO"
            "    users(user_id, play_mode, play_time)"
            "VALUES"
            "    (?, ?, ?)"
            "ON CONFLICT(user_id) DO UPDATE "
            "SET"
            "    play_mode = excluded.play_mode,"
            "    play_time = excluded.play_time,"
            "    updated_at = DATETIME('now', 'localtime')"
            ";"
        ;
        return m_db.exec(sql, s3dsql::DBValueArray{ 
            entity.userId, 
            Enum::ToStr(entity.playMode),
            entity.playTime.count()
        }) != 0;
    }

    bool DBUserDataStore::erase(s3d::int32 userId) const
    {
        s3d::String sql = U""
            "DELETE FROM"
            "    users"
            "WHERE"
            "    user_id = ?"
            ";"
            ;
        return m_db.exec(sql, s3dsql::DBValueArray{userId}) != 0;
    }

}
