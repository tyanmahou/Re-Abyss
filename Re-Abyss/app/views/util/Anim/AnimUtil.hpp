#pragma once
#include <Siv3D/Types.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class AnimUtil
    {
    public:
        /// <summary>
        /// レートからフレームに変換
        /// </summary>
        /// <param name="rate">0～1</param>
        /// <param name="frameSize"></param>
        /// <returns></returns>
        static s3d::int32 FrameFromRate(double rate, s3d::int32 frameSize);

        static s3d::int32 FrameFromMap(double rate, const s3d::Array<s3d::int32>& map);

        template<size_t N>
        static s3d::int32 FrameFromMap(double rate, const s3d::int32(&map)[N])
        {
            return map[FrameFromRate(rate, static_cast<s3d::int32>(N))];
        }

        /// <summary>
        /// ノコギリ波からフレームに変換
        /// </summary>
        /// <param name="period"></param>
        /// <param name="time"></param>
        /// <param name="frameSize"></param>
        /// <returns></returns>
        static s3d::int32 FrameFromSaw(double period, double time, s3d::int32 frameSize);

        /// <summary>
        /// 三角波からフレームに変換
        /// </summary>
        /// <param name="period"></param>
        /// <param name="time"></param>
        /// <param name="frameSize"></param>
        /// <returns></returns>
        static s3d::int32 FrameFromTriangle(double period, double time , s3d::int32 frameSize);
    };
}
