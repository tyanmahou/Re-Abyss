#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class IDecorService
    {
    public:
        virtual ~IDecorService() = default;

        virtual const s3d::Array<std::shared_ptr<IDecorModel>>& getFront() const = 0;
        virtual const s3d::Array<std::shared_ptr<IDecorModel>>& getBack() const = 0;
        virtual const s3d::Array<std::shared_ptr<IDecorModel>>& getCustom() const = 0;
    };
}