#include "DBUserDataStore.hpp"

namespace abyss::User
{
    UserEntity FromRow(s3dsql::DBRow& row)
    {
        return {
            .userId = row[U"user_id"].get<s3d::int32>(),
            .playMode = Enum::Parse<UserPlayMode>(row[U"play_mode"].get<s3d::String>()),
            .playTime = s3d::Duration(row[U"play_time"].get <double>()),
            .createdAt = s3d::DateTime()
        };
    }

    s3d::Array<UserEntity> DBUserDataStore::selectAll() const
    {
        s3d::Array<UserEntity> ret;
        s3d::String sql = U""
            "SELECT * FROM"
            "    users"
            ";"
            ;
        for (auto&& row : m_db.fetch(sql)) {
            ret << FromRow(row);
        }
        return ret;
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
        s3d::Optional<UserEntity> ret;
        m_db.fetchOne(sql, s3dsql::DBValueArray{ userId }).then([&](auto& row) {
            ret = FromRow(row);
        });
        return ret;
    }

    bool DBUserDataStore::update(const UserEntity& entity) const
    {
        s3d::String sql = U""
            "INSERT INTO"
            "    users(user_id, play_mode, play_time)"
            "VALUES"
            "    (?, ?, ?)"
            "ON CONFLICT(user_id) DO UPDATE"
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
