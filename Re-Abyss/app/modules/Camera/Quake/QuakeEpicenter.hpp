#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Shake/SimpleShake.hpp>

namespace abyss
{
    class QuakeEpicenter
    {
    public:
        /// <summary>
        /// 地震パラメータ
        /// </summary>
        /// <param name="maxOffset"></param>
        /// <param name="lengthSec">長さ(ゼロ以下の場合は無限)</param>
        QuakeEpicenter(double maxOffset = 5.0, double timeSec = -1.0);

        void update(double dt);
        void stop();
        bool isEnd() const;

        const s3d::Vec2& getOffset()const;

    private:
        Shake::SimpleShake m_shake;
    };
}
