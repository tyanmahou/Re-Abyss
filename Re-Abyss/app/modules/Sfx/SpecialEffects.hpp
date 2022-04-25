#pragma once
#include <abyss/modules/Sfx/Flush/Flush.hpp>
#include <abyss/modules/Sfx/SkipFade/SkipFade.hpp>
#include <abyss/modules/Sfx/BossFade/BossFade.hpp>

namespace abyss::Sfx
{
	/// <summary>
	/// Supecial Effect
	/// </summary>
	class SpecialEffects
	{
	public:
		Flush* flush()
		{
			return &m_flush;
		}
		SkipFade* skipFade()
		{
			return &m_skipFade;
		}
		BossFade* bossFade()
		{
			return &m_bossFade;
		}
		void setManager(Manager* pManager)
		{
			m_pManager = pManager;
		}
	public:
		void update(double dt);
		void draw() const;
	private:
		Manager* m_pManager;
		Flush m_flush;
		SkipFade m_skipFade;
		BossFade m_bossFade;
	};
}