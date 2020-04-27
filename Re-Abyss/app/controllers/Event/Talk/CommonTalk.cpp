#include "CommonTalk.hpp"

namespace abyss::Event::Talk
{
    void CommonTalk::setFaceManager(const std::shared_ptr<FaceManager>& face)
    {
        m_faceManager = face;
    }
    void CommonTalk::addSerif(Serif&& serif)
    {
        m_serifs.push(std::move(serif));
    }
    void CommonTalk::init()
    {}
    bool CommonTalk::update()
    {
        return false;
    }
    void CommonTalk::draw() const
    {}
}
