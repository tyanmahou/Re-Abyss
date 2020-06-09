#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/StopwatchEx/StopwatchEx.hpp>

namespace abyss
{
    class QuakeModel
    {
    private:
        double m_maxOffset = 0;
        double m_timeSec = 1.0;
        StopwatchEx m_stopwatch;

        Manager* m_pManager;
    public:
        /// <summary>
        /// 地震パラメータ
        /// </summary>
        /// <param name="pManager"></param>
        /// <param name="maxOffset"></param>
        /// <param name="lengthSec">長さ(ゼロ以下の場合は無限)</param>
        QuakeModel(Manager* pManager, double maxOffset = 5.0, double timeSec = -1.0);

        bool IsEnd() const;
        s3d::Vec2 apply(const s3d::Vec2& pos) const;
    };
}