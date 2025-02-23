#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Facility
{
  char name[50];
  double food_production;
  double water_production;
  double energy_production;
  double power_consumption;
  double oxygen_production;
  bool is_operational;
} Facility;

typedef struct Space_Station_Facilities
{
  char name[50];
  int facility_count;
  Facility* facilities[10];
}

void initialise_facility(Facility* facility, const char* NAME, double power_prod, double power_cons, double oxygen_prod, double food_prod, double water_prod, bool operational)
{
  facility->food_production = food_prod;
  facility->water_production = water_prod;
  facility->energy_production = power_prod;
  facility->power_consumption = power_cons;
  facility->oxygen_production = oxygen_prod;
  facility->is_operational = operational;
}

void initalise_station_facilities(Space_Station_Facilities* station_facilities)
{
  printf("%s", station_facilities->name);
  station->facility_count = 0;

  Facility* habitat = (Facility*)malloc(sizeof(Facility));
  initialise_facility(habitat, "Habitat", 0.0, 20.0, 0.0, 0.0, 0.0, true);
  station_facilities->facilities[station_facilities->facility_count++] = habitat;

  Facility* greenhouse = (Facility*)malloc(sizeof(Facility));
  initialise_facility(greenhouse, "Greenhouse", 0.0, 5.0, 3.0, 3250.0, 0.0, true);
  station_facilities->facilities[station_facilities->facility_count++] = greenhouse;
}
