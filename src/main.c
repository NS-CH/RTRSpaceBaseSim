// PREPROCESSOR INCLUDES

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// PREPROCESSOR DEFINES OF SIMULATION INDEPENDENT VARIABLES

#define INITIAL_CREW_MEMBER_NUM 6
#define INITIAL_FOOD_CALORIES 3586500
#define INITIAL_WATER_GALLON 180
#define INITIAL_OXYGEN 700 // TODO: MAKE OXYGEN COUNT A NUMBER BASED ON ACTUAL FACT
#define INITIAL_ENERGY_SUPPLY 300
#define FOOD_CALORIES_CONSUMPTION_PERSON 3250
#define WATER_GALLON_CONSUMPTION_PERSON 12
#define SURVIVAL_WITHOUT_LIFE_NEEDS_COUNT 5

// MAIN CODE
//
// Struct for Crewmember 

// Enum State for Crewmember

typedef enum Crew_State { Active = 0, Deactive = 1, Dead = 2 } Crew_State;

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
  Crewmember* crew[INITIAL_CREW_MEMBER_NUM];
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
    station->crew[i]->health = 100;
    station->crew[i]->energy = 100;
    station->crew[i]->wellbeing = 100;
    station->crew[i]->day_without_life_supply = 0;
    station->crew[i]->state = Active;
    station->crew[i]->is_sick = false;
  }
}
// Function to get Crew Count

int get_active_crew_count(Space_Station* station)
{
  int active_crew_count;
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
  int total_crew_count;
  for (int i = 0; i < INITIAL_CREW_MEMBER_NUM; i++)
  {
    if (station->crew[i]->state != Dead)
    {
      total_crew_count++;
    }
  }

  return total_crew_count;
}

// Function to simulation one day / iteration of simulation

void simulate_iteration(Space_Station* station)
{
  // Change Stations supply counts
  station->food_supply -= (FOOD_CALORIES_CONSUMPTION_PERSON * get_total_crew_count(station));
  station->water_supply -= (WATER_GALLON_CONSUMPTION_PERSON * get_total_crew_count(station));
  station->oxygen_supply -= 10; // TODO: MAKE OXYGEN SUPPLY VARIABLE ON ACTUAL AMOUNT
  station->energy_supply -= (INITIAL_ENERGY_SUPPLY * 0.1); // Subtracts energy count by 10% of inital energy count;
  
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
  Space_Station space_station;
  initialise_space_station(&space_station);
  simulate_iteration(&space_station);

  return 0;
}
