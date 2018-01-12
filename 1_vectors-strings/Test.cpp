#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
#include "Park.h"

 void test_1a_OpenPark() {

	ParkingLot p1(4, 6);
	// Tests if park was open with the capacity suggested
	ASSERT_EQUAL(4, p1.num_places());
	// Tests if park was open with the maximum number of clients suggested
	ASSERT_EQUAL(6, p1.max_clients());

}

// Este teste serve para avaliar a correcta implementação da questão b) da ficha prática 01
void test_1b_AddClient() {
	ParkingLot p1(3, 5);
	// Test if we can add a new client
	ASSERT_EQUAL(true, p1.new_client("Joao"));
	p1.new_client("Antonio");
	p1.new_client("Rui");
	p1.new_client("Maria");
	p1.new_client("Clara");
	// Tests if refuses to enter new client when num_max_clients is full
	ASSERT_EQUAL(false, p1.new_client("Paula"));
	// Tests is return the client correct position
	ASSERT_EQUAL(1, p1.client_position("Antonio"));
	// Tests if return -1 when client does not exist
	ASSERT_EQUAL(-1, p1.client_position("Joana"));
}

void test_1c_EnterPark() {
	ParkingLot p1(3, 5);
	p1.new_client("Joao");
	p1.new_client("Maria");
	p1.new_client("Antonio");
	p1.new_client("Rui");
	// Tests if allows an existent client to enter in the park
	ASSERT_EQUAL(true, p1.enter("Maria"));
	// Test if does not allow an inexistent client to enter in the park
	ASSERT_EQUAL(false, p1.enter("Paula"));
	// Test if does not allow a client to enter if already is in the park
	ASSERT_EQUAL(false, p1.enter("Maria"));
	p1.enter("Joao");
	p1.enter("Antonio");
	// Test if cannot enter when capacity is full
	ASSERT_EQUAL(false, p1.enter("Rui"));
}

void test_1d_RemoveClient() {
	ParkingLot p1(3, 5);
	p1.new_client("Joao");
	p1.new_client("Maria");
	p1.new_client("Antonio");
	p1.enter("Maria");
	// Tests if can't remove client inside the park
	ASSERT_EQUAL(false, p1.remove_client("Maria"));
	// Tests if can remove client outside the park
	ASSERT_EQUAL(true, p1.remove_client("Antonio"));
	// Tests if can't remove client that does not exist
	ASSERT_EQUAL(false, p1.remove_client("Ana"));
}

void test_1e_ExitPark() {
	ParkingLot p1(3, 5);
	p1.new_client("Joao");
	p1.new_client("Maria");
	p1.new_client("Rui");
	p1.enter("Maria");
	p1.enter("Joao");
	p1.enter("Rui");
	// Tests if client parked exits
	ASSERT_EQUAL(true, p1.exit("Maria"));
	// Tests if can't remove a parked client.
	ASSERT_EQUAL(false, p1.exit("Maria"));
	// Tests if can't remove client that does not exist
	ASSERT_EQUAL(false, p1.exit("Antonio"));
}

void test_1f_ParkCapacityPlaces() {
	ParkingLot p1(3, 5);
	p1.new_client("Joao");
	p1.new_client("Maria");
	p1.new_client("Antonio");
	p1.enter("Maria");
	p1.enter("Antonio");
	// Tests if capacity is correct
	ASSERT_EQUAL(3, p1.num_places());
	// Tests if the number of cars in the park is correct
	ASSERT_EQUAL(2, p1.no_free_places());
	// Tests if the number of clients registered in the park is corrected
	ASSERT_EQUAL(3, p1.actual_num_clients());
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1a_OpenPark));
	s.push_back(CUTE(test_1b_AddClient));
	s.push_back(CUTE(test_1c_EnterPark));
	s.push_back(CUTE(test_1d_RemoveClient));
	s.push_back(CUTE(test_1e_ExitPark));
	s.push_back(CUTE(test_1f_ParkCapacityPlaces));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "Algorithms and Data Structures");
}

int main(){
    runSuite();
}



