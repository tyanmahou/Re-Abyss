#include <abyss/types/UserPlayMode.hpp>
#include <abyss/commons/Msg/Common.hpp>

namespace abyss
{
    s3d::String Name(UserPlayMode value)
    {
        if (value == UserPlayMode::Normal) {
            return Msg::Common::UserPlayMode::Normal;
        }
        if (value == UserPlayMode::Hard) {
            return Msg::Common::UserPlayMode::Hard;
        }
        return Msg::Common::UserPlayMode::Normal;
    }
}