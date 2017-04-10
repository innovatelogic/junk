#pragma once

#include <map>

namespace junk
{
	namespace dp_fib_probe_a
	{
		int fib(int n)
		{
			if (n <= 1){
				return n;
			}
			return fib(n - 1) + fib(n - 2);
		}

        int fib_dp(int n, std::map<int, int> &mem)
        {
            auto iter = mem.find(n);
            if (iter != mem.end()) {
                return iter->second;
            }

            if (n < 2) {
                return n;
            }

            int fib = fib_dp(n - 1, mem) + fib_dp(n - 2, mem);

            mem[n] = fib;

            return fib;
        }
	}


}