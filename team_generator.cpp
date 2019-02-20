#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace {
	const std::string PROJECT_NAME = "name_selector";
	const unsigned int TEAM_SIZE = 5;
	const bool DEBUG = false;
}

struct Team {
	std::string members[5];
	int currentMembers = 0;
};


void assignTeams(std::vector<std::string> players);;
int getRandom(int min, int max);

int main(int argc, char **argv) {

	std::string name;
	std::vector<std::string> players;
	Team *teams;

	//Check that a file was provided
	if(argc != 2) {
		fprintf(stderr, "Usage:\n./%s [file]\n", PROJECT_NAME.c_str());
		return -1;
	}

	//Seed the random number
	srand(static_cast<unsigned int>(time(nullptr)));

	//Get the file name, make sure we can open it
	std::string filename = argv[1];
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
	assignTeams(players);

}

//Assign all players
void assignTeams(std::vector<std::string> players) {

	unsigned int numTeams = players.size() / TEAM_SIZE;
	unsigned int peopleLeftOver = players.size() % TEAM_SIZE;
	unsigned int teamNumber = 0;

	if(DEBUG) {
		printf("Number of teams = %d - Left over = %d\n", numTeams, peopleLeftOver);
	}

	if(peopleLeftOver) {
		numTeams++;
		if(DEBUG) {
			printf("Incrementing numbers of teams to %d\n", numTeams);
		}
	}

	Team teams[numTeams];
	std::vector<std::string>::iterator it;

	for(it = players.begin(); it != players.end(); it++) {

		//Keep getting a random number until the team isn't full
		while(true) {
			teamNumber = getRandom(0, numTeams);
			if(teams[teamNumber].currentMembers < TEAM_SIZE) {
				Team *team = &teams[teamNumber];
				team->members[team->currentMembers] = *it;
				team->currentMembers++;
				break;
			}
			if(DEBUG) {
				printf("Picking another random number...\n");
			}
		}
		
	}

	for(unsigned int i = 0; i < numTeams; i++) {
		Team *team = &teams[i];
		printf("Team %d\n", i);
		for(unsigned int j = 0; j < team->currentMembers; j++) {
			printf("	Member: %s\n", team->members[j].c_str());
		}

	}
}


//Return a random number from range min to max
int getRandom(int min, int max) {
	return min+rand()%(max - min + 1);
}
