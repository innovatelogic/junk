#pragma once

#include <map>
#include <stdlib.h>
#include <stack>
#include <string>

namespace junk
{
	namespace str_equation_analise
	{
		class Equation
		{
            typedef std::map<std::string, float> TMapTerm;

            enum class eq_sign {
                sign_plus = 0,
                sign_minus,
            };
			struct eq_term
			{
                eq_sign sign;
				std::string p;
				float m;

				eq_term() { clear(); }

                void clear() {
                    sign = eq_sign::sign_plus;
                    m = 1.f;
                    p = "";
                }
			};
			
			public:
				Equation(char *str)
				{
					if (!str){
						throw std::invalid_argument("invalid_argument");
					}
					analise_eq(str, str + strlen(str), 1);
				}

                std::string get_eq_by(std::string &&key)
                {
                    std::string out;

                    TMapTerm::iterator iter_find = m_terms.find(key);

                    if (iter_find != m_terms.end())
                    {
                        float div = iter_find->second;

                        if (div != 0)
                        {
                            out += key + '=';
                            bool first = true;
                            for (TMapTerm::iterator iter = m_terms.begin(); iter != m_terms.end(); ++iter) {
                                if (iter->first != key) 
                                {
                                    float digit = (float)((-1.f * iter->second) / div);

                                    if (!first && digit > 0) {
                                        out += '+';
                                    }
                                    std::string str_d = std::to_string(digit);
                                    str_d.erase(str_d.find_last_not_of('0') + 1, std::string::npos);
                                    out += str_d + iter->first;
                                    first = false;
                                }
                            }
                        }
                    }
                    return out;
                }
				
			private:
				void analise_eq(char *start, char *last, int sign)
				{
                    char *iter = start;
					
					eq_term term; // current eq term
					
					while (iter != last)
					{
						if (*iter == '(')
                        {
                            std::stack<char> p_stack;
                            p_stack.push(*start);

                            char *iter_brace = iter + 1;
							while (iter_brace)
                            {
                                if (*iter_brace == '(') {
                                    p_stack.push(*iter);
                                }
                                else if (*iter_brace == ')') {
                                    p_stack.pop();
                                }
                                if (p_stack.empty()) {
                                    break;
                                }
                                iter_brace++;
							}

                            if (!iter_brace) {
                                throw std::invalid_argument("invalid format");
                            }
							analise_eq(iter + 1, iter_brace, sign * (term.sign == eq_sign::sign_plus ? 1 : -1));
							iter = iter_brace + 1;
							continue;
						}
                        else if (*iter == '=') {
                            analise_eq(iter + 1, last, -1);
                            return;
                        }

                        char *end;
                        process_term(iter, last, term, &end);
						iter = end;

                        // term complete
                        if (is_sign(*iter) || iter == last)
                        {
                            add_term(term, sign);
                            term.clear();
                        }
					}
				}

                void process_term(char *begin, char *last, eq_term &term, char **end)
                {
                    if (is_sign(*begin)) {
                        term.sign = (*begin == '+') ? eq_sign::sign_plus : eq_sign::sign_minus;
                        *end = begin + 1;
                    }
                    else if (!is_digit(*begin)) // 
                    {
                        char *iter = begin + 1;
                        while (iter != last)
                        {
                            if (is_digit(*iter) || is_sign(*iter) || *iter == ')') {
                                break;
                            }
                            ++iter;
                        }
                        term.p.assign(begin, iter - begin);
                        *end = iter;
                    }
                    else // digit
                    {
                        term.m = strtof(begin, end);
                    }
                }
        
        protected:
            void add_term(const eq_term &term, int sign)
            {
                float val = term.m * ((term.sign == eq_sign::sign_minus ? -1 : 1)) * sign;

                if (m_terms.find(term.p) == m_terms.end()){
                    m_terms[term.p] = val;
                }
                else {
                    m_terms[term.p] += val;
                }
            }

            static bool is_digit(const char chr) { return chr >= '0' && chr - '0' <= 9; }
            static bool is_sign(const char chr) { return chr == '+' || chr == '-'; }

			public:
                TMapTerm m_terms;
		};
	}
}