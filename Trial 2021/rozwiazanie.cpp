#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//define file name and size of input data
#define dataFile "galerie.txt"
#define dataSize 50

//count malls in every country
struct countryMalls {
    string country;
    int mallCount;
};

//count shops in every mall and its size
struct mall {
    string city;
    int size;
    int shopsCount;
};

//count different shop sizes available in the mall
struct shopSizes {
    string city;
    vector <int> sizes;
    int sizesAvailable;
};

//declare functions
void countCountryMalls(vector <countryMalls> &, string country);
void countMallSize(vector <mall> &, string city, int width, int height);
void findBiggestAndSmallestMall(vector <mall> &, mall &, mall &);
void countShopSizes(vector <shopSizes> &, string city, int width, int height);

int main(void){
    //declare variables
    vector <countryMalls> mallsInAllCountries;

    mall theBiggest;
    mall theSmallest;

    vector <mall> allMalls;

    vector <shopSizes> allShops;

    //load file
    ifstream data;
    data.open(dataFile);

    //get data and process it with custom functions
    for(int i = 0; i < dataSize; i++) {
        string country, city, mallShops = "";

        data>>country>>city;
        countCountryMalls(mallsInAllCountries, country);

        for (int i = 0; i < 70; i++) {
            int width, heigth;
            data>>width>>heigth;
            countMallSize(allMalls, city, width, heigth);
            countShopSizes(allShops, city, width, heigth);
        }
        
    }

    findBiggestAndSmallestMall(allMalls, theBiggest, theSmallest);

    //dislay results
    for (int i = 0; i < mallsInAllCountries.size(); i++) {
        cout<<mallsInAllCountries[i].country<<" "<<mallsInAllCountries[i].mallCount<<endl;
    }
    cout<<endl;
    for (int i = 0; i < allMalls.size(); i++){
        cout<<allMalls[i].city<<" "<<allMalls[i].size<<" "<<allMalls[i].shopsCount<<endl;
    }
    cout<<endl;
    cout<<"The biggest mall and it's size: "<<theBiggest.city<<" "<<theBiggest.size<<endl;
    cout<<"The smallest mall and it's size: "<<theSmallest.city<<" "<<theSmallest.size<<endl;
    cout<<endl;

    int mostSizes = 0;
    int lessSizes = 0;
    for (int i = 0; i < allShops.size(); i++) {
        if (allShops[i].sizesAvailable > allShops[mostSizes].sizesAvailable) {
            mostSizes = i;
        }else if (allShops[i].sizesAvailable < allShops[lessSizes].sizesAvailable) {
            lessSizes = i;
        }
    }
    cout<<"Mall with most shop size options: "<<allShops[mostSizes].city<<" "<<allShops[mostSizes].sizesAvailable<<endl;
    cout<<"Mall with smallest shop size options: "<<allShops[lessSizes].city<<" "<<allShops[lessSizes].sizesAvailable<<endl;
    cout<<endl;

    return 0;
}

//count malls in each country using structures, if the country already exists in vector then add 1 to mall count
//if not then create a new structure in vector and set country name and mall count (1)
void countCountryMalls(vector <countryMalls> & mallsInCountries, string country) {
    bool exists = false;

    for (int i = 0; i < mallsInCountries.size(); i++){
        if (mallsInCountries[i].country == country){
            mallsInCountries[i].mallCount++;
            exists = true;
        }
    }

    if (exists == false){
        mallsInCountries.push_back(countryMalls());
        mallsInCountries[mallsInCountries.size() - 1].country = country;
        mallsInCountries[mallsInCountries.size() - 1].mallCount = 1;
    }
}

//count mall size by adding each shop area, if the mall doesnt exists in vector then add it
void countMallSize(vector <mall> & malls, string city, int width, int height) {
    bool exists = false;

    for (int i = 0; i < malls.size(); i++) {
        if (malls[i].city == city){
            if(width != 0 && height != 0) {
                malls[i].shopsCount++;
                malls[i].size += width*height;
            }
            exists = true;
        }
    }

    if (exists == false) {
        malls.push_back(mall());
        malls[malls.size() - 1].city = city;
        malls[malls.size() - 1].shopsCount = 1;
        malls[malls.size() - 1].size = width*height;
    }
}

//find the biggest and the smallest mall
void findBiggestAndSmallestMall(vector <mall> & malls, mall & bigMall, mall & smallMall) {
    bigMall.city = malls[0].city;
    bigMall.size = malls[0].size;

    smallMall.city = malls[0].city;
    smallMall.size = malls[0].size;

    for (int i = 1; i < malls.size(); i++) {
        if (malls[i].size > bigMall.size){
            bigMall.city = malls[i].city;
            bigMall.size = malls[i].size;
        }else if (malls[i].size < smallMall.size){
            smallMall.city = malls[i].city;
            smallMall.size = malls[i].size;
        }
    }
}

//count all available shop sizes, exclude 0
void countShopSizes(vector <shopSizes> & shops, string city, int width, int height) {
    bool exists = false;

    for (int i = 0; i < shops.size(); i++){
        if (shops[i].city == city){
            int shopSize = width*height;
            bool shopSizeExists = false;
            for (int j = 0; j < shops[i].sizes.size(); j++) {
                if ( shops[i].sizes[j] == shopSize) {
                    shopSizeExists = true;
                }
            }

            if ( shopSizeExists == false && shopSize != 0 ) {
                shops[i].sizesAvailable++;
                shops[i].sizes.push_back(shopSize);
            }
            exists = true;
        }
    }

    if (exists == false) {
        shops.push_back(shopSizes());
        shops[shops.size() - 1].city = city;
        shops[shops.size() - 1].sizes.push_back(width*height);
        shops[shops.size() - 1].sizesAvailable = 1;
    }
}