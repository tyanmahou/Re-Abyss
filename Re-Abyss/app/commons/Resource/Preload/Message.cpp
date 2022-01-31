#include <abyss/commons/Resource/Preload/Message.hpp>

#include <abyss/commons/Msg/Common.hpp>
#include <abyss/commons/Msg/Title.hpp>
#include <abyss/commons/Msg/SaveSelect.hpp>

namespace abyss::Resource::Preload
{
	void LoadMessage(s3d::StringView lang, const Assets* resource)
	{
		auto prefix = s3d::Fmt(Path::MsgPath)(lang);
		resource->loadToml<Msg::Common>(U"Common.toml", prefix);
		resource->loadToml<Msg::Title>(U"Title.toml", prefix);
		resource->loadToml<Msg::SaveSelect>(U"SaveSelect.toml", prefix);
	}
}
