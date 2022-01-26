#pragma once
#include <unordered_map>

#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>

#include <abyss/models/Actor/Gimmick/StartPos/StartPosModel.hpp>

namespace abyss
{
    class StartPosListModel
    {
        std::unordered_map<s3d::int32, StartPosModel> m_startPoss;
    public:
        void add(const StartPosModel& startPos);

        s3d::Optional<StartPosModel> find(s3d::int32 startId) const;
    };
}