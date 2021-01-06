#pragma once

namespace abyss::User
{
    class IMigrationService
    {
    public:
        virtual ~IMigrationService() = default;

        virtual void up() const = 0;
        virtual void down() const = 0;
    };
}