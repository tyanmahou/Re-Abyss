#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Process.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

namespace abyss::Adv
{
    AdvObj::AdvObj()
    {
        m_process = this->attach<Process>(this);
        m_sentence = this->attach<SentenceCtrl>(this);
    }
    bool AdvObj::update()
    {
        m_sentence->update();
        return m_process->update();
    }
}
