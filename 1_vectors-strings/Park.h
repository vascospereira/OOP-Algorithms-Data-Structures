#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCard {
public:
	string name;
	bool present;
};

class ParkingLot {
	unsigned int places;
	const unsigned int capacity;
	vector<InfoCard> clients;
	unsigned int num_clients;
	const unsigned int num_max_clients;
public:
	ParkingLot(unsigned int cap, unsigned int n_max_clients);
	bool new_client(const string & name);
	bool remove_client(const string & name);
	bool enter(const string & name);
	bool exit(const string & name);
	int client_position(const string & name) const;
	unsigned int num_places() const;
	unsigned int max_clients() const;
	unsigned int no_free_places() const;
	unsigned int actual_num_clients() const;
};
