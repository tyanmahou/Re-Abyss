#include <abyss/utils/DebugMenu/Root.hpp>
#include <abyss/utils/DebugMenu/DefaultSkin.hpp>
#include <Siv3D.hpp>

namespace abyss::DebugMenu
{
	Root::Root():
		m_skin(std::make_unique<DefaultSkin>())
	{
	}
	void Root::draw() const
	{
		Transformer2D transformer(Mat3x2::Translate(10, 10), s3d::TransformCursor::Yes);
		const s3d::Array<s3d::StringView> labels{
			U"AAAAAA",
			U"BBB",
			U"CCCCCCC"
		};
		m_skin->draw(labels, 1);
	}
}
