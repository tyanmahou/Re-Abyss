#pragma once
#include <abyss/models/Adv/Chara.hpp>

namespace abyss::Adv
{
    class IProjectService
    {
    public:
        virtual ~IProjectService() = default;

        virtual const s3d::Array<Chara>& getCharas() const = 0;
    };
}
