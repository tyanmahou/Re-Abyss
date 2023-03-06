#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Adv
{
    class Process;
    class SentenceCtrl;

    class AdvObj : public GameObject
    {
    public:
        AdvObj();

        bool update();
        const Ref<Process>& process() const
        {
            return m_process;
        }
        const Ref<SentenceCtrl>& sentence() const
        {
            return m_sentence;
        }
    private:
        Ref<Process> m_process;
        Ref<SentenceCtrl> m_sentence;
    };
}
