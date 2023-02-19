#include <abyss/values/UserPlayMode.hpp>
#include <abyss/commons/Msg/Manager.hpp>

namespace abyss
{
    s3d::String Name(UserPlayMode value)
    {
        if (value == UserPlayMode::Normal) {
            return Msg::Text(U"Common", U"UserPlayMode_Normal");
        }
        if (value == UserPlayMode::Hard) {
            return Msg::Text(U"Common", U"UserPlayMode_Hard");
        }
        return Msg::Text(U"Common", U"UserPlayMode_Normal");
    }
}
