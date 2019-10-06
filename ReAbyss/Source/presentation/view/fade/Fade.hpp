#pragma once

#include<functional>
#include<type_traits>
#include<Siv3D/Fwd.hpp>


namespace abyss
{
	/// <summary>
	/// �t�F�[�h�Ɏg�p�ł���֐���
	/// </summary>
	template<class Func, class... Args>
	concept IsFadeFunc = std::is_invocable_v<Func, double, Args...>;

	/// <summary>
	/// �t�F�[�h�C��
	/// </summary>
	template<class Func, class... Args> 
	void FadeIn(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(1.0 - t, std::forward<Args>(args)...);
	}

	/// <summary>
	/// �t�F�[�h�A�E�g
	/// </summary>
	template<class Func, class... Args>
	void FadeOut(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(t, std::forward<Args>(args)...);
	}

	/// <summary>
	/// �t�F�[�h�̎�ފ֐��Q
	/// </summary>
	namespace Fade
	{
		/// <summary>
		/// �ʏ�̃t�F�[�h
		/// </summary>
		void Default(double t);

		/// <summary>
		/// �~�`�؂蔲��
		/// </summary>
		void SmoothCircle(double t, const s3d::RectF& rect, const s3d::Vec2& pos);
	}
}
