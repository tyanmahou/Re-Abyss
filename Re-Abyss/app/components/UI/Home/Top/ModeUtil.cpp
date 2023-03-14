#include <abyss/components/UI/Home/Top/ModeUtil.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::Home::Top
{
    bool ModeUtil::IsUnlocked([[maybe_unused]]UIObj* pUi, Mode mode)
    {
        switch (mode)
        {
        case Mode::Seek:
            return true;
        case Mode::Guild:
            return false;
        case Mode::Maint:
            return false;
        case Mode::Memory:
            return false;
        case Mode::Collect:
            return false;
        case Mode::Option:
            return true;
        default:
            break;
        }
        return false;
    }
    bool ModeUtil::IsLocked(UIObj* pUi, Mode mode)
    {
        return !IsUnlocked(pUi, mode);
    }
    void ModeUtil::ForEach(std::function<void(Mode)> func)
    {
        for (Mode mode = Mode::Seek; mode < Mode::Max; ++mode) {
            func(mode);
        }
    }
}
