#pragma once

namespace junk
{
	namespace reverse_int_probe_a
	{
        template<typename T>
		int reverse(int n)
		{
			int out = 0;
			
			while (n > 0)
			{
				out = out * 10 + n % 10;
				n /= 10;
			}
			return out;
		}
	}
}