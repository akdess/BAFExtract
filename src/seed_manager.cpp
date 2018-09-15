#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "seed_manager.h"

#include "utils.h"

bool _DUMP_SEED_MGR_MESSAGES_ = false;

vector<int>* t_seed_manager::seeds = NULL;
int t_seed_manager::i_next_seed = 0;

t_seed_manager::t_seed_manager()
{
	if(t_seed_manager::seeds == NULL)
	{
		t_seed_manager::seeds = new vector<int>();
	}
}

t_seed_manager::t_seed_manager(char* seeds_fp)
{
	if(t_seed_manager::seeds == NULL)
	{
		t_seed_manager::seeds = new vector<int>();
	}

	FILE* f_seeds = open_f(seeds_fp, "r");
	if(f_seeds == NULL)
	{
		printf("Could not find seed file %s\n", seeds_fp);
		exit(0);
	}

	int cur_seed;
	while(fscanf(f_seeds, "%d", &cur_seed) == 1)
	{
		t_seed_manager::seeds->push_back(cur_seed); // Initing seed.
		printf("%d\n", t_seed_manager::seeds->back());
		
	}
	fclose(f_seeds);

	printf("------------------------\n");
	for(int i_seed = 0; i_seed < (int)t_seed_manager::seeds->size(); i_seed++)
	{
		printf("%d\n", t_seed_manager::seeds->at(i_seed));
	}

if(_DUMP_SEED_MGR_MESSAGES_)
	printf("Loaded %ld seeds.\n", t_seed_manager::seeds->size());
	//getc(stdin);
}

int t_seed_manager::seed_me()
{
	if(t_seed_manager::seeds == NULL)
	{
		t_seed_manager::seeds = new vector<int>();
	}

	int seed_candidate = 0;
	if(t_seed_manager::i_next_seed < (int)t_seed_manager::seeds->size())
	{
		seed_candidate = t_seed_manager::seeds->at(t_seed_manager::i_next_seed);
		t_seed_manager::i_next_seed++;

if(_DUMP_SEED_MGR_MESSAGES_)
		printf("New seed: %d\n", seed_candidate);
	}
	else
	{
		//printf("Generating newer seed!\n");
		//getc(stdin);

		seed_candidate = (int)time(NULL);

		// Compare candidate with all the seeds.
		bool has_it = false;
		do
		{			
			has_it = false;
			for(int i_seed = 0; i_seed < (int)t_seed_manager::seeds->size(); i_seed++)
			{
				if(seed_candidate == t_seed_manager::seeds->at(i_seed))
				{
					has_it = true;
				}
			}

			if(has_it)
			{
if(_DUMP_SEED_MGR_MESSAGES_)
				printf("Seed overlap, regenerating.\n");
				//getc(stdin);
				seed_candidate++;
			}
		}
		while(has_it);

if(_DUMP_SEED_MGR_MESSAGES_)
		printf("New seed: %d\n", seed_candidate);
		t_seed_manager::seeds->push_back(seed_candidate);
		t_seed_manager::i_next_seed++;
	}

	return(seed_candidate);
}

// Dump all the seeds.
void t_seed_manager::dump_seeds()
{
	if(t_seed_manager::seeds != NULL)
	{
		FILE* f_seeds = open_f("seeds.txt", "w");
		for(int i_seed = 0; i_seed < (int)t_seed_manager::seeds->size(); i_seed++)
		{
			fprintf(f_seeds, "%d\n", t_seed_manager::seeds->at(i_seed));
		}
		fclose(f_seeds);
	}
}

