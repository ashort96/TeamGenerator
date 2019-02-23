#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Team
{
	std::vector<std::string> members;
	int currentMembers = 0;
};


//Return a random number from range min to max
int getRandom(int min, int max)
{
	return min + rand() % (max - min + 1);
}


//Assign all players
void assignTeams(std::vector<std::string> players, unsigned int teamSize)
{
	unsigned int numTeams = players.size() / teamSize;
	unsigned int peopleLeftOver = players.size() % teamSize;
	unsigned int teamNumber = 0;

	if(peopleLeftOver) {
		numTeams++;
	}

	Team teams[numTeams];
	std::vector<std::string>::iterator it;

	for(it = players.begin(); it != players.end(); it++) {
		//Keep getting a random number until the team isn't full
		while(true) {
			teamNumber = getRandom(0, numTeams);

			if(teams[teamNumber].currentMembers < teamSize) {
				Team *team = &teams[teamNumber];
				team->members.push_back(*it);
				team->currentMembers++;
				break;
			}
		}
	}

	//Print off the teams
	for(unsigned int i = 0; i < numTeams; i++) {
		Team *team = &teams[i];
		printf("Team %d\n", i+1);
		for(unsigned int j = 0; j < team->currentMembers; j++) {
			printf("	Member: %s\n", team->members[j].c_str());
		}
	}
}


int main(int argc, char **argv)
{
	std::string name;
	std::vector<std::string> players;
	Team *teams;

	//Check that a file was provided
	if(argc != 3) {
		fprintf(stderr, "Usage:\n%s [file] [team size]\n", argv[0]);
		return -1;
	}

	//Seed the random number
	srand(static_cast<unsigned int>(time(nullptr)));

	//Get the file name, make sure we can open it
	std::string filename = argv[1];
	unsigned int teamSize = atoi(argv[2]);
	std::ifstream file;
	file.open(filename);

	if(!file) {
		fprintf(stderr, "Unable to open %s\n", filename.c_str());
		return -1;
	}

	while(getline(file, name)) {
		players.push_back(name);
	}

	//Close the file, we're done with it
	file.close();
	
	//Assign the teams
	assignTeams(players, teamSize);

	return 0;
}
