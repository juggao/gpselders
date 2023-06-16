/*
   Print a random GPS coördinate and a handy lookup url

   MIT (c) 2023 René Oudeweg
  
   gcc gpsrand.c -Wall -g -Og -o gpselders

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int degrees;
    int minutes;
    int seconds;
} Coordinate;

typedef struct {
    double latitude;
    double longitude;
} DCoordinate; 

void printurl(double latitude, double longitude)
{
  char url[256];

  // Construct the OpenStreetMap API URL with the latitude and longitude
  snprintf(url, sizeof(url), "https://www.openstreetmap.org/?mlat=%f&mlon=%f#map=15/%f/%f", latitude, longitude, latitude, longitude);
  printf("curl: %s\n", url);
  snprintf(url, sizeof(url), "https://www.google.com/maps/place/%f,%f", latitude, longitude);
  printf("curl: %s\n", url); 
}

double getRandomCoordinate() {

    // Generate a random coordinate within the range of -90 to 90
    // double coordinate = ((double)rand() / RAND_MAX) * 180 - 90;
    int randomNumber = rand() % (RAND_MAX + 1);
    printf("rand: %d\n", randomNumber);
    double coordinate = ((double)randomNumber / RAND_MAX) * 180 - 90;

    return coordinate;
}

Coordinate convertToDegrees(double decimalCoordinate) {
    Coordinate coord;

    // Extract degrees
    coord.degrees = (int)decimalCoordinate;

    // Convert the decimal part to minutes and seconds
    double decimalMinutes = (decimalCoordinate - coord.degrees) * 60;
    coord.minutes = (int)decimalMinutes;

    double decimalSeconds = (decimalMinutes - coord.minutes) * 60;
    coord.seconds = (int)decimalSeconds;

    return coord;
}

Coordinate getRandomGPSCoordinate(double* coor) {
    *coor = getRandomCoordinate();
    return convertToDegrees(*coor);
}

int main() {
    DCoordinate dc;
    Coordinate latitude, longitude;

    // Seed the random number generator with the current time
    srand(time(NULL));

    latitude = getRandomGPSCoordinate(&dc.latitude);
    longitude = getRandomGPSCoordinate(&dc.longitude);
    printf("latitude: %f\n", dc.latitude);
    printf("longitude: %f\n", dc.longitude); 
    printf("Latitude: %d° %d' %d\"\n", latitude.degrees, latitude.minutes, latitude.seconds);
    printf("Longitude: %d° %d' %d\"\n",longitude.degrees, longitude.minutes, longitude.seconds);
    printurl(dc.latitude,dc.longitude);

 /*   queryGoogleWithCoordinates(lat, lon); */
 /*   queryOpenStreetMapWithCoordinates(dc.latitude, dc.longitude); */
    return 0;
}


