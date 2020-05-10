#pragma once
namespace abyss
{
    class ILastUpdateModel
    {
    public:
        virtual ~ILastUpdateModel() = default;
        virtual void onLastUpdate(double dt) = 0;
    };
}