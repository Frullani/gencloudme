//
//  interface.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef interface_hpp
#define interface_hpp


#include "controler.hpp"

//CREATED BY ARSENIY KLEVAKIN 211 GROUP
class interface{ //class interfeysa
private: controler rol;
public:
    ofstream incon;
    double x, y, Dx, Dy, N, delta;
    int a, k;
    string com;
    //string filename="in.txt";
    ifstream in;
    interface();
    string get();
    void readcom();
    
    char *gettime();
};
#endif /* interface_hpp */
