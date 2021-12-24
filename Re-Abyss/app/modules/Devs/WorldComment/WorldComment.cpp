#include "WorldComment.hpp"
#include <abyss/commons/FontName.hpp>
#include <Siv3D.hpp>

namespace abyss::Devs
{
	struct WorldComment::Requestor::Handle
	{
		Handle(WorldComment* _pWorldComment) :
			pWorldComment(_pWorldComment),
			id(_pWorldComment->m_idCounter.createId()),
			offset(0, 0)
		{}

		WorldComment* pWorldComment;
		s3d::uint64 id;
		s3d::Vec2 offset;
		bool isGrab = false;
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

	std::unique_ptr<WorldComment::Requestor> WorldComment::getRequestor()
	{
		return std::unique_ptr<Requestor>(new Requestor(this));
	}

	void WorldComment::flush()
	{
		m_records.clear();
	}
	void WorldComment::draw()
	{
		auto&& font = FontAsset(FontName::Serif);
		bool alreadyGlabOther = false;
		for (const auto& [handle, text, pos, color] : m_records) {
			if (!handle) {
				continue;
			}
			auto&& drawbleText = font(text);

			auto commentPos = pos + Vec2{ 0, -drawbleText.regionAt().h - 30 } + handle->offset;
			auto region = drawbleText.regionAt(commentPos).stretched(10.0);

			auto backColor = region.mouseOver() ? ColorF(color).setA(0.6) : ColorF(color).setA(0.5);
			{
				Vec2 bc = region.bottomCenter();
				auto offs = s3d::Min(10.0, region.w / 4.0);
				s3d::Triangle(
					bc.movedBy(-offs, 0),
					bc.movedBy(offs, 0),
					pos
				).draw(backColor);
			}
			region.draw(backColor);
			if (m_selectId == handle->id) {
				region.drawFrame(5.0f, ColorF(color).setA(0.8));
			}
			drawbleText.drawAt(commentPos, s3d::Palette::Black);
			if (!alreadyGlabOther && region.leftClicked()) {
				m_selectId = handle->id;
				handle->isGrab = true;
				alreadyGlabOther = true;
			} else if (MouseL.up()) {
				handle->isGrab = false;
			}
			if (handle->isGrab) {
				handle->offset += Cursor::Delta();
			}
		}
	}
	void WorldComment::request(Record&& record)
	{
		m_records.push_back(std::move(record));
	}
}