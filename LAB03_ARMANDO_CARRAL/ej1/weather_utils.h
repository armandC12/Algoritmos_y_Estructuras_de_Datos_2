/*
  @file weather_utils.h
  @brief Defines the structure and methods of the lowest minimum temperature, the highest maximum temperature, and the highest monthly amount of precipitation.
*/

#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H
#include <stdio.h>
#include "array_helpers.h"
#include "weather.h"

/* create un array for climate data */
typedef int Temp [YEARS];
typedef month_t Rainfall [YEARS];

/* receives an array, and returns the lowest minimum temperature */
unsigned int weather_min_temp(WeatherTable a);

/* Returns an array with the maximum temperatures of each year */
void weather_max_temp(WeatherTable a, Temp output);

/* Shows the array output[] that has the maximum temperatures of each year */
void array_dump_maxTemp(Temp output);

/* Returns an array[] with the months of each year where there was the highest monthly amount of rainfall */
void weather_max_rainfall(WeatherTable a, Rainfall output);

/* Shows the arrangement output[] with the months of greatest precipitation of each year */
void array_dump_month(Rainfall output);

#endif //_WEATHER_UTILS_H
