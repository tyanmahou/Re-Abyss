#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
#include <abyss/modules/Adv/base/Process.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

namespace abyss::Adv
{
    AdvObj::AdvObj()
    {
        m_engine = this->attach<Engine>(this);
        m_process = this->attach<Process>(this);
        m_sentence = this->attach<SentenceCtrl>(this);
    }
    bool AdvObj::update()
    {
        m_sentence->update();
        m_process->update();
        return m_engine->update();
    }
}
