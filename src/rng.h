#ifndef _PPF_RNG_
#define _PPF_RNG_

#include <vector>

using namespace std;

class t_rng
{
public:
	t_rng(int _prn_gen_seed);
	~t_rng();

	double random_double_ran3();
	double random_gaussian_double_ran3();
	vector<int>* permute_indices(int i_max, int i_to_exclude_from_first_position);
	vector<int>* fast_permute_indices(int i_min, int i_max);

public:
	int prn_gen_seed;
	int inext,inextp;
	long ma[56]; // The value 56 (range ma[1..55]) is special and should 
	int iff; // not be modifed; see Knuth.
	double ran3(long* idum);
};

#endif // _PPF_RNG_


