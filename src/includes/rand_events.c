#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// CREATE DUST STORM EVENT

void create_dust_storm()
{

}

// CREATE ASTEROID RAND EVENT

typedef struct Asteroid
{
  double mass;
} Asteroid;

void initialise_asteroid(Asteroid* asteroid)
{
  asteroid->mass = ((rand() * 2) / (rand() % 10)) * 2260000000;
}

void shoot_asteroid(Asteroid* asteroid, int* damage_caused)
{
  int distance_from_base_km = 0;
  int fatal_damage_range;
  int shock_damage_range;
  int relative_shock_damage_power;
  int relative_base_distance_from_asteroid;

  distance_from_base_km = rand() % 200;

  // Asteroid mass = 4'520'000'000 means shock_damage_range = 200;
  
  fatal_damage_range = (asteroid->mass / 2260000000) * 30;
  shock_damage_range = (asteroid->mass / 2260000000) * 100;

  if (fatal_damage_range >= distance_from_base_km)
  {
    *damage_caused = -1; // Returns fatal as damage_caused
    return;
  }

  if (distance_from_base_km > shock_damage_range)
  {
    *damage_caused = 0;
    return;
  }

  if (shock_damage_range < distance_from_base_km) { return; }

  relative_shock_damage_power = shock_damage_range / 200;
  relative_base_distance_from_asteroid = (shock_damage_range / distance_from_base_km) - 1;

  *damage_caused = relative_shock_damage_power * (shock_damage_range) * relative_base_distance_from_asteroid;

  return;
}
