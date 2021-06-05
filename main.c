/*
lat1 خط الطول الاول
lon1 خط العرض الاول
*/

#include<stdio.h>
#include<conio.h>
#include<math.h>

#define pi 3.14159265358979323846

double deg2rad(double);
double rad2deg(double);


double distance(double lat1, double lon1, double lon2, double lat2)
{
    scanf("%%lf %%lf", &lat1, &lon1);
    scanf("%%lf %%lf", &lat2, &lon2);
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515 * 1609.344; // distance is now in miles * 1609.344 in meters 
        return (dist); // in meters 
    }

}
double main() {
    
    return(0);
}
/* ::This function converts decimal degrees to radians : */
double deg2rad(double deg) {
    return (deg * pi / 180);
}
/* ::This function converts radians to decimal degrees : */
double rad2deg(double rad) {
    return (rad * 180 / pi);
}