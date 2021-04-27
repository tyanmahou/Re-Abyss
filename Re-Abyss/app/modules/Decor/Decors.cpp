#include "Decors.hpp"
#include "DecorGraphics.hpp"

namespace abyss
{
    Decors::Decors()
    {}
    void Decors::flush()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.flush();
        }
    }
    void Decors::update()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.update();
        }
    }
    void Decors::draw(s3d::int32 order) const
    {
        if (m_decors.find(order) == m_decors.end()) {
            return;
        }
        m_decors.at(order).draw();
    }
    void Decors::drawBack() const
    {
        this->draw(DecorOrder::Back);
    }
    void Decors::drawMiddle() const
    {
        this->draw(DecorOrder::Middle);
    }
    void Decors::drawFront() const
    {
        this->draw(DecorOrder::Front);
    }

    void Decors::onCheckOut()
    {
        m_bufferLayer = Decor::FlipBuffer(m_bufferLayer);
    }

    void Decors::onCheckIn()
    {
        for (auto&& [layer, decor] : m_decors) {
            decor.clear(Decor::FlipBuffer(m_bufferLayer));
        }
    }

    Ref<Decor::DecorObj> Decors::create(s3d::int32 order)
    {
        return  this->regist(order, std::make_shared<Decor::DecorObj>());
    }

    Ref<Decor::DecorObj> Decors::regist(s3d::int32 order, const std::shared_ptr<Decor::DecorObj>& decor)
    {
        decor->setManager(m_pManager);
        decor->setBufferLayer(m_bufferLayer);
        m_decors[order].push(decor);
        return decor;
    }

    s3d::uint32 Decors::getAnimGId(s3d::uint32 gId, double time) const
    {
        return m_graphics->getAnimGId(gId, time);
    }
    s3d::TextureRegion Decors::getTexture(s3d::uint32 gId, double time) const
    {
        return m_graphics->getTexture(gId, time);
    }

    size_t Decors::size() const
    {
        size_t ret = 0;
        for (auto&& [layer, decor] : m_decors) {
            ret += decor.size();
        }
        return ret;
    }

    Decor::DecorIdTable Decors::getIdTable() const
    {
        Decor::DecorIdTable ret;
        for (auto&& [layer, decor] : m_decors) {
            auto table = decor.getIdTable();
            for (auto&& [category, objs] : table) {
                ret[category].insert(objs.begin(), objs.end());
            }
        }
        return ret;
    }
}
