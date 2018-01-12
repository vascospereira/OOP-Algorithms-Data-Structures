#include "Park.h"
#include <vector>

using namespace std;

ParkingLot::ParkingLot(unsigned int cap, unsigned int n_max_clientes): capacity(cap), num_max_clients(n_max_clientes)
{
	num_clients = 0;
	places = cap;
}

unsigned int ParkingLot::num_places() const
{
	return capacity;
}

unsigned int ParkingLot::max_clients() const
{
	return num_max_clients;
}

int ParkingLot::client_position(const string & name) const
{
	for(unsigned i = 0; i < clients.size(); i++)
		if(clients.at(i).name == name) return i;
	return -1;
}

bool ParkingLot::new_client(const string &name)
{
	if(num_clients == num_max_clients) return false;
	if(client_position(name) != -1) return false;
	InfoCard client;
	client = { name, false };
	clients.push_back(client);
	num_clients++;
	return true;
}

bool ParkingLot::enter(const string &name)
{
	if(places == 0) return false;
	int pos = client_position(name);
	if(pos == -1) return false;
	if(clients.at(pos).present == true) return false;
	clients.at(pos).present = true;
	places--;
	return true;
}

bool ParkingLot::exit(const string & name)
{
	int pos = client_position(name);
	if(pos == -1) return false;
	if(!clients.at(pos).present) return false;
	clients.at(pos).present = false;
	places++;
	return true;
}

bool ParkingLot::remove_client(const string & name)
{
	for(vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++) {
		if(it->name == name){
			if(!it->present){
				clients.erase(it);
				num_clients--;
				return true;
			}
			return false;
		}
	}
	return false;
}

unsigned int ParkingLot::no_free_places() const
{
	return capacity - places;
}

unsigned int ParkingLot::actual_num_clients() const
{
	return num_clients;
}
