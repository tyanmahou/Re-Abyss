#include "../include/S3DTiled/TiledObject.hpp"

#include<Siv3D/XMLReader.hpp>
#include<Siv3D/Parse.hpp>


namespace s3dTiled
{
	void TiledObject::setProps(TiledProperties&& _props)
	{
		this->props = std::move(_props);
	}

	s3d::Optional<TiledProperty> TiledObject::getProperty(const s3d::String& key) const
	{
		if (props.find(key) != props.end()) {
			return props.at(key);
		}
		return s3d::none;
	}

}