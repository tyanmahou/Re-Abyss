#include "SenserCtrlModel.hpp"
#include <abyss/controllers/Actors/Enemy/Slime/Senser/Senser.hpp>

namespace abyss::Slime
{
    void SenserCtrlModel::set(std::shared_ptr<Senser> senser)
    {
        m_senser = senser;
    }

    void SenserCtrlModel::destroy()
    {
        if (m_senser) {
            m_senser->destroy();
        }
    }

}
