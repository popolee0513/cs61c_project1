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
  flightSys_t *system = malloc(sizeof(flightSys_t));
  if (system == NULL) {
    allocation_failed();
  }
  system->capacity = 10;
  system->airports = malloc(sizeof(airport_t *)*system->capacity);
  system->numAirports = 0;
  return system;
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
  flight_t *flight = malloc(sizeof(flight_t));
  //flight->dest = malloc(sizeof(struct airport));
  //flight->dest->name = malloc(strlen(destination->name) + 1);
  //strcpy(flight->dest->name,destination->name);
  flight->dest = destination;
  flight->depart_t =  malloc(sizeof(timeHM_t));
  flight->depart_t->hours = departure->hours;
  flight->depart_t->minutes = departure->minutes;
  flight->arrival_t =  malloc(sizeof(timeHM_t));
  flight->arrival_t->hours = arrival->hours;
  flight->arrival_t->minutes = arrival->minutes;
  flight->cost = cost;
  return flight;
}

/*
 *  Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) {
  for (int i = 0; i < system->numAirports; i++) {
      airport_t *airport = system->airports[i];
      for (int j = 0; j < airport->numflights; j++){
          flight_t *flight = airport->flights[j];
          deleteFlight(flight);
          }
    free(airport->name);
    free(airport->flights);
    free(airport);
  }
  free(system->airports);
  free(system);
}

/*
 *  Frees all memory allocated for a single flight. You may or may not decide
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight) {
  // Replace this line with your code
  free(flight->depart_t);
  free(flight->arrival_t);
  free(flight);
}


/*
 *  Adds a airport with the given name to the system. You must copy the string and store it.
 *  Do not store `name` (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* system, char* name) {
  // Replace this line with your code
  airport_t *airport = malloc(sizeof(airport_t));
  airport->name = malloc(strlen(name)+1);
  strcpy(airport->name,name);
  airport->capacity = 10;
  airport->flights = malloc(sizeof(flight_t *)*airport->capacity);
  airport->numflights = 0;


  if (system->numAirports + 1 >= system->capacity) {
      system->airports = realloc(system->airports, sizeof(airport_t *) * system->capacity*2);
      system->capacity = system->capacity*2;
   }
  system->airports[system->numAirports] = airport;
  system->numAirports += 1;

}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) {
  for (int i = 0; i < system->numAirports; i++) {
    airport_t *airport = system->airports[i];
    if (strcmp(airport->name, name) == 0) {
      return airport;
    }
  }
  return NULL;
}

/*
 *  Print each airport name in the order they were added through addAirport, one on each line.
 *  Make sure to end with a new line. You should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) {
  if (system == NULL || system->airports == NULL) {
    return;
  }

  for (int i = 0; i < system->numAirports; i++) {
    airport_t *airport = system->airports[i];
    if (airport && airport->name) {
      printf("%s\n", airport->name);
    }
  }
}


/*
 *  Adds a flight to source's schedule, stating a flight will leave to destination at departure time and arrive at arrival time.
 */
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code

  flight_t* flight = createFlight(destination, departure, arrival, cost);

  if (source->numflights + 1 >= source->capacity) {
           source->flights = realloc(source->flights, sizeof(flight_t *) * source->capacity*2);
           source->capacity = source->capacity*2;
  }
  source->flights[source->numflights] = flight;
  source->numflights += 1;

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
  flight_t *flight = airport->flights;
  if (flight == NULL) {
    return ;
  }
  printf("%s\n",airport->name);
  for (int i = 0; i < airport->numflights; i++){
    flight_t *flight = airport->flights[i];
    printf("%s ",flight->dest->name);
    printTime(flight->depart_t);
    printf(" ");
    printTime(flight->arrival_t);
    printf(" ");
    printf("$%d\n",flight->cost);
  }
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
  flight_t *bestflight = NULL;
  for (int i = 0; i < source->numflights; i++){
    flight_t *flight = source->flights[i];
   if (
    strcmp(destination->name, flight->dest->name) == 0 &&
    (isAfter(flight->depart_t, now) || isEqual(flight->depart_t, now))
    ){
        if (bestflight == NULL) {
          bestflight = flight;
        } else {
          if (isEqual(flight->arrival_t ,bestflight->arrival_t)) {
             if (flight->cost < bestflight-> cost) {
                 bestflight = flight;
             }
          } else {
             if (isAfter(bestflight->arrival_t,flight->arrival_t)){
                 bestflight = flight;
             }
          }
        }
    }

  }
  if (bestflight == NULL) {
    return false;
  }
    *cost = bestflight->cost;
    departure->hours = bestflight->depart_t->hours;
    departure->minutes = bestflight->depart_t->minutes;
    arrival->hours = bestflight->arrival_t->hours;
    arrival->minutes = bestflight->arrival_t->minutes;

    return true;
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
    if (flight_list == NULL || airport_name_list == NULL || size <= 0) {
        return -1;
    }

    int cost = 0;

    for (int i = 0; i < size; i++) {
        // 基本 NULL 檢查
        if (flight_list[i] == NULL || airport_name_list[i] == NULL) {
            return -1;
        }

        flight_t* flight = flight_list[i];
        if (flight->dest == NULL || flight->dest->name == NULL ||
            flight->arrival_t == NULL || flight->depart_t == NULL) {
            return -1;
        }

        // 檢查目的地名稱是否一致
        if (strcmp(airport_name_list[i], flight->dest->name) != 0) {
            return -1;
        }

        // 檢查時間順序（從第二個 flight 開始）
        if (i > 0) {
            flight_t* prev_flight = flight_list[i - 1];
            if (prev_flight == NULL || prev_flight->arrival_t == NULL) {
                return -1;
            }
            if (!isAfter(flight->depart_t, prev_flight->arrival_t) &&
                !isEqual(flight->depart_t, prev_flight->arrival_t)) {
                return -1;
            }
        }
        cost += flight->cost;
    }
    return cost;
}


