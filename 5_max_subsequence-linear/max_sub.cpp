// max subsequence - linear
#include <iostream>
#include <vector>
using namespace std;

template <class Comparable>
Comparable max_sub_sum(const vector<Comparable> &v) {
	Comparable this_sum = 0, max_sum = 0;
	for(unsigned i = 0; i < v.size(); i++){
		this_sum += v.at(i);
		if(this_sum > max_sum)
			max_sum = this_sum;
		else if(this_sum < 0)
			this_sum = 0;
	}
	return max_sum;
}

int main()
{
	vector<int> v1 = {-2, 11, -14, 13, -4, 6};
	vector<float> v2 = {-2.2, 11.3, -4.8, 13.1, -4.7, 2.0};
	cout << max_sub_sum(v1) << endl;
	cout << max_sub_sum(v2) << endl;
}
