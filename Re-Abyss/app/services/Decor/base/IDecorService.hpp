#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor
{
    class IDecorService
    {
    public:
        virtual ~IDecorService() = default;

        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getFront() const = 0;
        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getBack() const = 0;
        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getCustom() const = 0;
    };
}
