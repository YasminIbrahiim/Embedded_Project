#include<stdio.h>
#include<math.h>
#define pi 3.14159265358979323846

double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1,double lon1,double lon2,double lat2);
int Update_distance(double lat, double lon);
int call_back(int(*ptr)());
int get_coordinates();

double distance(double lat1,double lon1,double lon2,double lat2)
{
     printf("lon1 = %lf\n",lon1);
	 printf("lat1 = %lf\n",lat1);
	 printf("lon2 = %lf\n",lon2);
	 printf("lat2 = %lf\n",lat2);
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
        printf("distance = %lf\n",dist);
		return dist; 		// in meters 
    }

}
//This function converts decimal degrees to radians 
double deg2rad(double deg) {
    return (deg * pi / 180);
}
//This function converts radians to decimal degrees 
double rad2deg(double rad) {
    return (rad * 180 / pi);
}
double prev_lat = 0 ;
double prev_lon = 0 ;
double Total_distance = 0;
int Update_distance(double lati, double loni){   
		
        if ((prev_lat != 0 ) && (prev_lon != 0)){
          printf("not equal 0 = \n" );
		  while( Total_distance < 100){
         Total_distance += distance(prev_lat , prev_lon, loni ,lati );
		   
           prev_lat = lati;
           prev_lon = loni;
			int(*ptr)() = &get_coordinates;			
			call_back(ptr);	
}
		   int d = (int) Total_distance;
           printf("total = %d\n",d); 
		   return d;			
        }   		
			prev_lat = lati;
           prev_lon = loni;
		   printf("equal 0\n");
		   int(*ptr)() = &get_coordinates;
			call_back(ptr);
           
		  } 

int call_back(int(*ptr)()){
	(*ptr) ();
}
int get_coordinates(){ 
 double lat;
 double lon;
	 printf("Enter lat , lon\n ");
	 scanf("%lf %lf", &lat , &lon);
	 Update_distance(lat,lon);
	
	 }

int main (){
int(*ptr)() = &get_coordinates;
call_back(ptr);
return(0);
}