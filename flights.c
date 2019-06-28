/*
 * CS61C Summer 2019
 * Name:
 * Login:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "flight_structs.h"
#include "timeHM.h"

/*
 *  This should be called if memory allocation failed.
 */
static void allocation_failed(void) {
  fprintf(stderr, "Out of memory.\n");
  exit(EXIT_FAILURE);
}


/*
 *  Creates and initializes a flight system, which stores the flight schedules of several airports.
 *  Returns a pointer to the system created.
 */
flightSys_t* createSystem(void) {
  // Replace this line with your code
  return NULL;
}


/*
 *   Given a destination airport, departure and arrival times, and a cost, return a pointer to new flight_t.
 *
 *   Note that this pointer must be available to use even after this function returns.
 *   (What does this mean in terms of how this pointer should be instantiated?)
 *   Additionally you CANNOT assume that the `departure` and `arrival` pointers will persist after this function completes.
 *   (What does this mean about copying dep and arr?)
 */

flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code
  return NULL;
}

/*
 *  Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) {
  // Replace this line with your code
}

/*
 *  Frees all memory allocated for a single flight. You may or may not decide
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight) {
  // Replace this line with your code
}


/*
 *  Adds a airport with the given name to the system. You must copy the string and store it.
 *  Do not store `name` (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* system, char* name) {
  // Replace this line with your code
}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) {
  // Replace this line with your code
  return NULL;
}


/*
 *  Print each airport name in the order they were added through addAirport, one on each line.
 *  Make sure to end with a new line. You should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) {
  // Replace this line with your code
}


/*
 *  Adds a flight to source's schedule, stating a flight will leave to destination at departure time and arrive at arrival time.
 */
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code
}


/*
 *  Prints the schedule of flights of the given airport.
 *
 *  Prints the airport name on the first line, then prints a schedule entry on each
 *  line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".
 *
 *  You should use `printTime()` (look in `timeHM.h`) to print times, and the order should be the same as
 *  the order they were added in through addFlight. Make sure to end with a new line.
 *  You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* airport) {
  // Replace this line with your code
}


/*
 *   Given a source and destination airport, and the time now, finds the next flight to take based on the following rules:
 *   1) Finds the earliest arriving flight from source to destination that departs after now.
 *   2) If there are multiple earliest flights, take the one that costs the least.
 *
 *   If a flight is found, you should store the flight's departure time, arrival time, and cost in the `departure`, `arrival`,
 *   and `cost` params and return true. Otherwise, return false.
 *
 *   Please use the functions `isAfter()` and `isEqual()` from `timeHM.h` when comparing two timeHM_t objects and compare
 *   the airport names to compare airports, not the pointers.
 */
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival,
                   int* cost) {
  // Replace this line with your code
  return false;
}

/*
 *  Given a list of flight_t pointers (`flight_list`) and a list of destination airport names (`airport_name_list`),
 *  first confirm that it is indeed possible to take these sequences of flights, (i.e. be sure that the i+1th flight departs
 *  after or at the same time as the ith flight arrives) (HINT: use the `isAfter()` and `isEqual()` functions).
 *  Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t structs.
 *
 *  `size` tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors.
 *  As one example, if you encounter NULL's for any values that you might expect to be non-NULL return -1, but test for other possible errors too.
 *
 *  Return from this function the total cost of taking these sequence of flights.
 *  If it is impossible to take these sequence of flights,
 *  if the list of destination airport names doesn't match the actual destination airport names provided in the flight_t struct's,
 *  or if you run into any errors mentioned previously or any other errors, return -1.
 */
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int size) {
  // Replace this line with your code
  return -1;
}

