//
//  controler.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#include "controler.hpp"
//CREATED BY ARSENIY KLEVAKIN 211 GROUP

controler::controler(){
    logcon.open("logcon.txt", ios_base::app);
    logcon << "New session " << gettime();
}

void controler::gencloud(double x, double y, double Dx, double Dy, int N){
    C = new cloud;
    C->gen(x, y, Dx, Dy, N);
    F->clouds.push_back(*C); //hranenie oblaka v pole
    F->countC++;
    
    F->countP += C->countP;
    logcon << "generate cloud Number " << C->Numcl << " "<<gettime();
}
void controler::genfield(){
    F = new field;
    logcon << "generate field " << gettime();
}

void controler::write(){ //zapis v fail
    string filename="dots.txt";
    ofstream out(filename);
    int numpoints=0;
    for(int j=0; j<F->countC; j++){ //po kolichestvu oblakob
        for(int i=0; i<F->clouds[j].countP; i++){//po kolichestvu tochek
            
            out << F->clouds[j].points[i].x << " ";
            out << F->clouds[j].points[i].y << " ";
            out << F->clouds[j].points[i].color << endl;
            //out <<F->clouds[j].points[i].marker << endl;
                numpoints++;
        }
    }
    out.close();
    logcon << "write "  << numpoints << " points to file " << gettime();
}

void controler::gistogramm_cloud(cloud A, int k){
    double min, max, h;
    int N, count=0;
    vector <double> sortX;
    vector<double> rect;
    for(int i=0; i<A.countP; i++){
        sortX.push_back(A.points[i].x);
    }
    
    sortX=bubleS(sortX);
    min=sortX[0];
    max=sortX[sortX.size()-1];
    cout << min << " " << max;
    h=(max-min)/k;
    //cout << " " << h+min << " " <<h*3+min;
    //cout << sortX.size();
    for(int i=1; i<=k; i++){
        N=0;
        for(int j=count; j<sortX.size(); j++){
            if((sortX[j]<=h*i+min)&&(sortX[j]>=h*(i-1)+min)){
                N++;
                cout << h*(i-1)+min << " X " <<h*i+min << " ";
                cout << sortX[j] << endl;
            }
        }
        rect.push_back(N);
    }
    for(int i=0; i<k; i++){
        cout << " " << rect[i];
    }
    logcon << "build gistogram for " << A.Numcl << " cloud "<< gettime();
    write_gis_cloud(A, rect, min, max, h);
    
}

void controler::write_gis_cloud(cloud A, vector<double> rect,double min,double max,double k){
    ofstream gis;
    string filename;
    double machtab = 5;
    vector<double> pers;
    double sred=0;
    double ax, bx, cx, dx;
    double ay, by, cy, dy;
    filename="giscl.txt";
    gis.open(filename);
    ax=3;
    for(int i=0; i<rect.size(); i++){
        pers.push_back(rect[i]/A.countP);
        //cout <<ax/A.countP;
        //cout<<endl << pers[i];
    }
    for(int i=0; i<A.countP; i++){
        sred=A.points[i].y+sred;
    }
    sred=sred/A.countP;
    cout <<"sred="<< min;
    for(int i=0; i<rect.size(); i++){
        ax=min+k*(i+1);
        ay=sred+pers[i]*machtab;
        bx=min+k*(i);
        by=ay;
        cx=bx;
        cy=sred;
        dx=ax;
        dy=cy;
        gis << bx << " " << by <<endl;
        gis << cx << " " << cy <<endl;
        gis << dx << " " << dy <<endl;
        gis << ax << " " << ay <<endl;
        gis << bx << " " << by <<endl;
        gis << ax << " " << ay <<endl;
    }
    logcon << "write gistogram to file" << gettime();
}

void controler::gistogramm_all(int k){
    double min, max, h;
    long N=0, count=0, NN=0;
    vector <double> sortX;
    vector<double> rect;
    for(int i=0; i<F->countC; i++){
        NN=NN+F->clouds[i].countP;
        for(int j=0; j<F->clouds[i].countP; j++){
            sortX.push_back(F->clouds[i].points[j].x);
        }
    }
    
    sortX=bubleS(sortX);
    min=sortX[0];
    max=sortX[sortX.size()-1];
    cout << min << " " << max;
    h=(max-min)/k;
    //cout << " " << h+min << " " <<h*3+min;
    //cout << sortX.size();
    for(int i=1; i<=k; i++){
        N=0;
        for(long j=count; j<sortX.size(); j++){
            if((sortX[j]<=h*i+min)&&(sortX[j]>=h*(i-1)+min)){
                N++;
                cout << h*(i-1)+min << " X " <<h*i+min << " ";
                cout << sortX[j] << endl;
            }
        }
        rect.push_back(N);
    }
    for(int i=0; i<k; i++){
        cout << " " << rect[i];
    }
    logcon << "build gistogram for " << " all points "<< gettime();
    write_gis_all(rect, min, max, h, NN);
}

void controler::write_gis_all(vector<double> rect, double min,double max, double k, long N){
    ofstream gis;
    string filename;
    double machtab = 5;
    vector<double> pers;
    double sred=0;
    double ax, bx, cx, dx;
    double ay, by, cy, dy;
    filename="gisall.txt";
    gis.open(filename);
    ax=3;
    for(int i=0; i<rect.size(); i++){
        pers.push_back(rect[i]/N);
        //cout <<ax/A.countP;
        //cout<<endl << pers[i];
    }
    for(int i=0; i<F->countC; i++){
        for(int j=0; j<F->clouds[i].countP; j++){
            sred=sred+F->clouds[i].points[j].y;
        }
    }
    sred=sred/N;
    cout <<"sred="<< min;
    for(int i=0; i<rect.size(); i++){
        ax=min+k*(i+1);
        ay=sred+pers[i]*machtab;
        bx=min+k*(i);
        by=ay;
        cx=bx;
        cy=sred;
        dx=ax;
        dy=cy;
        gis << bx << " " << by <<endl;
        gis << cx << " " << cy <<endl;
        gis << dx << " " << dy <<endl;
        gis << ax << " " << ay <<endl;
        gis << bx << " " << by <<endl;
        gis << ax << " " << ay <<endl;
    }
    logcon << "write gistogram to file " << gettime();
}



void controler::write_clasters(){
    ofstream out;
    out.open("clasters.txt");
    for(int j=0; j<F->countC; j++){ //po kolichestvu oblakob
        for(int i=0; i<F->clouds[j].countP; i++){//po kolichestvu tochek
            if( F->clouds[j].points[i].marker!=3){
            out << F->clouds[j].points[i].x << " ";
            out << F->clouds[j].points[i].y << " ";
                out <<F->clouds[j].points[i].color << endl;}
            else{
                out << F->clouds[j].points[i].x << " ";
                out << F->clouds[j].points[i].y << " ";
                out << 0.7 << endl;
            }
            //out <<F->clouds[j].points[i].marker << endl;
        }
    }
    out.close();
}

char* controler::gettime(){
    char *t;
    time_t now = time(0);
    t = ctime(&now);
    return t;
}
