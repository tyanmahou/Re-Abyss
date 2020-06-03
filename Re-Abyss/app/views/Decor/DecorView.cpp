#include "DecorView.hpp"
#include <abyss/views/Decor/base/IDecorVM.hpp>

namespace abyss
{
    void DecorView::add(s3d::int32 order, const std::shared_ptr<IDecorVM>& vm)
    {
        m_decors[order].push_back(vm);
    }

    void DecorView::clear()
    {
        m_decors.clear();
    }
    void DecorView::update(double time)
    {
        for (auto& decor : m_decors) {
            for (const auto& vm : decor.second) {
                vm->setTime(time);
            }
        }
    }
    void DecorView::draw(s3d::int32 order, const s3d::RectF& screen) const
    {
        if (m_decors.find(order) == m_decors.end()) {
            return;
        }
        for (const auto& vm : m_decors.at(order)) {
            vm->draw(screen);
        }
    }
}
