#include <abyss/modules/Novel/Novels.hpp>

namespace abyss::Novel
{
    bool Novels::update()
    {
        for (auto it = m_stash.begin(); it != m_stash.end();) {
            if (!(*it)->isStahed()) {
                m_talks.push((*it));
                it = m_stash.erase(it);
            } else {
                ++it;
            }
        }
        do {
            if (m_talks.empty()) {
                return false;
            }
            auto& front = m_talks.front();
            if (!m_doneCurrentInit) {
                if (!front->isSetuped()) {
                    front->setup();
                    front->start();
                }
                m_doneCurrentInit = true;
            }
            if (!front->update()) {
                front->end();
                m_talks.pop();
                m_doneCurrentInit = false;
            } else if (front->isStahed()) {
                m_stash << front;
                m_talks.pop();
                m_doneCurrentInit = false;
            }
        } while (!m_doneCurrentInit);

        return true;
    }
    bool Novels::isEmpty() const
    {
        return m_talks.empty();
    }
    Ref<TalkObj> Novels::create()
    {
        return this->regist(std::make_shared<TalkObj>());
    }

    Ref<TalkObj> Novels::regist(const std::shared_ptr<TalkObj>& talk)
    {
        talk->setManager(m_pManager);
        m_talks.push(talk);
        return talk;
    }
    s3d::Optional<Chara> Novels::findChara(CharaKind kind) const
    {
        if (!m_charaTable) {
            return s3d::none;
        }
        return m_charaTable->find(kind);
    }
}
