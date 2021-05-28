#include "RecoveryVM.hpp"
#include <Siv3D.hpp>
namespace abyss::Actor::Item::Recovery
{
    RecoveryVM::RecoveryVM()
    {}

    void RecoveryVM::draw() const
    {
        Circle(m_pos, 10.0f).draw();
    }
}
