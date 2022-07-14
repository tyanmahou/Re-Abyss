#pragma once
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/UI/Dialog/DialogResult.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::UI::DialogUtil
{
    template<class Type, class... Args>
    concept DialogBuildy = requires
    {
        typename Type::value_type;
        requires UIBuildy<Type, Args...>;
    };

    template<class BuilderType, class ResultType, class... Args>
    [[nodiscard]] Coro::Task<ResultType> Wait(GameObject* pObj, Args&&... args)
    {
        auto dialog = pObj->getModule<UIs>()->create<BuilderType>(std::forward<Args>(args)...);
        auto result = dialog->find<Dialog::DialogResult<ResultType>>();
        while (result) {
            if (const auto& ret = result->get()) {
                if (dialog) {
                    dialog->destroy();
                }
                co_return *ret;
            }
            co_yield{};
        }
        if (dialog) {
            dialog->destroy();
        }
        co_return{};
    }

    template<class BuildType, class... Args> requires DialogBuildy<BuildType, Args...>
    [[nodiscard]] Coro::Task<typename BuildType::value_type> Wait(GameObject* pObj, Args&&... args)
    {
        return Wait<BuildType, typename BuildType::value_type, Args...>(pObj, std::forward<Args>(args)...);
    }
}
