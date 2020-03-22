#pragma once

#pragma warning(push)
#pragma warning(disable:26812)

namespace abyss
{
	// 梯子状態
	class LadderStateModel
	{
	public:
		enum State
		{
			None = 0x0,
			IsLadder = 0x1,
			IsLadderTop = 0x3,
			CanLadder = 0x4,
		};
	private:
		State m_state = None;
	public:
		LadderStateModel() = default;
		LadderStateModel(State s) :
			m_state(s)
		{}

		void setIsLadder()
		{
			m_state = static_cast<State>(m_state | IsLadder);
		}
		bool isLadder() const
		{
			return (m_state & IsLadder) != 0;
		}
		void setLadderTop()
		{
			m_state = static_cast<State>(m_state | IsLadderTop);
		}
		void cancelLadderTop()
		{
			m_state = static_cast<State>(m_state & ~0x2);
		}
		bool isLadderTop() const
		{
			return (static_cast<State>(m_state & IsLadderTop) == IsLadderTop);
		}
		operator bool() const
		{
			return this->isLadder();
		}
		void setCanLadder()
		{
			m_state = static_cast<State>(m_state | CanLadder);
		}
		bool canLadder()const
		{
			return (m_state & CanLadder) != 0;
		}

		void reset()
		{
			if (!this->isLadder() || !this->canLadder()) {
				m_state = None;
			}
			m_state = static_cast<State>(m_state & ~CanLadder);
		}
	};
}

#pragma warning(pop)
