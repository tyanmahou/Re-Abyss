#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class RoomTranslator
    {
    public:
        static RoomData ToModel(const RoomEntity& entity);
    };
}