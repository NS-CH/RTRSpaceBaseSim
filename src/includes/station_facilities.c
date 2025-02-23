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
} Space_Station_Facilities;

void initialise_facility(Facility* facility, const char* NAME, double power_prod, double power_cons, double oxygen_prod, double food_prod, double water_prod, bool operational)
{
  facility->food_production = food_prod;
  facility->water_production = water_prod;
  facility->energy_production = power_prod;
  facility->power_consumption = power_cons;
  facility->oxygen_production = oxygen_prod;
  facility->is_operational = operational;
}

void initialise_station_facilities(Space_Station_Facilities* station_facilities)
{
  printf("%s", station_facilities->name);
  station_facilities->facility_count = 0;

  Facility* habitat = (Facility*)malloc(sizeof(Facility));
  initialise_facility(habitat, "Habitat", 0.0, 20.0, 0.0, 0.0, 0.0, true);
  station_facilities->facilities[station_facilities->facility_count++] = habitat;

  Facility* greenhouse = (Facility*)malloc(sizeof(Facility));
  initialise_facility(greenhouse, "Greenhouse", 0.0, 5.0, 3.0, 3250.0, 0.0, true);
  station_facilities->facilities[station_facilities->facility_count++] = greenhouse;

  Facility* water_recycler = (Facility*)malloc(sizeof(Facility));
  initialise_facility(water_recycler, "Water Recycler", 0.0, 3.0, 0.0, 0.0, 1.8, true);
  station_facilities->facilities[station_facilities->facility_count++] = water_recycler;

  Facility* solar_panels = (Facility*)malloc(sizeof(Facility));
  initialise_facility(solar_panels, "Solar Panels", 30.0, 0, 0, 0, 0, true);
  station_facilities->facilities[station_facilities->facility_count++] = solar_panels;
}

double get_total_energy_use(Space_Station_Facilities* facilities)
{
  double total_energy_use = 0;
  for (int i = 0; i < facilities->facility_count; i++)
  {
    total_energy_use += facilities->facilities[i]->power_consumption;
  }

  return total_energy_use;
}

double get_total_energy_produce(Space_Station_Facilities* facilities)
{
  double total_energy_production;
  for (int i = 0; i < facilities->facility_count; i++)
  {
    total_energy_production += facilities->facilities[i]->energy_production;
  }

  return total_energy_production;
}

double get_total_food_produce(Space_Station_Facilities* facilities)
{
  double total_food_production;
  for (int i = 0; i < facilities->facility_count; i++)
  {
    total_food_production += facilities->facilities[i]->food_production;
  }

  return total_food_production;
}

double get_total_water_produce(Space_Station_Facilities* facilities)
{
  double total_water_production;
  for (int i = 0; i < facilities->facility_count; i++)
  {
    total_water_production += facilities->facilities[i]->water_production;
  }

  return total_water_production;
}

double get_total_oxygen_produce(Space_Station_Facilities* facilities)
{
  double total_oxygen_production;
  for (int i = 0; i < facilities->facility_count; i++)
  {
    total_oxygen_production += facilities->facilities[i]->oxygen_production;
  }

  return total_oxygen_production;
}
