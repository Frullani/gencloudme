//
//  function.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#include "function.hpp"
//CREATED BY ARSENIY KLEVAKIN 211 GROUP
vector<double> bubleS(vector<double> a){
    double buth;
    bool go=true;
    while (go==true) {
        go =false;
        for(int i=0; i<a.size()-1; i++){
            if(a[i+1]<a[i]){
                buth = a[i];
                a[i]=a[i+1];
                a[i+1]=buth;
                go=true;
                //cout << a[0];
            }
        }
    }
    return a;
}
