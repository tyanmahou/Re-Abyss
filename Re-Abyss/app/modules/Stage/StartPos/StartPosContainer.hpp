#pragma once
#include <abyss/modules/Stage/StartPos/StartPos.hpp>
#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>
#include<Siv3D/HashTable.hpp>

namespace abyss
{
    class StartPosContainer
    {
    public:
        void add(const StartPos& startPos);

        s3d::Optional<StartPos> find(s3d::int32 startId) const;
    private:

        s3d::HashTable<s3d::int32, StartPos> m_container;
    };
}
