#pragma once

#include <map>

namespace junk
{
	namespace dp_fib_probe_a
	{
        template<typename T>
		int fib(int n)
		{
			if (n <= 1){
				return n;
			}
			return fib<T>(n - 1) + fib<T>(n - 2);
		}

        template<typename T>
        int fib_dp(int n, std::map<int, int> &mem)
        {
            auto iter = mem.find(n);
            if (iter != mem.end()) {
                return iter->second;
            }

            if (n < 2) {
                return n;
            }

            int fib = fib_dp<T>(n - 1, mem) + fib_dp<T>(n - 2, mem);

            mem[n] = fib;

            return fib;
        }
	}


}