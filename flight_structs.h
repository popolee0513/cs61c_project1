/*
 * CS61C Summer 2019
 * Name:
 * Login:
 */

#ifndef FLIGHT_STRUCTS_H
#define FLIGHT_STRUCTS_H

#include "timeHM.h"

typedef struct flightSys flightSys_t;
typedef struct airport airport_t;
typedef struct flight flight_t;

struct flightSys {
  // Place the members you think are necessary for the flightSys struct here.
  struct airport **airports;
  int numAirports;           // 目前有幾個 airport
  int capacity;              // 陣列容量

};

struct airport {
  // Place the members you think are necessary for the airport struct here.
  char *name;
  struct flight **flights;
  int numflights;               // 目前有幾個 flight
  int capacity;              // 陣列容量
};

struct flight {
  // Place the members you think are necessary for the flight struct here.
  struct airport *dest;
  timeHM_t *depart_t;
  timeHM_t *arrival_t;
  int cost;
};

#endif

