#include <abyss/commons/Resource/Preload/Message.hpp>

#include <abyss/commons/Msg/Common.hpp>
#include <abyss/commons/Msg/Title.hpp>
#include <abyss/commons/Msg/SaveSelect.hpp>

namespace abyss::Resource::Preload
{
	Preloader Message(s3d::StringView lang)
	{
        PreloadInfo info{};
        auto prefix = s3d::Fmt(Path::MsgPath)(lang);
        info.custom << [prefix](const Assets* assets) {
            assets->loadToml<Msg::Common>(U"Common.toml", prefix);
        };
        info.custom << [prefix](const Assets* assets) {
            assets->loadToml<Msg::Title>(U"Title.toml", prefix);
        };
        info.custom << [prefix](const Assets* assets) {
            assets->loadToml<Msg::SaveSelect>(U"SaveSelect.toml", prefix);
        };
		return Preloader(std::move(info));
	}
}
