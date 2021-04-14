#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

namespace abyss::decor
{
    class DecorInfo final : public IComponent
    {
    public:
		DecorInfo(DecorObj* pObj, const DecorEntity& entity);

		s3d::uint32 getId() const { return m_entity.id; }
		s3d::uint32 getGId() const { return m_entity.gId; }
		DecorType getType() const { return m_entity.type; }
		s3d::Vec2 getPos() const { return m_entity.pos; }
		s3d::Vec2 getSize() const { return m_entity.size; }
		double getRotation() const { return m_entity.rotation; }
		bool isMirrored() const { return m_entity.isMirrored; }
		double isFlipped() const { return m_entity.isFlipped; }

		bool isInScreen(const s3d::RectF& screen) const;

		s3d::RectF toRect() const;
		s3d::Quad toQuad() const;
	private:
		DecorObj* m_pObj;

		// 本当はあんましたないけどロジックを統一したいのでﾖｼ
		DecorEntity m_entity;
    };
}