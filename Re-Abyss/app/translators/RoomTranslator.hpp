#pragma once
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class RoomTranslator
    {
    public:
        static RoomModel ToModel(const RoomEntity& entity);
    };
}