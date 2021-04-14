#include "Decor.hpp"
#include "DecorGraphics.hpp"

namespace abyss
{
    Decor::Decor()
    {}
    void Decor::flush()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.flush();
        }
    }
    void Decor::update()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.update();
        }
    }
    void Decor::draw(s3d::int32 order) const
    {
        if (m_decors.find(order) == m_decors.end()) {
            return;
        }
        m_decors.at(order).draw();
    }
    void Decor::drawBack() const
    {
        this->draw(DecorOrder::Back);
    }
    void Decor::drawMiddle() const
    {
        this->draw(DecorOrder::Middle);
    }
    void Decor::drawFront() const
    {
        this->draw(DecorOrder::Front);
    }

    void Decor::onCheckOut()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.clear();
        }
    }

    Ref<decor::DecorObj> Decor::create(s3d::int32 order)
    {
        return  this->regist(order, std::make_shared<decor::DecorObj>());
    }

    Ref<decor::DecorObj> Decor::regist(s3d::int32 order, const std::shared_ptr<decor::DecorObj>& decor)
    {
        decor->setManager(m_pManager);
        m_decors[order].push(decor);
        return decor;
    }
    s3d::TextureRegion Decor::getTexture(s3d::uint32 gId, double time) const
    {
        return m_graphics->getTexture(gId, time);
    }

    size_t Decor::size() const
    {
        size_t ret = 0;
        for (auto&& [layer, decor] : m_decors) {
            ret += decor.size();
        }
        return ret;
    }
}
