#include "TmxBackGroundDataStore.hpp"
#include <abyss/entities/BackGround/BackGroundEntity.hpp>

namespace abyss
{
	using namespace s3dTiled;

    s3d::Array<BackGroundEntity> TmxBackGroundDataStore::select() const
    {
        s3d::Array<BackGroundEntity> ret;
		auto parser = [&](const GroupLayer& layer) {
			for (const auto& child : layer.getLayers()) {
				child.then([&](const ImageLayer& i) {
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
				});
			}
		};
		m_tmx.getLayer(U"bgs")->then(parser);
        return ret;
    }
}
