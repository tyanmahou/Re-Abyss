#include "CameraFixCtrl.hpp"

namespace abyss
{
    s3d::Vec2 CameraFixCtrl::apply(const s3d::Vec2& targetPos) const
    {
        s3d::Vec2 ret = targetPos;
        for (const auto& fix : m_fixs) {
            if (fix) {
                ret = fix->apply(ret);
            }
        }
        return ret;
    }
    void CameraFixCtrl::add(const std::shared_ptr<ICameraFix>& fix)
    {
        m_fixs.push_back(fix);
        m_fixs.sort_by([](const std::shared_ptr<ICameraFix>& a, const std::shared_ptr<ICameraFix>& b) {
            return a->priority() < b->priority();
        });
    }
    void CameraFixCtrl::remove(const std::shared_ptr<ICameraFix>&fix)
    {
        m_fixs.remove(fix);
    }
}
