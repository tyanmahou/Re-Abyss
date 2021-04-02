#include "Decor.hpp"

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
    void Decor::draw(s3d::int32 order, const s3d::RectF& screen) const
    {
        if (m_decors.find(order) == m_decors.end()) {
            return;
        }
        m_decors.at(order).draw();
    }
    void Decor::drawBack(const s3d::RectF& screen) const
    {
        this->draw(DecorOrder::Back, screen);
    }
    void Decor::drawMiddle(const s3d::RectF& screen) const
    {
        this->draw(DecorOrder::Middle, screen);
    }
    void Decor::drawFront(const s3d::RectF & screen) const
    {
        this->draw(DecorOrder::Front, screen);
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
}
