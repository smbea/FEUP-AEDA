//
// Created by Beatriz Mendes on 16/10/2017.
//
#include "Beach.h"
#include <cmath>
#include <iomanip
#include <string>

//Beach
Beach::Beach(string &county,string &name, bool &blueflag, bool &lifeguard, unsigned long &max_capacity, float &LAT , float &LONG, vector<string> &basicServices):
county(county),name(name), blueflag(blueflag), max_capacity(max_capacity), LAT(LAT), LONG(LONG)
{
    this->basicServices=basicServices;
}


bool Beach::get_blue_flag(){return blueflag;}

bool Beach::get_lifeguard(){return lifeguard;}

unsigned long Beach::get_max_capacity(){return max_capacity;}

float Beach::get_Latitude(){return LAT;}

float Beach::get_Longitude(){return LONG;}

vector<Services> Beach::getExtraServices(){return extraServices;}

double Beach::distanceToBeach(float LAT, float LONG){
    double dLONG, dLAT, a, c, distance, earthRadius;
    earthRadius=6373;

    dLONG = this->LONG-LONG;
    dLAT= this->LAT - LAT;
    a= pow(sin(dLAT/2),2) + cos(LAT) * cos(this->LAT) * sin(dLONG/2);
    c= 2 * atan2(sqrt(a),sqrt(1-a));
    distance= c * 6373;

    return distance;
}

//River Beach
RiverBeach::RiverBeach(string &county, string &name, bool &blueflag, bool &lifeguard, unsigned long &max_capacity, float &LAT , float &LONG,  float &width, float &maxDepth, vector<string> &basicServices)
        :Beach(county, name, blueflag, lifeguard, max_capacity,  LAT ,  LONG, basicServices) {
    this->width=width;
    this->maxDepth=maxDepth;
}

RiverBeach::RiverBeach(string beach)
:Beach()
{
    unsigned long last;
    unsigned long stop; //stop is pos for last ';' found

    //attribute county
    stop= beach.find_first_of(';');
    this->county = beach.substr(0,stop);

    //name
    beach = beach.substr(stop+2); // +2 marks the begining of the char after space
    stop = beach.find_first_of(';');
    this->name = beach.substr(0,stop);

    //attribute blueflag
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    if(stoi(beach.substr(0,stop))){

        this->blueflag=true;

    }else
        this->blueflag=false;

    // attribute lifeguard
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    if(stoi(beach.substr(0,stop))){

        this->lifeguard=true;

    }else
        this->lifeguard=false;

    //attribute maximum capacity
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    this->max_capacity = stoul(beach.substr(0,stop));

    //attribute Latitude
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    this->LAT = stof(beach.substr(0,stop));

    //attribute Longitude
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    this->LONG = stof(beach.substr(0,stop));

    //attribute width
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    this->width = stof(beach.substr(0,stop));

    //attribute maximum depth
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    this->maxDepth = stof(beach.substr(0,stop));

    //attribute basic serves
    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    last = beach.find_first_of(';',stop);
    string bservices = beach.substr(stop,last);

    beach = beach.substr(stop+2);
    stop = beach.find_first_of(';');
    unsigned int last = beach.find_first_of(';',stop);
    string basic_services = beach.substr(stop,last);
    while(stop!=string::npos){
        this->basicServices.push_back(basic_services.substr(0,stop));
        beach = basic_services.substr(stop+2);
        stop = basic_services.find_first_of(',');
    }

    stop = beach.find_first_of('(');
    string extra_services = beach.substr(stop+2,beach.find_first_of(')')-stop);
    while(stop != string::npos){
        last = extra_services.find_first_of(';');
        string service,type,name,priceRange,stars;
        service = extra_services.substr(stop+2,last-stop);
        unsigned int pos = extra_services.find_first_of(',');
        type = service.substr(stop,pos-stop);
        stop = pos;
        pos = service.find_first_of(',',stop);
        name = service.substr(stop,pos-stop);
        stop = pos;
        pos = service.find_first_of(',',stop);
        priceRange = service.substr(stop,pos-stop);
        stop = pos;
        pos = last;
        stars = service.substr(stop,pos-stop);
        this->extraServices.emplace_back( Services(type,name,priceRange,stars));
        stop = last;
    }
}

void RiverBeach::displayBeach(){

    cout << "County : " << county << endl;
    cout << "GPS coordinates: " << LAT << " | " << LONG << endl;
    cout << "Name   : " << name << endl;
    cout << "Maximum Capacity : " << max_capacity << endl;
    cout << "Width : " << width << endl;
    cout << "Maximum Depth :" << maxDepth << endl;

    if(blueflag == true && lifeguard == true){

        cout << "Useful information : " <<  "Blue Flag" << endl << setw(21) << setfill(' ') << "Life Guard" << endl;
        for (unsigned int i = 0; i < basicServices.size(); i++){

            cout << setw(21) << setfill(' ') << basicServices.at(i);
        }
    }else if(blueflag == true && lifeguard == false){
        cout << "Useful information : " <<  "Blue Flag" << endl;
        for (unsigned int i = 0; i < basicServices.size(); i++){

            cout << setw(21) << setfill(' ') << basicServices.at(i);
        }
    }else if(blueflag == false && lifeguard == false){
        cout << "Useful information : " << "Life Guard" << endl;
        for (unsigned int i = 0; i < basicServices.size(); i++) {

            cout << setw(21) << setfill(' ') << basicServices.at(i);
        }
    }
    else{
        cout << "Useful information : " << basicServices.at(0) << endl;
        for (unsigned int i = 1; i < basicServices.size(); i++) {

            cout << setw(21) << setfill(' ') << basicServices.at(i);
        }
    }

    cout << endl << "Services : " << endl;
    for(unsigned int i = 0; i < extraServices.size(); i++){
        cout << setw(11) << setfill(' ') << "Type : " << extraServices.at(i).getType() << endl;
        cout << setw(11) << setfill(' ') << "Name : " << extraServices.at(i).getName() << endl;
        cout << setw(11) << setfill(' ') << "Price Range : " << extraServices.at(i).getPriceRange() << endl;
        cout << setw(11) << setfill(' ') << "Stars : " << extraServices.at(i).getStars() << endl << endl;
    }
}

//Bayou Beach
BayouBeach::BayouBeach(string &county, string &name, bool &blueflag, bool &lifeguard, unsigned long &max_capacity, float &LAT , float &LONG, float &aquaticArea, vector<string> &basicServices)
        :Beach(county,name, blueflag, lifeguard, max_capacity,  LAT ,  LONG, basicServices){
    this->aquaticArea=aquaticArea;
}

