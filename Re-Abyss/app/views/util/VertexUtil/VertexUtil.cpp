#include <abyss/views/util/VertexUtil/VertexUtil.hpp>
#include <Siv3D.hpp>

namespace
{
	using namespace abyss;

	// 以下のコード移植
	// https://github.com/Siv3D/OpenSiv3D/blob/main/Siv3D/src/Siv3D/Renderer2D/Vertex2DBuilder.cpp

	static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

	static constexpr Vertex2D::IndexType RectFrameIndexTable[24] = { 0, 1, 2, 3, 2, 1, 0, 4, 1, 5, 1, 4, 5, 4, 7, 6, 7, 4, 3, 7, 2, 6, 2, 7 };

	static constexpr Vertex2D::IndexType MaxSinCosTableQuality = 40;

	static constexpr Vertex2D::IndexType SinCosTableSize = ((MaxSinCosTableQuality - 5) * (6 + (MaxSinCosTableQuality))) / 2;

	static const std::array<Float2, SinCosTableSize> CircleSinCosTable = []() {
		std::array<Float2, SinCosTableSize> results{};
		Float2* pDst = results.data();

		for (int32 quality = 6; quality <= MaxSinCosTableQuality; ++quality) {
			const float radDelta = Math::TwoPiF / quality;

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				const float rad = (radDelta * i);
				(pDst++)->set(std::cos(rad), -std::sin(rad));
			}
		}

