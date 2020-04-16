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
					BackGroundEntity entity{
						.id = i.getId(),
						.name = i.getName(),
						.filePath = i.getImagePath(),
						.offset = i.getOffset(),
						.loop = { i.getProperty(U"loopX").value_or(false),i.getProperty(U"loopY").value_or(false) },
						.rate = { i.getProperty(U"rateX").value_or(1.0), i.getProperty(U"rateY").value_or(1.0) }
					};
					ret.push_back(std::move(entity));
				});
			}
		};
		m_tmx.getLayer(U"bgs")->then(parser);
        return ret;
    }
}
