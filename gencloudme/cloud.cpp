//
//  cloud.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 12.10.2020.
//

#include "cloud.hpp"
//CREATED BY ARSENIY KLEVAKIN 211 GROUP
void cloud::gen(double x, double y, double Dx, double Dy, int N){ //generacia oblaka
    double t; int znak;
    double sum_x, sum_y, newX, newY;
    //vector<point> points;
    for(int i=0; i<N; i++){ //generim tocki
        point newpoint;
        
        t=rand()%100;
        t=t/20;
        if(rand()%2==1) znak=1;
        else znak=-1;
        t=t*znak;
        sum_x=t;
        
        t=rand()%100;
        t=t/20;
        if(rand()%2==1) znak=1;
        else znak=-1;
        t=t*znak;
        sum_y=t;
        
        sum_x=sampleNormal();
        sum_y=sampleNormal();
        
        newX=x + (sum_x)*Dx;
        newY=y + (sum_y)*Dy;
        
        newpoint.in(newX, newY);
        points.push_back(newpoint); //zapis kajdoy tocki v svoe oblako
    }
    countP=N; //zapisali kolicestvo tochek
}

double cloud::sampleNormal() {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}
