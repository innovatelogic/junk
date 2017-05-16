#pragma once

namespace junk
{
	namespace cpp_test_code
	{

		class MyClassA
		{
		private:
			int	a;
		public:
			MyClassA()
			: a(0)
			{
			}

			// SetA changes internal state of class so it should not be const
			// const int _val does not nesseseary by passing by value (change to int)
			void SetA(int _val)
			{
				a = _val;
			}

			virtual void Process() = 0; // pure virtual function every derived class
										// should implement it
		};

		class MyClassB : public MyClassA
		{
		private:
			int	b;
		public:
			MyClassB()
			{
				SetA(1); // a = 1; -> a is private in public class so we need to use SetA function
				b = 2;
			}

			void Process() override // implement pure virtual function in A
			{

			}
		};

		void MyFunction()
		{
			MyClassB	toto;
			toto.Process();
		}
	}
}

