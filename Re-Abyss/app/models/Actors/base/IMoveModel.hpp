#pragma once
namespace abyss
{
    class IMoveModel
    {
    public:
        virtual ~IMoveModel() = default;
        virtual void onMove(double dt) = 0;
    };
}