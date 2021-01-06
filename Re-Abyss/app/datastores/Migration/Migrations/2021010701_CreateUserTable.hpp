#pragma once
#include <abyss/datastores/Migration/base/IMigration.hpp>

namespace abyss::User::Migrations
{
    template<>
    class Migration<2021010701> : public IMigration
    {
    public:
        void up() const override
        {

        }
        void down() const override
        {

        }
    };
}