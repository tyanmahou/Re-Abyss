#pragma once
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Sound
    {
        ActManager* m_pManager;
    public:
        void setManager(ActManager* pManager)
        {
            m_pManager = pManager;
        }
        void playSe(const s3d::FilePath& path, const s3d::Vec2& pos) const;
    };
}