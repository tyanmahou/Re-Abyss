#pragma once

namespace abyss::InterpUtil
{
    /// <summary>
    /// デルタタイムを考慮して、補間率
    /// </summary>
    double DampRatio(double ratio, double dt, double baseFps = 60.0);
}