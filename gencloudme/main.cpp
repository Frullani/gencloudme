//
//  main.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 17.09.2020.
//

#include "interface.hpp"


using namespace std;

//CREATED BY ARSENIY KLEVAKIN 211 GROUP
int main() {
    interface inter;
    ofstream incon;
    //string test = "ok";
    string s;
    s=inter.get();
    while(1){
        //if(s == "exit") break;
        inter.readcom();
        if(s == "exit") break;
        s=inter.get();
        //if(s == "exit") break;
    }
    return 0;
}
