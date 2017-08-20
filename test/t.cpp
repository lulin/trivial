#include <vector>
using namespace std;

class Solution {
	public:
		vector<int> twoSum(vector<int>& nums, int target) {
			vector<int> aux = nums;
			sort<vector<int>::iterator>(aux.begin(), aux.end());

			auto it = aux.begin();
			for(; it != aux.end(); it++) {
				if (*it >= target/2) {
					break;
				}
			}
			auto it_small = it;
			auto it_big = it + 2;
			for (;*it_small + *it_big != target;) {
				auto sum = *it_small + *it_big;
				if (sum > target) {
					it_small--;
					continue;
				}
				if (sum < target) {
					it_big++;
					continue;
				}
			}

			vector<int> ret;
			for (int i = 0; i < nums.size(); i++) {
				if (nums[i] == *it_small) {
					ret.push_back(i);
					break;
				}
			}
			for (int i = 0; i < nums.size(); i++) {
				if (nums[i] == *it_big) {
					ret.push_back(i);
					break;
				}
			}

			return ret;
		}
};
