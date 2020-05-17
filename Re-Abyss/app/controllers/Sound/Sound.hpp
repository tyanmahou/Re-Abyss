#pragma once
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Sound
    {
        Manager* m_pManager;
    public:
        void setManager(Manager* pManager)
        {
            m_pManager = pManager;
        }
    };
}