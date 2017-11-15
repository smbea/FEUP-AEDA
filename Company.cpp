#include "Company.h"
#include "Interfaces.h"
#include <fstream>

Company::Company() {
    string fileBeach = "BeachFile.txt";
    ifstream file;
    string beach, type;
    unsigned long stop;

    //verify file is successfully opened

    file.open(fileBeach);

    if (!file.is_open()) {
        cout << "Error in opening file. Exiting program...";
        exit(1);

    }

    while (getline(file, beach)) {
        stop = beach.find_first_of(';');
        type = beach.substr(0, stop);


        if (type == "river") {

            Beaches.push_back(new RiverBeach(beach.substr(stop + 2)));
        } else if (type == "bayou") {

            Beaches.push_back(new BayouBeach(beach.substr(stop + 2)));
        }
    }
}

unsigned int Company::beachExists(string name){
    for (unsigned int i = 0; i < Beaches.size(); ++i) {

        if (Beaches.at(i)->get_name() == name) {
            return i;
        }
    }
        return -1;
}

void Company::addBeach() {
    string type, county, name, utility;
    bool lifeguard, blueflag;
    unsigned long max_capacity;
    float lat, longi, width, maxDepth, aquaticArea;
    vector<string> basicServices;
    int utilities, counter = 0, services;
    string sType, sName, sPriceRange, sStars;

    cout << "Insert type (Bayou or River): " << endl << ":::";
    cin >> type;
    while(type != "River" && type != "Bayou"){

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid type: ";
        cin >> type;
    }

    cout << endl << "Insert county (eg: Arcos de Valdevez): "<< endl << ":::";
    cin.ignore(1000, '\n');
    getline(cin,county);

    cout << endl << "Insert name: "<< endl << ":::";
    getline(cin,name);

    cout << endl << "Insert 1 if contains blueflag, 0 otherwise: "<< endl << ":::";
    cin >> blueflag;

    cout << endl << "Insert 1 if contains lifeguard, 0 otherwise: "<< endl << ":::";
    cin >> lifeguard;

    cout << endl << "Insert maximum capacity (eg: 1000): "<< endl << ":::";
    cin >> max_capacity;
    fail(max_capacity);

    cout << endl << "Insert latitude and longitude coordinates(eg: 40.268799): "<< endl << ":::";
    cin >> lat;
    fail(lat);

    cout << ":::";
    cin >> longi;
    fail(longi);

    if (type == "River") {

        cout << endl << "Insert width in meters (eg: 72): "<< endl << ":::";
        cin >> width;
        fail(width);

        cout << endl << "Insert depth in meters (eg: 12): "<< endl << ":::";
        cin >> maxDepth;
        fail(maxDepth);

        Beaches.push_back(new RiverBeach(county, name, blueflag, lifeguard, max_capacity, lat, longi, width, maxDepth));
    }

    if (type == "Bayou") {

        cout << endl << "Insert width in meters (eg: 1150500000): " << endl << ":::";
        cin >> aquaticArea;
        fail(aquaticArea);

        (new BayouBeach(county, name, blueflag, lifeguard, max_capacity, lat, longi, aquaticArea));
    }
    
    cout << endl << "How many basic utilities does the beach have? (eg: wc, showers...): "<< endl << ":::";
    cin >> utilities;
    fail(utilities);
    while (counter < utilities) {
        cout << endl << ++counter << "st utility: ";
        getline(cin,utility);
        Beaches.at(Beaches.size() - 1)->getBasicServices().push_back(utility);
    }

    cout << endl << "How many services does the beach have? (eg, Hotel, Bar): "<< endl << ":::";
    cin >> services;
    fail(services);
    counter = 0;
    while (counter < services) {
        cout << endl << ++counter << "st service: ";
        
        cout << endl << "Type (eg: Hotel, Bar): ";
        getline(cin,sType);

        cout << endl << "Name (eg: Tapada Grande): ";
        getline(cin,sName);

        cout << endl << "Price Range (eg: 1/3): ";
        cin >> sPriceRange;
        while(sPriceRange != "1/3" || sPriceRange != "2/3" || sPriceRange != "3/3"){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid value: ";
            cin >> sPriceRange;
        }

        cout << endl << "Stars (eg: **): ";
        cin >> sStars;
        while(sStars != "*" || sStars != "**" || sStars != "***"){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid value: ";
            cin >> sStars;
        }

        Beaches.at(Beaches.size() - 1)->getExtraServices().emplace_back(Services(sType, sName, sPriceRange, sStars));
    }

    cout << "Beach added successfully!" << string(4,'\n');
}

