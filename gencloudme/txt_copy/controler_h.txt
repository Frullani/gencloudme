//
//  controler.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef controler_hpp
#define controler_hpp

#include <fstream>

#include "field.hpp"
#include "function.hpp"


using namespace std;
//CREATED BY ARSENIY KLEVAKIN 211 GROUP
class controler{ //klas kontrolera
public:
    ofstream logcon;
    bool EXgistogramm = false;
    cloud* C;
    field* F;
    field* F_forel;
    //find_clasters* FC;
    controler();
    void gencloud(double x, double y, double Dx, double Dy, int N);
    void genfield();
    void write();
    void gistogramm_cloud(cloud A, int k);
    void write_gis_cloud(cloud A, vector<double> rect,double min,double max,double k);
    void gistogramm_all(int k);
    void write_gis_all(vector<double> rect, double min,double max, double k, long N);
    void create_find_claster();
    void write_clasters();
    
    //void genfield_for_forel();
    char* gettime();
};
#endif /* controler_hpp */
