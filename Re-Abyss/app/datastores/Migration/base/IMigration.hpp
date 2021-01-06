#pragma once

namespace abyss::User
{
    class IMigration
    {
    public:
        virtual ~IMigration() = default;
        virtual void up() const = 0;
        virtual void down() const = 0;
    };
}
