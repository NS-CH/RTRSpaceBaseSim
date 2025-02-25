#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "rand_events.c"

typedef struct Management
{
  bool is_operational;
  Asteroid* detected_asteroids;
  int asteroid_count;
} Management;

void initialise_management_centre(Management* management)
{
  management->is_operational = true;
  management->detected_asteroids = malloc(sizeof(Asteroid));
  management->asteroid_count = 0;
}

void detect_asteroid(Management* management, Asteroid* asteroid)
{
  initialise_asteroid(asteroid);

  management->detected_asteroids[asteroid_count] = asteroid;
  management->asteroid_count++;
}

void track_asteroid(Management* management)
{
  printf("-=-=-=-=-=-=-=-=-");
  for (int i = 0; i < management->asteroid_count; i++)
  {
    printf("Asteroid Mass: %d", management->detected_asteroids[i]->mass);
    printf("Impact Distance from Base: %d", management->detected_asteroids[i]->distance_from_base_km);
    printf("Days until Impact: %d", management->detected_asteroids[i]->days_till_impact);
    printf("--==--==--==--");
  }
}

void kill_management_centre(Management* management)
{
  free(management->detected_asteroids);
  management->asteroid_count = 0;
}
