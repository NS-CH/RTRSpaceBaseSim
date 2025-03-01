// PREPROCESSOR INCLUDES

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "includes/station_facilities.c"
#include "includes/rand_events.c"
#include "includes/manage_station.c"

// PREPROCESSOR DEFINES OF SIMULATION INDEPENDENT VARIABLES

#define INITIAL_CREW_MEMBER_NUM 6
#define INITIAL_FOOD_CALORIES 3586500
#define INITIAL_WATER_GALLON 180
#define INITIAL_OXYGEN 700 // TODO: MAKE OXYGEN COUNT A NUMBER BASED ON ACTUAL FACT
#define INITIAL_ENERGY_SUPPLY 300
#define FOOD_CALORIES_CONSUMPTION_PERSON 3250
#define WATER_GALLON_CONSUMPTION_PERSON 0.55
#define SURVIVAL_WITHOUT_LIFE_NEEDS_COUNT 5

#define DAYS_SUPPLY_LEFT_BEFORE_END 10

// MAIN CODE
//
// Struct for Crewmember 

// Enum State for Crewmember

typedef enum Crew_State { Active = 0, Deactive = 1, Dead = 2 } Crew_State;
typedef enum Station_State { Good = 0, Rationing = 1, Failed = 2 } Station_State;

typedef struct Crewmember 
{
  double health;
  double energy;
  double wellbeing;
  int day_without_life_supply;
  Crew_State state;
  bool is_sick;
} Crewmember;

// Struct for Space_Station

typedef struct Space_Station
{
  double food_supply;
  double water_supply;
  double oxygen_supply;
  double energy_supply;
  Station_State state;
  Crewmember* crew[INITIAL_CREW_MEMBER_NUM];
  Space_Station_Facilities station_facilities[10];
} Space_Station;

// Initalise Members in the Space Station

void initialise_space_station(Space_Station* station)
{
  // Initialise variables for station
  station->food_supply = INITIAL_FOOD_CALORIES;
  station->water_supply = INITIAL_WATER_GALLON;
  station->oxygen_supply = INITIAL_OXYGEN;
  station->energy_supply = INITIAL_ENERGY_SUPPLY;

  // Initialise variables for the crewmembers of station
  for (int i = 0; i < INITIAL_CREW_MEMBER_NUM; i++)
  {
    station->crew[i] = (Crewmember*)malloc(sizeof(Crewmember));
    station->crew[i]->health = 100;
    station->crew[i]->energy = 100;
    station->crew[i]->wellbeing = 100;
    station->crew[i]->day_without_life_supply = 0;
    station->crew[i]->state = 0; // ACTIVE by Default
    station->crew[i]->is_sick = false;
  }

  initialise_station_facilities(station->station_facilities);
}

// Function to get Crew Count

int get_active_crew_count(Space_Station* station)
{
  int active_crew_count = 0;
  for (int i = 0; i < INITIAL_CREW_MEMBER_NUM; i++)
  {
    if (station->crew[i]->state == Active)
    {
      active_crew_count++;
    }
  }

  return active_crew_count;
}

int get_total_crew_count(Space_Station* station)
{
  int total_crew_count = 0;
  for (int i = 0; i < INITIAL_CREW_MEMBER_NUM; i++)
  {
    if (station->crew[i]->state != Dead)
    {
      total_crew_count++;
    }
  }

  return total_crew_count;
}

// MID ITERATION TASKS AND EVENTS FUNCTIONS

void crew_eat(Space_Station* station)
{
  int total_food_used = 0;

  for (int i = 0; i < get_total_crew_count(station); i++)
  {
    total_food_used += FOOD_CALORIES_CONSUMPTION_PERSON;
  }

  if (station->food_supply < (total_food_used * DAYS_SUPPLY_LEFT_BEFORE_END))
  {
    station->state = 1; // Sets state of the station to be Rationing
  }

  if (station->state == 1)
  {
    total_food_used /= 2; // If the state is rationing, half the amount of food consumption
  }

  station->food_supply -= total_food_used;
}

void crew_drink(Space_Station* station)
{
  int total_water_used = 0;

  for (int i = 0; i < get_total_crew_count(station); i++)
  {
    total_water_used += WATER_GALLON_CONSUMPTION_PERSON;
  }

  if (station->water_supply < (total_water_used * DAYS_SUPPLY_LEFT_BEFORE_END))
  {
    station->state = 1;
  }

  if (station->state = 1)
  {
    total_water_used *= 0.8;
  }

  station->water_supply -= total_water_used;
}

// Facility Manager

void facility_manager(Space_Station* station)
{
  double total_energy_use = get_total_energy_use(station->station_facilities);
  double total_energy_production = get_total_energy_produce(station->station_facilities);
  double total_food_production = get_total_food_produce(station->station_facilities);
  double total_water_production = get_total_water_produce(station->station_facilities);
  double total_oxygen_production = get_total_oxygen_produce(station->station_facilities);

  station->energy_supply -= total_energy_use;
  station->energy_supply += total_energy_production;
  station->food_supply += total_food_production;
  station->water_supply += total_water_production;
  station->oxygen_supply += total_oxygen_production;
}

// Function to simulation one day / iteration of simulation

void simulate_iteration(Space_Station* station)
{
  // Change Stations supply counts

  station->oxygen_supply -= 10; // TODO: MAKE OXYGEN SUPPLY VARIABLE ON ACTUAL AMOUNT
  
  // Updates Crewmembers variables

  for (int i = 0; i < get_total_crew_count(station); i++)
  {
    if (station->crew[i]->state == Active)
    {
      station->crew[i]->energy -= 8;
      station->crew[i]->wellbeing -= 5;
    }
    else if (station->crew[i]->state == Deactive)
    {
      station->crew[i]->energy -= 2;
      station->crew[i]->wellbeing -= 7;
    }
  }

  // Create Mid-Iteration tasks / Events that will affect the simulate_iteration

  // Call eating Function
  
  crew_eat(station);
  crew_drink(station);

  // Call Facility Manager
  
  facility_manager(station);

  // Prints Data to the Console

  printf("Station Supplies:\n");
  printf("Food (CALORIES): %lf, Water (GALLONS): %lf, Oxygen: %lf, Energy (JOULES): %lf\n",
         station->food_supply,
         station->water_supply,
         station->oxygen_supply,
         station->energy_supply);

  printf("Crewmember attributes:\n");
  printf("----------------------\n");
  
  for (int i = 0; i < get_total_crew_count(station); i++)
  {
    printf("Crewmember %i:\n", i);
    printf("Health: %lf, Energy: %lf, Wellbeing: %lf, Days Without Life-Needing Supplies: %i, State: %i, Is Sick: %i\n",
          station->crew[i]->health,
          station->crew[i]->energy,
          station->crew[i]->wellbeing,
          station->crew[i]->day_without_life_supply),
          station->crew[i]->state,
          station->crew[i]->is_sick;
    printf("-_-_-_-_-_-_-_-_-_-_-\n");
  }
}

int main()
{
  // Allows for random events
  srand(time(NULL));

  // Initialises space station
  Space_Station space_station;
  initialise_space_station(&space_station);

  // Simulates iterations for sets number of times
  for (int i = 0; i < 5; i++)
  {
    simulate_iteration(&space_station);
    printf("----------");
  }

  // Frees the allocates memory for the space station crew
  for (int i = 0; i < INITIAL_CREW_MEMBER_NUM; i++)
  {
    free(space_station.crew[i]);
  }

  return 0;
}
