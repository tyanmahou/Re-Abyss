#pragma once

#pragma warning(push)
#pragma warning(disable:26812)

namespace abyss
{
	// 梯子状態
	struct LadderStateModel
	{
		enum State
		{
			None = 0x0,
			IsLadder = 0x1,
			IsLadderTop = 0x3,
			CanLadder = 0x4,
		}state = None;

		LadderStateModel() = default;
		LadderStateModel(State s) :
			state(s)
		{}

		void setIsLadder()
		{
			state = static_cast<State>(state | IsLadder);
		}
		bool isLadder() const
		{
			return (state & IsLadder) != 0;
		}
		void setLadderTop()
		{
			state = static_cast<State>(state | IsLadderTop);
		}
		void cancelLadderTop()
		{
			state = static_cast<State>(state & ~0x2);
		}
		bool isLadderTop() const
		{
			return (static_cast<State>(state & IsLadderTop) == IsLadderTop);
		}
		operator bool() const
		{
			return this->isLadder();
		}
		void setCanLadder()
		{
			state = static_cast<State>(state | CanLadder);
		}
		bool canLadder()const
		{
			return (state & CanLadder) != 0;
		}

		void reset()
		{
			if (!this->isLadder() || !this->canLadder()) {
				state = None;
			}
			state = static_cast<State>(state & ~CanLadder);
		}
	};
}

#pragma warning(pop)
