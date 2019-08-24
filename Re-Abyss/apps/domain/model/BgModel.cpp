//#include "BgModel.hpp"
//#include "../common/Constants.hpp"
//#include <S3DTiled/TiledLayer.hpp>
//#include <Siv3D/TextureRegion.hpp>
//
//using namespace s3dTiled;
//
//abyss::BgModel::BgModel(const ImageLayer& imageLayer):
//	m_texture(imageLayer.getTexture()),
//	m_offset(imageLayer.getOffset()),
//	m_loop({
//		imageLayer.getProperty(L"loopX").value_or(false),
//	    imageLayer.getProperty(L"loopY").value_or(false)
//	}),
//	m_rate({
//		imageLayer.getProperty(L"rateX").value_or(1.0),
//		imageLayer.getProperty(L"rateY").value_or(1.0)
//	})
//{}
//
//void abyss::BgModel::draw(const s3d::Vec2& pos) const
//{
//	const auto& screen = Constants::GameScreenSize;
//	
//	double u = m_loop.x ? (pos.x - screen.x/2 - m_offset.x) / screen.x / m_rate.x : 0;
//	double v = m_loop.y ? (pos.y - screen.y/2 - m_offset.y) / screen.y / m_rate.y : 0;
//	double x = m_loop.x ? pos.x : m_offset.x + m_texture.size.x /2;
//	double y = m_loop.y ? pos.y : m_offset.y + m_texture.size.y /2;
//	m_texture.uv(u, v, 1, 1).drawAt({ x, y });
//}
