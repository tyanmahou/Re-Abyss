#include "TmxBackGroundDataStore.hpp"
#include <abyss/entities/BackGround/BackGroundEntity.hpp>
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace abyss
{
	using namespace s3dTiled;

    s3d::Array<BackGroundEntity> TmxBackGroundDataStore::select() const
    {
        s3d::Array<BackGroundEntity> ret;
		auto layer = m_tmx.getLayer(U"bgs");
		if (!layer) {
			return ret;
		}
		auto parser = [&](const ImageLayer& i) {
			BackGroundEntity entity;
			entity.id = i.getId();
			entity.name = i.getName();
			entity.filePath = i.getImagePath();
			entity.offset = i.getOffset();
			entity.fix = { i.getProperty(U"fixX").value_or(false),i.getProperty(U"fixY").value_or(false) };
			if (auto rateX = i.getProperty(U"rateX")) {
				entity.rate.x = rateX->toFloat();
			}
			if (auto rateY = i.getProperty(U"rateY")) {
				entity.rate.y = rateY->toFloat();
			}
			ret.push_back(std::move(entity));
		};

		TmxParseUtil::ParseForGroup(*layer, parser);

        return ret;
    }
	s3d::Color TmxBackGroundDataStore::getBgColor() const
	{
		return m_tmx.getBackGroundColor().value_or(s3d::Palette::Black);
	}
}
