#include <string>

namespace junk
{
	namespace string_convert_probe_a
	{
		template<typename T>
		std::string int_to_str(int number, int base)
		{
			if (!(base == 2 || base == 10 || base == 16)){
				return std::string(""); // throw exception
			}
			bool minus = false;
			if (number < 0){
				minus = true;
				number *= -1;
			}
			
			std::string out;
			
			do
			{
				out = "0123456789ABCDEF"[ number % base] + out;
				number /= base;
			}while (number > 0);
			
			if (minus){
				out = std::string("-") + out;
			}
			return out;
		}
		
		template<typename T>
		int str_to_int(const std::string &str)
		{
			int out = 0;
            bool minus = false;

			if (!str.empty())
			{
				if (str[0] == '-'){
					minus = true;
				}
				
				for (size_t i = minus ? 1 : 0; i < str.size(); i++)
				{
					int digit = str[i] - '0';
					
					if (digit >= 0 && digit <= 9){
						out = out * 10 + digit;
					}
					else{
						return 0;
					}
				}
			}
			
			return (minus ? -1 : 1) * out;
		}

        template<typename T>
        int ConvertStringToInt(const char *str)
        {
            int out = 0;
            bool minus = false;

            if (str)
            {
                size_t len = strlen(str);
                if (len > 0)
                {
                    if (str[0] == '-') {
                        minus = true;
                    }

                    for (size_t i = minus ? 1 : 0; i < len; i++)
                    {
                        int digit = str[i] - '0';

                        if (digit >= 0 && digit <= 9) {
                            out = out * 10 + digit;
                        }
                        else {
                            return 0;
                        }
                    }
                }
            }

            return (minus ? -1 : 1) * out;
        }
	}
}