		return results;
	}();

	[[nodiscard]]
	inline const Float2* GetSinCosTableStartPtr(const uint16 quality) noexcept
	{
		return &CircleSinCosTable[((quality - 6) * (6 + (quality - 1))) / 2];
	}

	[[nodiscard]]
	inline constexpr Vertex2D::IndexType CalculateCircleQuality(const float size) noexcept
	{
		if (size <= 5.0f) {
			return static_cast<Vertex2D::IndexType>(size + 3) * 2;
		} else {
			return static_cast<Vertex2D::IndexType>(Min(18 + (size - 5.0f) / 2.2f, 255.0f));
		}
	}

	[[nodiscard]]
	inline constexpr Vertex2D::IndexType CalculateCircleFrameQuality(const float size) noexcept
	{
		if (size <= 1.0f) {
			return 6;
		} else if (size <= 8.0f) {
			return Max(static_cast<Vertex2D::IndexType>(2.0 * size), Vertex2D::IndexType(8));
		} else {
			return static_cast<Vertex2D::IndexType>(Min(16 + (size - 8.0f) / 2.2f, 255.0f));
		}
	}

	[[nodiscard]]
	inline constexpr Vertex2D::IndexType CalculateCirclePieQuality(const float size, const float angle)
	{
		const float rate = Min(Abs(angle) / (Math::TwoPiF) * 2.0f, 1.0f);

		Vertex2D::IndexType quality = 0;

		if (size <= 1.0f) {
			quality = 4;
		} else if (size <= 6.0f) {
			quality = 7;
		} else if (size <= 8.0f) {
			quality = 11;
		} else {
			quality = static_cast<Vertex2D::IndexType>(Min(size * 0.225f + 18.0f, 255.0f));
		}

		return static_cast<Vertex2D::IndexType>(Max(quality * rate, 3.0f));
	}

	[[nodiscard]]
	inline constexpr Vertex2D::IndexType CaluculateFanQuality(const float r) noexcept
	{
		return r <= 1.0f ? 3
			: r <= 6.0f ? 5
			: r <= 12.0f ? 8
			: static_cast<Vertex2D::IndexType>(Min(64.0f, r * 0.2f + 6));
	}

	void DrawCircle(
		const Float2& center,
		float r,
		const VertexUtil::CircleBuildCallback& callback,
		const VertexUtil::VertexCallback& fixCallback
	) {
		const float absR = Abs(r);

		constexpr float scale = 1.0f;
		const Vertex2D::IndexType quality = ::CalculateCircleQuality(absR * scale);
		const Vertex2D::IndexType vertexSize = (quality + 1), indexSize = (quality * 3);

		Buffer2D buffer(vertexSize, indexSize);
		Vertex2D* pVertex = buffer.vertices.data();
		Vertex2D::IndexType* pIndex = &buffer.indices.data()->i0;

		if (!pVertex) {
			return;
		}

		// 中心
		const float centerX = center.x;
		const float centerY = center.y;
		pVertex[0].pos.set(centerX, centerY);

		// 周
		if (quality <= ::MaxSinCosTableQuality) {
			const Float2* pCS = ::GetSinCosTableStartPtr(quality);
			Vertex2D* pDst = &pVertex[1];

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				(pDst)->pos.set(r * pCS->x + centerX, r * pCS->y + centerY);
				if (callback) {
					callback(pDst, pCS->x, pCS->y);
				}
				pDst++;
				++pCS;
			}
		} else {
			const float radDelta = Math::TwoPiF / quality;
			Vertex2D* pDst = &pVertex[1];

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				const float rad = (radDelta * i);
				const auto [s, c] = FastMath::SinCos(rad);
				(pDst)->pos.set(centerX + r * c, centerY - r * s);
				if (callback) {
					callback(pDst, c, -s);
				}
				pDst++;
			}
		}

		{
			if (fixCallback) {
				fixCallback(pVertex, vertexSize);
			}
		}

		{
			for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i) {
				*pIndex++ = (i + 1);
				*pIndex++ = 0;
				*pIndex++ = (i + 2);
			}

			*pIndex++ = quality;
			*pIndex++ = 0;
			*pIndex++ = 1;
		}

		buffer.draw();
	}

	void DrawCircleFrame(
		const Float2& center,
		const float rInner,
		const float thickness,
		const VertexUtil::CircleFrameBuildCallback& callback,
		const VertexUtil::VertexCallback& fixCallback
	) {
		const float rOuter = (rInner + thickness);

		constexpr float scale = 1.0f;
		const Vertex2D::IndexType quality = ::CalculateCircleFrameQuality(rOuter * scale);
		const Vertex2D::IndexType vertexSize = (quality * 2), indexSize = (quality * 6);

		Buffer2D buffer(vertexSize, indexSize);
		Vertex2D* pVertex = buffer.vertices.data();
		Vertex2D::IndexType* pIndex = &buffer.indices.data()->i0;

		if (!pVertex) {
			return;
		}

		const float centerX = center.x;
		const float centerY = center.y;

		if (quality <= ::MaxSinCosTableQuality) {
			const Float2* pCS = ::GetSinCosTableStartPtr(quality);
			Vertex2D* pDst = pVertex;

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				(pDst)->pos.set(centerX + rOuter * pCS->x, centerY + rOuter * pCS->y);
				auto outerVertex = pDst++;
				(pDst)->pos.set(centerX + rInner * pCS->x, centerY + rInner * pCS->y);
				auto innerVertex = pDst++;
				if (callback) {
					callback(outerVertex, innerVertex, pCS->x, pCS->y);
				}

				++pCS;
			}
		} else {
			const float radDelta = Math::TwoPiF / quality;
			Vertex2D* pDst = pVertex;

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				const float rad = (radDelta * i);
				const auto [s, c] = FastMath::SinCos(rad);

				(pDst)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
				auto outerVertex = pDst++;
				(pDst)->pos.set(centerX + rInner * c, centerY - rInner * s);
				auto innerVertex = pDst++;
				if (callback) {
					callback(outerVertex, innerVertex, c, -s);
				}
			}
		}

		if (fixCallback) {
			fixCallback(pVertex, vertexSize);
		}

		for (Vertex2D::IndexType i = 0; i < quality; ++i) {
			for (Vertex2D::IndexType k = 0; k < 6; ++k) {
				*pIndex++ = ((i * 2 + ::RectIndexTable[k]) % (quality * 2));
			}
		}

		buffer.draw();
	}

	void DrawCircleArc(
		const Float2& center,
		const float rInner,
		const float startAngle,
		const float _angle,
		const float thickness,
		const VertexUtil::CircleFrameBuildCallback& callback,
		const VertexUtil::VertexCallback& fixCallback
	)
	{
		if (_angle == 0.0f) {
			return;
		}

		const float angle = Clamp(_angle, -Math::TwoPiF, Math::TwoPiF);
		const float rOuter = rInner + thickness;
		constexpr float scale = 3.0f;
		const Vertex2D::IndexType quality = ::CalculateCirclePieQuality(rOuter * scale, angle);
		const Vertex2D::IndexType vertexSize = (quality * 2), indexSize = ((quality - 1) * 6);

		Buffer2D buffer(vertexSize, indexSize);
		Vertex2D* pVertex = buffer.vertices.data();
		Vertex2D::IndexType* pIndex = &buffer.indices.data()->i0;

		if (!pVertex) {
			return;
		}

		{
			const float centerX = center.x;
			const float centerY = center.y;
			const float radDelta = Math::TwoPiF / (quality - 1);
			const float start = -(startAngle + angle) + Math::HalfPiF;
			const float angleScale = (angle / Math::TwoPiF);
			Vertex2D* pDst = pVertex;

			for (Vertex2D::IndexType i = 0; i < quality; ++i) {
				const float rad = start + (radDelta * i) * angleScale;
				const auto [s, c] = FastMath::SinCos(rad);
				(pDst)->pos.set(centerX + rOuter * c, centerY - rOuter * s);
				auto outerVertex = pDst++;
				(pDst)->pos.set(centerX + rInner * c, centerY - rInner * s);
				auto innerVertex = pDst++;
				if (callback) {
					callback(outerVertex, innerVertex, c, -s);
				}
			}
		}

		if (fixCallback) {
			fixCallback(pVertex, vertexSize);
		}

		for (Vertex2D::IndexType i = 0; i < (quality - 1); ++i) {
			for (Vertex2D::IndexType k = 0; k < 6; ++k) {
				*pIndex++ = (i * 2 + ::RectIndexTable[k]);
			}
		}
		buffer.draw();
	}
}
namespace abyss
{
	void VertexUtil::DrawCircle(
		const s3d::Circle& circle,
		const CircleBuildCallback& callback,
		const VertexCallback& fixCallback
	) {
		::DrawCircle(
			circle.center,
			static_cast<float>(circle.r),
			callback,
			fixCallback
		);
	}
	void VertexUtil::DrawCircleFrame(
		const s3d::Circle& circle,
		double innerThickness,
		double outerThickness,
		const CircleFrameBuildCallback& callback,
		const VertexCallback& fixCallback
	) {
		::DrawCircleFrame(
			circle.center,
			static_cast<float>(circle.r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			callback,
			fixCallback
		);
	}
	void VertexUtil::DrawCircleArc(
		const s3d::Circle& circle,
		double startAngle,
		double angle,
		double innerThickness, 
		double outerThickness,
		const CircleFrameBuildCallback& callback,
		const VertexCallback& fixCallback
	) {
		::DrawCircleArc(
			circle.center,
			static_cast<float>(circle.r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			callback,
			fixCallback
		);
	}
}