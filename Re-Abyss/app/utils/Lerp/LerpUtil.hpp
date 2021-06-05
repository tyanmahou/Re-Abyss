#pragma once

namespace abyss::LerpUtil
{
    /// <summary>
    /// デルタタイムを考慮して、補間率
    /// </summary>
    double Ratio(double ratio, double dt);
}