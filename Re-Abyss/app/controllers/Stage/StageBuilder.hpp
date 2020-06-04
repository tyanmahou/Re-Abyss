#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class StageLoader
    {
        std::shared_ptr<IBackGroundService> m_backGroundService;

    public:
        void initBackGround(BackGround& backGround);
    };
}