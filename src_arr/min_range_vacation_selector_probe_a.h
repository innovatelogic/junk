#pragma once

#include <map>
#include <vector>
#include <utility>
#include <limits>

namespace junk
{
	namespace vacation_selector
	{
		class VacationSelector
		{
			public:
				VacationSelector(const std::vector<std::pair<char, int>> &vacations)
					: m_idx(0)
					, m_size(0)
					, m_value(INT_MAX){
					process(vacations);
				}
				
				void process(const std::vector<std::pair<char, int>> &vacations)
				{
					// to identify unique set 
					std::map<char, int> flags;
					for (const auto &v : vacations){
						flags[v.first] = 0;
					}
				
					// use slow & fast runner
					size_t slow = 0;
                    size_t fast = 0;

                    const size_t v_size = vacations.size();
					do
					{
						bool is_full_set = true;
						for (const auto &f : flags) {
							if (f.second == 0){
								is_full_set = false;
								break;
							}
						}
							
						if (is_full_set)
						{
							int curr = 0;
							for (const auto &f : flags) {
								curr += f.second;
							}
							
							if (m_value > curr)
							{
								m_idx = slow;
								m_size = fast - slow;
								m_value = curr;
							}
                            
							flags[vacations[slow].first] -= vacations[slow].second;
							slow++;
						}
						else
						{
                            if (fast >= vacations.size()) {
                                return; // skip no full sets left
                            }
							flags[vacations[fast].first] += vacations[fast].second;
							fast++;
						}
                    } while (true);
				}

                int min_idx() const { return m_idx; }
                int size() const { return m_size; }
                int value() const { return m_value; }

			private:
				int m_idx;
				int m_size;
				int m_value;
		};
	}
}