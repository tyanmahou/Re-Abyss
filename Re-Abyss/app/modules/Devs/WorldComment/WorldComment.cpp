#include "WorldComment.hpp"
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>

namespace abyss::Devs
{
	struct WorldComment::Record
	{
		Ref<Requestor::Handle> handle;
		s3d::String text;
		s3d::Vec2 pos;
		s3d::ColorF color;
	};
	struct WorldComment::Requestor::Handle
	{
		Handle(WorldComment* _pWorldComment) :
			pWorldComment(_pWorldComment),
			id(_pWorldComment->m_idCounter.createId())
		{}

		WorldComment* pWorldComment;
		s3d::uint64 id;
		s3d::Optional<s3d::Vec2> commentPos;
	};
	void WorldComment::Requestor::comment(const s3d::String& text, const s3d::Vec2& pos, const s3d::ColorF& color) const
	{
		m_pHandle->pWorldComment->request(Record{
			.handle = m_pHandle,
			.text = text,
			.pos = pos,
			.color = color
		});
	}
	WorldComment::Requestor::Requestor(WorldComment* pWorldComment) :
		m_pHandle(std::make_shared<Handle>(pWorldComment))
	{}

	void WorldComment::flush()
	{
		m_records.clear();
	}
	void WorldComment::draw()
	{
		auto&& font = FontAsset(FontName::Serif);
		for (const auto& [handle, text, pos, color] : m_records) {
			if (!handle) {
				continue;
			}
			auto&& drawbleText = font(text);
			if (!handle->commentPos) {
				handle->commentPos = pos + Vec2{ 0, -drawbleText.regionAt().h - 10 };
			}
			auto region = drawbleText.regionAt(handle->commentPos.value_or(pos));
			{
				Vec2 bc = region.bottomCenter();
				auto offs = s3d::Min(5.0, region.w / 4.0);
				s3d::Triangle(
					bc.movedBy(-offs, 0),
					bc.movedBy(offs, 0),
					pos
				).draw(color);
			}
			region.draw(color);
			if (m_selectId == handle->id) {
				region.drawFrame(1.0f, color);
			}
			drawbleText.drawAt(pos, s3d::Palette::Black);
		}
	}
	void WorldComment::request(Record&& record)
	{
		m_records.push_back(std::move(record));
	}
}