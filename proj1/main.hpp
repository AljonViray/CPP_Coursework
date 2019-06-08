//Code made by Aljon Viray, ID: 86285526
#include <iostream>
#include <string>


//Variables for Starting Location
float	      startLat,    startLon;	   //Starting Values
std::string   startLatDir, startLonDir;    //Starting Directions
std::string   startWord,   startName;	   //Starting words to make name

//Variables for New Location(s)
float	      newLat,    newLon,    newDist;
std::string   newLatDir, newLonDir;
std::string   newWord,   newName;

//Variables for Closest & Farthest Locations
float	      closeLat=0,  closeLon=0,  closeDist=0,    farLat=0,  farLon=0,  farDist=0;
std::string   closeLatDir, closeLonDir,                 farLatDir, farLonDir;
std::string   closeWord,   closeName,                   farWord,   farName;

//Misc Variables
int numOfTargets;