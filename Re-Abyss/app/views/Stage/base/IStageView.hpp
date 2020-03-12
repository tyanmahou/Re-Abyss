#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class IStageView
	{
	public:
		virtual ~IStageView() = default;

		/// <summary>
		/// 背面
		/// </summary>
		/// <param name="camera"></param>
		virtual void drawBack(const CameraView& camera) const= 0;

		/// <summary>
		/// 中面
		/// </summary>
		/// <param name="camera"></param>
		virtual void drawMiddle(const CameraView& camera) const= 0;

		/// <summary>
		/// 前面
		/// </summary>
		/// <param name="camera"></param>
		virtual void drawFront(const CameraView& camera) const = 0;
	};
}