#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::Cycle::SaveSelect::SelectFrame
{
    /// <summary>
    /// 選択枠
    /// </summary>
    class SelectFrameVM
    {
        s3d::Texture m_trashIcon;

        s3d::int32 m_selectUserId = 0;
    public:
        SelectFrameVM();
        SelectFrameVM& setSelectUserId(s3d::int32 userId)
        {
            m_selectUserId = userId;
            return *this;
        }
        void draw() const;
    };
}