#pragma once
#include <abyss/models/User/UserModel.hpp>

namespace abyss::UI::SaveSelect::CreateUserConfirm
{
    struct Result
    {
        bool isBack = false;
        UserPlayMode playMode = UserPlayMode::Normal;
    };
}