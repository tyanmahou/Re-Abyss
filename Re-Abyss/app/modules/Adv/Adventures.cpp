#include <abyss/modules/Adv/Adventures.hpp>

namespace abyss::Adv
{
    bool Adventures::update()
    {
        do {
            if (m_talks.empty()) {
                return false;
            }
            auto& front = m_talks.front();
            if (!m_doneCurrentInit) {
                front->setup();
                front->start();
                m_doneCurrentInit = true;
            }
            if (!front->update()) {
                front->end();
                m_talks.pop();
                m_doneCurrentInit = false;
            }
        } while (!m_doneCurrentInit);

        return true;
    }
    bool Adventures::isEmpty() const
    {
        return m_talks.empty();
    }
    Ref<AdvObj> Adventures::create()
    {
        return this->regist(std::make_shared<AdvObj>());
    }

    Ref<AdvObj> Adventures::regist(const std::shared_ptr<AdvObj>& talk)
    {
        talk->setManager(m_pManager);
        m_talks.push(talk);
        return talk;
    }
    s3d::Optional<Chara> Adventures::findChara(CharaKind kind) const
    {
        if (!m_project) {
            return s3d::none;
        }
        return m_project->findChara(kind);
    }
}
