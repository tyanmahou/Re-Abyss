#include <abyss/utils/Migration/Migration.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;

    MIGRATION(CreateUserTable)
    {
        void up() const override
        {
            auto&& db = Resource::SaveUtil::DB();
            StringView sql = U""
                "CREATE TABLE IF NOT EXISTS users("
                "  `user_id` INTEGER PRIMARY KEY NOT NULL,"
                "  `play_mode` TEXT NOT NULL,"
                "  `play_time` REAL DEFAULT(0) NOT NULL,"
                "  `updated_at` TEXT DEFAULT(DATETIME('now', 'localtime')) NOT NULL,"
                "  `created_at` TEXT DEFAULT(DATETIME('now', 'localtime')) NOT NULL"
                "); ";
            db.exec(sql);
        }
        void down() const override
        {
            auto&& db = Resource::SaveUtil::DB();
            StringView sql = U""
                "DROP TABLE IF EXISTS users;"
            ;

            db.exec(sql);
        }
    }_;
}
