#include <abyss/components/UI/Home/Top/ModeUpdater.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::UI::Home::Top
{
    ModeUpdater::ModeUpdater()
    {
        // Mode ↑→↓←
        m_changerMap[Mode::Seek] = { s3d::none, Mode::Guild, Mode::Maint, Mode::Maint };
        m_changerMap[Mode::Guild] = { Mode::Seek, Mode::Collect, Mode::Memory, Mode::Seek };
        m_changerMap[Mode::Maint] = { Mode::Seek, Mode::Memory, s3d::none, s3d::none };
        m_changerMap[Mode::Memory] = { Mode::Guild, Mode::Guild, s3d::none, Mode::Maint };
        m_changerMap[Mode::Collect] = { s3d::none, s3d::none, Mode::Option, Mode::Guild};
        m_changerMap[Mode::Option] = { Mode::Collect, s3d::none, s3d::none, Mode::Guild };
    }
    Mode ModeUpdater::update(Mode mode) const
    {
        if (InputManager::Up.down()) {
            if (const auto& next = m_changerMap.at(mode)[0]) {
                return *next;
            }
        } else if (InputManager::Right.down()) {
            if (const auto& next = m_changerMap.at(mode)[1]) {
                return *next;
            }
        } else if (InputManager::Down.down()) {
            if (const auto& next = m_changerMap.at(mode)[2]) {
                return *next;
            }
        } else if (InputManager::Left.down()) {
            if (const auto& next = m_changerMap.at(mode)[3]) {
                return *next;
            }
        }
        return mode;
    }
}
