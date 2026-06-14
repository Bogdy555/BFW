#ifndef BFW_Animation_hpp

#define BFW_Animation_hpp



#include "BFW.hpp"



namespace BFW
{

	template <typename T> struct AnimationState
	{

		T State;
		float Begin;
		float End;

		AnimationState(const T& _State = T(), const float _Begin = 0.0f, const float _End = 0.0f) : State(_State), Begin(_Begin), End(_End)
		{

		}

	};

	template <typename T> class Animation
	{

	public:

		Animation() : Time(0.0f), Loop(true), AnimationStates()
		{

		}

		Animation(const Animation& _Other) : Time(_Other.Time), Loop(_Other.Loop), AnimationStates(_Other.AnimationStates)
		{

		}

		Animation(Animation&& _Other) noexcept : Time(_Other.Time), Loop(_Other.Loop), AnimationStates((Vector<AnimationState<T>>&&)(_Other.AnimationStates))
		{
			_Other.Time = 0.0f;
			_Other.Loop = true;
		}

		virtual ~Animation()
		{

		}

		void Update(const float _TimeStep)
		{
			Time += _TimeStep;

			if (Loop)
			{
				while (Time >= AnimationStates[AnimationStates.GetSize() - 1].End)
				{
					Time -= AnimationStates[AnimationStates.GetSize() - 1].End;
				}
			}
			else
			{
				if (Time > AnimationStates[AnimationStates.GetSize() - 1].End)
				{
					Time = AnimationStates[AnimationStates.GetSize() - 1].End;
				}
			}
		}

		void SetTime(const float _Time)
		{
			Time = _Time;
		}

		void SetLoop(const bool _Loop)
		{
			Loop = _Loop;
		}

		virtual const T GetCurrentState() const = 0;

		const size_t GetCurrentStateIndex() const
		{
			for (size_t _Index = 0; _Index < AnimationStates.GetSize(); _Index++)
			{
				if (AnimationStates[_Index].Begin <= Time && Time < AnimationStates[_Index].End)
				{
					return _Index;
				}
			}

			if (Time == AnimationStates[AnimationStates.GetSize() - 1].End)
			{
				return AnimationStates.GetSize() - 1;
			}

			return (size_t)(-1);
		}

		const float GetTime() const
		{
			return Time;
		}

		const bool GetLoop() const
		{
			return Loop;
		}

		Vector<AnimationState<T>>& GetAnimationStates()
		{
			return AnimationStates;
		}

		const Vector<AnimationState<T>>& GetAnimationStates() const
		{
			return AnimationStates;
		}

		Animation& operator= (const Animation& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			Time = _Other.Time;
			Loop = _Other.Loop;
			AnimationStates = _Other.AnimationStates;

			return *this;
		}

		Animation& operator= (Animation&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			Time = _Other.Time;
			Loop = _Other.Loop;
			AnimationStates = (Vector<AnimationState<T>>&&)(_Other.AnimationStates);

			_Other.Time = 0.0f;
			_Other.Loop = true;

			return *this;
		}

	protected:

		float Time;
		bool Loop;
		Vector<AnimationState<T>> AnimationStates;

	};

	template <typename T> class StepAnimation : public Animation<T>
	{

	public:

		StepAnimation() : Animation<T>()
		{

		}

		StepAnimation(const StepAnimation& _Other) : Animation<T>((const Animation<T>&)(_Other))
		{

		}

		StepAnimation(StepAnimation&& _Other) noexcept : Animation<T>((Animation<T>&&)(_Other))
		{

		}

		~StepAnimation()
		{

		}

		const T GetCurrentState() const override
		{
			for (size_t _Index = 0; _Index < AnimationStates.GetSize(); _Index++)
			{
				if (AnimationStates[_Index].Begin <= Time && Time < AnimationStates[_Index].End)
				{
					return AnimationStates[_Index].State;
				}
			}

			if (Time == AnimationStates[AnimationStates.GetSize() - 1].End)
			{
				return AnimationStates[AnimationStates.GetSize() - 1].State;
			}

			return T();
		}

		StepAnimation& operator= (const StepAnimation& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			*(Animation<T>*)(this) = (const Animation<T>&)(_Other);

			return *this;
		}

		StepAnimation& operator= (StepAnimation&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			*(Animation<T>*)(this) = (Animation<T>&&)(_Other);

			return *this;
		}

	private:

		using Animation<T>::Time;
		using Animation<T>::Loop;
		using Animation<T>::AnimationStates;

	};

	template <typename T, const T (*Lerper)(const T, const T, const float)> class LinearAnimation : public Animation<T>
	{

	public:

		LinearAnimation() : Animation<T>()
		{

		}

		LinearAnimation(const LinearAnimation& _Other) : Animation<T>((const Animation<T>&)(_Other))
		{

		}

		LinearAnimation(LinearAnimation&& _Other) noexcept : Animation<T>((Animation<T>&&)(_Other))
		{

		}

		~LinearAnimation()
		{

		}

		const T GetCurrentState() const override
		{
			for (size_t _Index = 0; _Index < AnimationStates.GetSize(); _Index++)
			{
				if (AnimationStates[_Index].Begin <= Time && Time < AnimationStates[_Index].End)
				{
					if (_Index != AnimationStates.GetSize() - 1)
					{
						return Lerper(AnimationStates[_Index].State, AnimationStates[_Index + 1].State, (Time - AnimationStates[_Index].Begin) / (AnimationStates[_Index].End - AnimationStates[_Index].Begin));
					}
					else
					{
						if (Loop)
						{
							return Lerper(AnimationStates[_Index].State, AnimationStates[0].State, (Time - AnimationStates[_Index].Begin) / (AnimationStates[_Index].End - AnimationStates[_Index].Begin));
						}
						else
						{
							return AnimationStates[_Index].State;
						}
					}
				}
			}

			if (Time == AnimationStates[AnimationStates.GetSize() - 1].End)
			{
				return AnimationStates[AnimationStates.GetSize() - 1].State;
			}

			return T();
		}

		LinearAnimation& operator= (const LinearAnimation& _Other)
		{
			if (this == &_Other)
			{
				return *this;
			}

			*(Animation<T>*)(this) = (const Animation<T>&)(_Other);

			return *this;
		}

		LinearAnimation& operator= (LinearAnimation&& _Other) noexcept
		{
			if (this == &_Other)
			{
				return *this;
			}

			*(Animation<T>*)(this) = (Animation<T>&&)(_Other);

			return *this;
		}

	private:

		using Animation<T>::Time;
		using Animation<T>::Loop;
		using Animation<T>::AnimationStates;

	};

}



#endif
