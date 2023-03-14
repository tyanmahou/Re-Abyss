#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    class ModeUtil
    {
    public:
        /// <summary>
        /// ロック解除されてるか
        /// </summary>
        /// <param name="pUi"></param>
        /// <param name="mode"></param>
        /// <returns></returns>
        static bool IsUnlocked(UIObj* pUi, Mode mode);

        /// <summary>
        /// ロックされているか
        /// </summary>
        /// <param name="pUi"></param>
        /// <param name="mode"></param>
        /// <returns></returns>
        static bool IsLocked(UIObj* pUi, Mode mode);

        /// <summary>
        /// 全モードに適用
        /// </summary>
        /// <param name="func"></param>
        static void ForEach(std::function<void(Mode mode)> func);
    };
}
