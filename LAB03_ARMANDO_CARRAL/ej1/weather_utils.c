/*
  @file weather_utils.c
  @brief Implements weather utils structure and methods
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "weather_utils.h"

unsigned int weather_min_temp(WeatherTable a) {
	int minTempHist = INT_MAX;

	for (unsigned int year = 0u; year < YEARS; ++year) {
		for (unsigned int month = 0u; month < MONTHS; ++month) {
			for (unsigned int day = 0u; day < DAYS; ++day) {
				Weather weather = a[year][month][day];
				if(weather._min_temp < minTempHist){
					minTempHist = weather._min_temp;
				}
			}
		}
	}

	return minTempHist;
}

void weather_max_temp(WeatherTable a, Temp output) {
	for(unsigned int year = 0u; year < YEARS; ++year){
		int maxTemp = INT_MIN;
		for (unsigned int month = 0u; month < MONTHS-1u; ++month) {
			for (unsigned int day = 0u; day < DAYS-1u; ++day) {
				Weather weather = a[year][month][day];
				if(weather._max_temp > maxTemp){
					maxTemp = weather._max_temp;
				}
			}
		}
		output[year] = maxTemp;
	}
}

void weather_max_rainfall(WeatherTable a, Rainfall output) {
	for (unsigned int year = 0; year < YEARS; ++year) {
		month_t mesPrec = january;
		unsigned int prec = 0u;
		for (unsigned int month = 0; month < MONTHS-1u; ++month) {
			unsigned int sumPrec = 0u;
			for (unsigned int day = 0u; day < DAYS-1u; ++day) {
				sumPrec = sumPrec + a[year][month][day]._rainfall;
			}
			if (prec < sumPrec) {
				prec = sumPrec;
				mesPrec = month;
			}
		}
		output[year] = mesPrec;
	}
}

void array_dump_maxTemp(Temp output){
	for (unsigned int year = 0u; year < YEARS; ++year) {
		printf("year: %d, maxTemp: %d\n", (year + FST_YEAR), output[year]);
	}
}
void array_dump_month(Rainfall output){
	for (unsigned int year = 0u; year < YEARS; ++year) {
		month_t months = output[year]+1u;
		switch(months){
			case january:
			printf("year: %d, month with the highest rainfall: January\n", (year + FST_YEAR));
			break;
			case february:
			printf("year: %d, month with the highest rainfall: February\n", (year + FST_YEAR));
			break;
			case march:
			printf("year: %d, month with the highest rainfall: March\n", (year + FST_YEAR));
			break;
			case april:
			printf("year: %d, month with the highest rainfall: April\n", (year + FST_YEAR));
			break;
			case may:
			printf("year: %d, month with the highest rainfall: May\n", (year + FST_YEAR));
			break;
			case june:
			printf("year: %d, month with the highest rainfall: June\n", (year + FST_YEAR));
			break;
			case july:
			printf("year: %d, month with the highest rainfall: July\n", (year + FST_YEAR));
			break;
			case august:
			printf("year: %d, month with the highest rainfall: August\n", (year + FST_YEAR));
			break;
			case september:
			printf("year: %d, month with the highest rainfall: September\n", (year + FST_YEAR));
			break;
			case october:
			printf("year: %d, month with the highest rainfall: October\n", (year + FST_YEAR));
			break;
			case november:
			printf("year: %d, month with the highest rainfall: November\n", (year + FST_YEAR));
			break;
			case december:
			printf("year: %d, month with the highest rainfall: December\n", (year + FST_YEAR));
			break;
			default: printf("Invalid month\n");
		}
	}
}
