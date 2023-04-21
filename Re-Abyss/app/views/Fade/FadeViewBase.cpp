#include <abyss/views/Fade/FadeViewBase.hpp>

namespace abyss::Fade
{
    bool FadeViewBase::fadeTimeAdjust(double& t, double factor) const
    {
        if (t > factor) {
            return false;
        }

        t *= (1 / factor);
        return true;
    }
}