void Company::alterRBeachInfo(unsigned int option, unsigned int i) {
    string name, county;
    bool blueflag, lifeguard;
    unsigned long max_capacity;
    float lat, longi;
    float width, maxDepth;
    vector<string> basicServices;
    vector<Services> extraServices;

    switch (option) {
        case 1:
            cout << "Insert new name: " << endl;
            cin >> name;
            Beaches.at(i)->set_name(name);
            break;
        case 2:
            Beaches.at(i)->set_blue_flag();
            break;
        case 3:
            Beaches.at(i)->set_lifeguard();
            break;
        case 4:
            cout << "Insert new maximum capacity: " << endl;
            cin >> max_capacity;
            Beaches.at(i)->set_max_capacity(max_capacity);
            break;
        case 5:
            cout << "Insert new width: " << endl;
            cin >> width;
            Beaches.at(i)->set_width(width);
            break;
        case 6:
            cout << "Insert new depth area: " << endl;
            cin >> maxDepth;
            Beaches.at(i)->set_maxDepth(maxDepth);
            break;
        case 7:
            cout << "Insert latitude and longitude coordinates separated by a space (eg: 40.268799 -7.143181): "
                 << endl;
            cin >> lat >> longi;
            Beaches.at(i)->set_latitude(lat);
            Beaches.at(i)->set_longitude(longi);
            break;
        case 8:
            break;
    }

}

void Company::alterBBeachInfo(unsigned int option, unsigned int i) {
    string name, county;
    bool blueflag, lifeguard;
    unsigned long max_capacity;
    float lat, longi;
    float aquaticArea;
    vector<string> basicServices;
    vector<Services> extraServices;

    switch (option) {
        case 1:
            cout << "Insert new name: " << endl;
            cin >> name;
            Beaches.at(i)->set_name(name);
            break;
        case 2:
            Beaches.at(i)->set_blue_flag();
            break;
        case 3:
            Beaches.at(i)->set_lifeguard();
            break;
        case 4:
            cout << "Insert new maximum capacity: " << endl;
            cin >> max_capacity;
            Beaches.at(i)->set_max_capacity(max_capacity);
            break;
        case 5:
            cout << "Insert new width: " << endl;
            cin >> aquaticArea;
            Beaches.at(i)->set_width(aquaticArea);
            break;
        case 6:
            cout << "Insert latitude and longitude coordinates separated by a space (eg: 40.268799 -7.143181): "
                 << endl;
            cin >> lat >> longi;
            Beaches.at(i)->set_latitude(lat);
            Beaches.at(i)->set_longitude(longi);
            break;
        case 7:
            break;
    }

}

void Company::removeBeach() {
    string name;
    bool removed = false;

    cout << "Insert beach name: ";
    cin >> name;

    for (int i = 0; i < Beaches.size(); ++i) {

        if (Beaches.at(i)->get_name() == name) {

            Beaches.erase(Beaches.begin()+i);
            cout << endl<< name<< " beach erased successfully!" << string(4,'\n');
            removed = true;
        }
    }

    if(!removed){
        cout <<endl << "ERROR: There is no beach with the given name!" << string(4,'\n');
    }
}

