#include <abyss/datastores/Attribute/TmxAttributeDataStore.hpp>

namespace abyss::Attribute
{
	s3d::Color TmxAttributeDataStore::getBgColor() const
	{
		return m_tmx.getBackGroundColor().value_or(s3d::Palette::Black);
	}
}