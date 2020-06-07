#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/entities/BackGround/BackGroundEntity.hpp>

namespace abyss
{
    class IBackGroundService
    {
    public:
        virtual ~IBackGroundService() = default;

        virtual  const s3d::Array<BackGroundEntity>& getBgs()const = 0;

        virtual const s3d::Color& getBgColor()const = 0;
    };
}