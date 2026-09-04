#ifndef BFW_Animation_hpp

#define BFW_Animation_hpp



#include "BFW.hpp"



namespace BFW
{

	namespace Animation
	{

		template <typename T> struct State
		{

			T Value;
			float Begin;
			float End;

			State() : Value(), Begin(0.0f), End(0.0f)
			{

			}

			State(const T& _Value, const float _Begin, const float _End) : Value(_Value), Begin(_Begin), End(_End)
			{

			}

			State(const State& _Other) = default;

			State(State&& _Other) noexcept : Value((T&&)(_Other.Value)), Begin(_Other.Begin), End(_Other.End)
			{
				_Other.Begin = 0.0f;
				_Other.End = 0.0f;
			}

			State& operator= (const State& _Other) requires (!std::is_const_v<T>) = default;

			State& operator= (State&& _Other) noexcept requires (!std::is_const_v<T>)
			{
				if (this == &_Other)
				{
					return *this;
				}

				Value = (T&&)(_Other.Value);
				Begin = _Other.Begin;
				End = _Other.End;

				_Other.Begin = 0.0f;
				_Other.End = 0.0f;

				return *this;
			}

		};

		template <typename T> class Sequence
		{

		private:

			using Type = std::remove_const_t<T>;
			using ConstType = std::add_const_t<T>;

		public:

			Sequence() : Time(0.0f), Loop(true), SequenceStates()
			{

			}

			Sequence(const Sequence& _Other) : Time(_Other.Time), Loop(_Other.Loop), SequenceStates(_Other.SequenceStates)
			{

			}

			Sequence(Sequence&& _Other) noexcept : Time(_Other.Time), Loop(_Other.Loop), SequenceStates((Vector<State<Type>>&&)(_Other.SequenceStates))
			{
				_Other.Time = 0.0f;
				_Other.Loop = true;
			}

			virtual ~Sequence()
			{

			}

			void Update(const float _TimeStep)
			{
				Time += _TimeStep;

				if (Loop)
				{
					while (Time >= SequenceStates[SequenceStates.GetSize() - 1].End)
					{
						Time -= SequenceStates[SequenceStates.GetSize() - 1].End;
					}
				}
				else
				{
					if (Time > SequenceStates[SequenceStates.GetSize() - 1].End)
					{
						Time = SequenceStates[SequenceStates.GetSize() - 1].End;
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

			virtual ConstType GetCurrentState() const = 0;

			const size_t GetCurrentStateIndex() const
			{
				for (size_t _Index = 0; _Index < SequenceStates.GetSize(); _Index++)
				{
					if (SequenceStates[_Index].Begin <= Time && Time < SequenceStates[_Index].End)
					{
						return _Index;
					}
				}

				if (Time == SequenceStates[SequenceStates.GetSize() - 1].End)
				{
					return SequenceStates.GetSize() - 1;
				}

				return std::numeric_limits<size_t>::max();
			}

			const float GetTime() const
			{
				return Time;
			}

			const bool GetLoop() const
			{
				return Loop;
			}

			Vector<State<Type>>& GetSequenceStates() requires (!std::is_const_v<T>)
			{
				return SequenceStates;
			}

			const Vector<State<Type>>& GetSequenceStates() const
			{
				return SequenceStates;
			}

			Sequence& operator= (const Sequence& _Other)
			{
				if (this == &_Other)
				{
					return *this;
				}

				Time = _Other.Time;
				Loop = _Other.Loop;
				SequenceStates = _Other.SequenceStates;

				return *this;
			}

			Sequence& operator= (Sequence&& _Other) noexcept
			{
				if (this == &_Other)
				{
					return *this;
				}

				Time = _Other.Time;
				Loop = _Other.Loop;
				SequenceStates = (Vector<State<Type>>&&)(_Other.SequenceStates);

				_Other.Time = 0.0f;
				_Other.Loop = true;

				return *this;
			}

		protected:

			float Time;
			bool Loop;
			Vector<State<Type>> SequenceStates;

		};

		template <typename T> class StepSequence : public Sequence<T>
		{

		private:

			using Type = std::remove_const_t<T>;
			using ConstType = std::add_const_t<T>;

		public:

			StepSequence() : Sequence<T>()
			{

			}

			StepSequence(const StepSequence& _Other) : Sequence<T>((const Sequence<T>&)(_Other))
			{

			}

			StepSequence(StepSequence&& _Other) noexcept : Sequence<T>((Sequence<T>&&)(_Other))
			{

			}

			~StepSequence()
			{

			}

			ConstType GetCurrentState() const override
			{
				for (size_t _Index = 0; _Index < SequenceStates.GetSize(); _Index++)
				{
					if (SequenceStates[_Index].Begin <= Time && Time < SequenceStates[_Index].End)
					{
						return SequenceStates[_Index].Value;
					}
				}

				if (Time == SequenceStates[SequenceStates.GetSize() - 1].End)
				{
					return SequenceStates[SequenceStates.GetSize() - 1].Value;
				}

				return Type();
			}

			StepSequence& operator= (const StepSequence& _Other)
			{
				if (this == &_Other)
				{
					return *this;
				}

				*(Sequence<T>*)(this) = (const Sequence<T>&)(_Other);

				return *this;
			}

			StepSequence& operator= (StepSequence&& _Other) noexcept
			{
				if (this == &_Other)
				{
					return *this;
				}

				*(Sequence<T>*)(this) = (Sequence<T>&&)(_Other);

				return *this;
			}

		private:

			using Sequence<T>::Time;
			using Sequence<T>::Loop;
			using Sequence<T>::SequenceStates;

		};

		template <typename T, std::add_const_t<T>(*Lerper)(std::add_const_t<T>&, std::add_const_t<T>&, const float)> class LinearSequence : public Sequence<T>
		{

		private:

			using Type = std::remove_const_t<T>;
			using ConstType = std::add_const_t<T>;

		public:

			LinearSequence() : Sequence<T>()
			{

			}

			LinearSequence(const LinearSequence& _Other) : Sequence<T>((const Sequence<T>&)(_Other))
			{

			}

			LinearSequence(LinearSequence&& _Other) noexcept : Sequence<T>((Sequence<T>&&)(_Other))
			{

			}

			~LinearSequence()
			{

			}

			ConstType GetCurrentState() const override
			{
				for (size_t _Index = 0; _Index < SequenceStates.GetSize(); _Index++)
				{
					if (SequenceStates[_Index].Begin <= Time && Time < SequenceStates[_Index].End)
					{
						if (_Index != SequenceStates.GetSize() - 1)
						{
							return Lerper(SequenceStates[_Index].Value, SequenceStates[_Index + 1].Value, (Time - SequenceStates[_Index].Begin) / (SequenceStates[_Index].End - SequenceStates[_Index].Begin));
						}
						else
						{
							if (Loop)
							{
								return Lerper(SequenceStates[_Index].Value, SequenceStates[0].Value, (Time - SequenceStates[_Index].Begin) / (SequenceStates[_Index].End - SequenceStates[_Index].Begin));
							}
							else
							{
								return SequenceStates[_Index].Value;
							}
						}
					}
				}

				if (Time == SequenceStates[SequenceStates.GetSize() - 1].End)
				{
					return SequenceStates[SequenceStates.GetSize() - 1].Value;
				}

				return Type();
			}

			LinearSequence& operator= (const LinearSequence& _Other)
			{
				if (this == &_Other)
				{
					return *this;
				}

				*(Sequence<T>*)(this) = (const Sequence<T>&)(_Other);

				return *this;
			}

			LinearSequence& operator= (LinearSequence&& _Other) noexcept
			{
				if (this == &_Other)
				{
					return *this;
				}

				*(Sequence<T>*)(this) = (Sequence<T>&&)(_Other);

				return *this;
			}

		private:

			using Sequence<T>::Time;
			using Sequence<T>::Loop;
			using Sequence<T>::SequenceStates;

		};

	}

}



#endif
