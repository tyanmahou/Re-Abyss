#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss::User::Migrations
{
    class IMigration
    {
    public:
        virtual ~IMigration() = default;
        virtual void up() const = 0;
        virtual void down() const = 0;
    };

    template<s3d::int32 ID>
    class Migration;

}
