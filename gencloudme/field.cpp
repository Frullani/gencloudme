//
//  field.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//
#include <math.h>
#include "field.hpp"

//CREATED BY ARSENIY KLEVAKIN 211 GROUP

void field::gencloud(double x, double y, double Dx, double Dy, int N){
    if(state=="ok"){
        cloud A;
        clouds.push_back(A);
        A.Numcl=clouds.size()%1000-1;
        while (cout << "ok") {
            cout << "klop";
        }
    }
}

void field::cpycloud(string file){
    ifstream in;
    string line;
    cloud A;
    //file.insert(0, 1, '"');
    //file.push_back('"');
    in.open(file);
    int n;
    point p;
    double t;
    in >> n;
    for(int i=0; i<n; i++){
        in >> p.x;
        in >> p.y;
        in >> t;
        A.points.push_back(p);
    }
    A.countP=n;
    clouds.push_back(A);
    A.Numcl=clouds.size()%1000-1;
    countC++;
    countP=countP+n;
}

void field::gen_distant_M(){
    DM= new distant_matrix;
    build_matix();
}

void field::point_numbering(){
    int counter=0;
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            clouds[i].points[j].NumP=counter;
            counter++;
        }
    }
}



point* field::find_point_by_number(int n){ //return ptr of point by number
    long C=0;
    int i=0;
    for(i=0; i<countC; i++){
        C=C+clouds[i].countP;
        if(n<C) {
            C=C-clouds[i].countP;
            break;
        }
    }
    return &clouds[i].points[n-C];
}

void field::wave_algo(vector<vector<bool>> B, int p){
    vector<point*> ter;
    point *a;
    point *main;
    int t=0;
    bool go=true;
    
    main=find_point_by_number(p);
    
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            clouds[i].points[j].new_state=t;
        }
    }
    t++;
    main->new_state=t;
    main->priv_state=0;
    ter.push_back(main);
    
    while(go==true){
        t++;
        
        for(int i=0; i<countC; i++){
            for(int j=0; j<clouds[i].countP; j++){ //prohod po vsem toshkam
                if((clouds[i].points[j].new_state==t-1)&&(clouds[i].points[j].marker!=3)){ //esli tochka yavlatca frontom volni
                    //cout << "T=" << t << endl;
                    for(int k=1; k<B.size(); k++){ //serch for incendentnie tochki
                        if((B[clouds[i].points[j].NumP][k]==1)&&(clouds[i].points[j].marker!=3)){
                
                            a=find_point_by_number(k);
                            if(a->new_state==0){
                            a->priv_state=a->new_state;
                            a->new_state=t;
                            
                            ter.push_back(a);
                            }
                        }
                    }
                }
            }
        }
        //cout << ter.size();
        go=false;
        
        for(int i=0; i<countC; i++){
            for(int j=0; j<clouds[i].countP; j++){
                if((clouds[i].points[j].new_state==t-1)&&(clouds[i].points[j].marker!=3)) go = true;
            }
        }
        //if(go==false) cout << "advwfvq";
        //countClas++;
    }
    for(int i=0; i<ter.size(); i++){
        FC->new_cluster();
        FC->clasters[FC->countClas-1].points.push_back(ter[i]);
    }
    //FC->new_cluster();
}

void field::find_by_wave(){
    //wave_algo(GM->BI, 0);
    FC=new find_clasters;
    FC_count++;
    FC->FC_num=FC_count-1;
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            if((clouds[i].points[j].new_state==0)&&(clouds[i].points[j].marker==1)){
                cout << "arivederchi";
                wave_algo(FC->GM->BI, clouds[i].points[j].NumP);
            }
        }
    }
    FC->colorize();
}

void field::k_means(int k){
    vector<point> c;
    vector<point *> group;
    point a;
    bool go=true;
    
    for(int i=0; i<k; i++){
        a=*find_point_by_number(i);
        a.metka=i;
        c.push_back(a);
    }
    
    while (go == true) {
        razmetka(k, c);
        go=false;
        
        for(int i=0; i<k; i++){
            group.clear();
            group=find_group(i, group);
            //cout<<endl <<group.size();
            a=center_mass(group);
            if((go==false)&&((a.x!=c[i].x)||(a.y!=c[i].y))) go=true; //term of stop
            c[i]=a;
        }
        
    }
    FC = new find_clasters;
    
    for(int i=0; i<k; i++){
        FC->new_cluster();
        group.clear();
        group=find_group(i, group);
        FC->clasters[i].points=group;
    }
    FC->colorize();
    fin_cl.push_back(*FC);
}

double field::D(point a, point b){
    return (sqrt(mod((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))));
}

double field::mod(double a){
    if (a==0) return a;
    if (a<0.000001) return -a;
    else return a;
}

void field::razmetka(int k, vector<point> c){ //find nearest center to point and marker it one by one
    double min, metka, d;

    for(int i=0; i<countC; i++){ //razmetka tochek
        for(int j=0; j<clouds[i].countP; j++){ //prohod po vsem toshkam
            min = D(clouds[i].points[j], c[0]);
            metka=c[0].metka;
            
            for(int l=1; l<k; l++){
                d=D(clouds[i].points[j], c[l]);
                if(min>d) {
                    min=d;
                    metka=c[l].metka;
                }
            }
            clouds[i].points[j].metka=metka;
        }
    }
}

void field::razmetka_in_group(int p, vector<point*> dot, vector<point> c){
    double min, metka, d;
    
    for(int i=0; i<dot.size(); i++){
        min = D(*dot[i], c[0]);
        metka=c[0].metka;
        
        for(int l=1; l<p; l++){
            d=D(*dot[i], c[l]);
            if(min>d) {
                min=d;
                metka=c[l].metka;
            }
        }
        dot[i]->metka=metka;
    }
}

vector<point *> field::find_group(int metka, vector<point *> g){ //nohodit vse tocki s metkoy
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            if(clouds[i].points[j].metka==metka){
                g.push_back(&clouds[i].points[j]);
                //cout<<endl << g.size();
            }
        }
    }
    return g;
}

point field::center_mass(vector<point *> g){ //find center mass of group
    point a;
    a.x=g[0]->x;
    a.y=g[0]->y;
    a.metka=g[0]->metka;
    for(int i=1; i<g.size(); i++){
        a.x=a.x+(g[i]->x-a.x)/(i+1);
        a.y=a.y+(g[i]->y-a.y)/(i+1);
    }
    return a;
}

void field::DBSCAN(double d, int k){
    int sum=0;
    FC=new find_clasters;
    FC_count++;
    FC->FC_num=FC_count-1;
    
    FC->GM->build_GM(DM->M, d);
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            sum=0;
            for(int l=0; l<FC->GM->BI.size(); l++){
                sum=sum+FC->GM->BI[clouds[i].points[j].NumP][l];
            }
            if(sum>=k){
                clouds[i].points[j].marker=1;
                for(int l=0; l<FC->GM->BI.size(); l++){
                    if(FC->GM->BI[clouds[i].points[j].NumP][l]==1) {
                        find_point_by_number(l)->marker=2;
                    }
                }
            }
            
        }
    }
}


void field::build_matix(){ //stroim matricu rassroyaniy
    vector <double> buth;
    vector<vector <double>> M;
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            for(int k=0; k<countC; k++){
                for(int l=0; l<clouds[k].countP; l++){
                    buth.push_back(D(clouds[i].points[j], clouds[k].points[l]));
                }
            }
            M.push_back(buth);
            buth.clear();
        }
    }
    DM->M=M;
}


void field::k_means_core(int k, int p){ //k - Number of clasters, p - numvber of cores
    vector<point> c;
    vector<point *> group;
    vector<vector<point>> core;
    vector<vector<point*>> privcore;
    point a;
    ofstream out_p, out_c;
    out_c.open("k_means_cores.txt");
    out_p.open("k_means_dots.txt");
    
    //bool go=true;
    
    core.resize(k); privcore.resize(k);
    
    
    for(int i=0; i<k; i++){
        core[i].resize(p);
    }
    
   // group=find_group(100, group);
    //k_means_for_group(k, group, 1);
    k_means(k);
    //group=find_group(0, group);
    //core[0]=k_means_for_group(p, group, 0);
    
    FC = new find_clasters;
    for(int i=0; i<k; i++){
        FC->new_cluster();
        group.clear();
        group=find_group(i, group);
        FC->clasters[i].points=group;
    }
    
    for(int g=0; g<1000; g++){
        
        for(int i=0; i<k; i++){ //for each group
        group.clear();
        group=find_group(i, group);
        //cout << group.size() <<"!!!"<< i<<endl;
        if(( group.size()!=0)&&( group.size()!=1))
        core[i]=k_means_for_group(p, group, i);
            for(int ver=0; ver<group.size(); ver++){
                group[ver]->metka=-p-10;
            }
        }
        razmetka_by_core(k, core);
        
        for(int i=0; i<k; i++){
            //FC->new_cluster();
            group.clear();
            group=find_group(i, group);
            FC->clasters[i].points=group;
        }
        FC->colorize();
        write_dots_in_iteration(out_p);
        out_p << endl << endl;
        write_cores_to_file(core, out_c);
    }
    
    
    FC->colorize();
    write_cores_to_file(core, out_c);
    fin_cl.push_back(*FC);
}

vector<point> field::k_means_for_group(int k, vector<point*> dot, int marker){ //k_means for group of dots by k claters
    vector<point> c;
    vector<point *> group;
    point a;
    bool go=true;
    
    for(int i=0; i<k; i++){
        a=*dot[i];
        a.metka=-i-1;
        c.push_back(a);
    }
    
    while (go == true) {
        razmetka_in_group(k, dot, c);
        go=false;
        
        for(int i=0; i<k; i++){
            group.clear();
            group=find_group(-i-1, group);
            //cout<<endl <<group.size();
            a=center_mass(group);
            if((go==false)&&((a.x!=c[i].x)||(a.y!=c[i].y))) go=true; //term of stop
            c[i]=a;
        }
        
    }
    for(int i=0; i<c.size(); i++){
        c[i].metka=marker;
    }
    return c;
}

void field::razmetka_by_core(int k, vector<vector<point>> core){ //razmetca tochek
    double min, metka, d;

    for(int i=0; i<countC; i++){ //razmetka tochek
        for(int j=0; j<clouds[i].countP; j++){ //prohod po vsem toshkam
            min = D(clouds[i].points[j], core[0][0]);
            metka=0;
            
            for(int l=1; l<core.size(); l++){
                for(int t=1; t<core[l].size(); t++){
                   d = D(clouds[i].points[j], core[l][t]);
                    if(min>d) {
                        min=d;
                        metka=core[l][t].metka;
                    }
                }
            }
            clouds[i].points[j].metka=metka;
        }
    }
}

void field::EM_algo(int k){ //EM algoritm for k clasters
    vector<double> w; //prior probabilltis for claster
    vector<vector<double>> mu; //center of claster
    vector<vector<vector<double>>> sum; //covarience
    FC = new find_clasters;
    vector<double> buth;
    double S, klop;
    mu.resize(k); //for 2d EM
    sum.resize(k);
    vector<point*> group;
    
    vector<vector<double>> test;
    vector<double> mutest;
    point g;
    test.resize(2);
    test[0].resize(2);
    test[1].resize(2);
    test[0][0]=1;
    test[0][1]=0.5;
    test[1][0]=0.5;
    test[1][1]=4;
    g.x=5;
    g.y=5;
    mutest.resize(2);
    mutest[0]=3;
    mutest[1]=4;
    g.x=0;
    ofstream out_p, out_e;
    out_e.open("ellips.txt");
    out_p.open("EMdots.txt");
    for(int i=0; i<k; i++){ //incelezation of arrays
        mu[i].push_back(i);
        mu[i].push_back(i);
        
        S=k;
        //cout << "s=" << S;
        w.push_back(1/S);
        //cout << w[0];
        
        sum[i].resize(2);
        sum[i][0].push_back(1); //matrix with size k*2*2
        sum[i][0].push_back(0);
        sum[i][1].push_back(0); //matrix with size k*2*2
        sum[i][1].push_back(1);
        
    }
    
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            cout << sum[1][i][j];
        }
        cout << endl;
    }
    
    FC->ME.exp.resize(k);
    for(int i=0; i<k; i++){
        FC->ME.exp[i].resize(countP);
        cout << "mux=" <<mu[i][0] <<"muy="<<mu[i][1] <<"w="<<w[i] <<"sum="<<sum[i][0][0]<<"sum="<<sum[i][1][1]<< endl;
    }
    
    razmetka_for_EM(k);
    
    for(int i=0; i<k; i++){
        FC->new_cluster();
        group.clear();
        group=find_group(i, group);
        FC->clasters[i].points=group;
    }
    FC->colorize();
    
    for(int glob=0; glob<200; glob++){
        cout <<"itr=" << glob << endl;
    for(int i=0; i<k; i++){ //E step
        //FC->ME.exp[i].resize(countP);
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
                S=0;
                for(int l=0; l<k; l++){
                    S=S+w[l]*parametr_of_distribution(clouds[q].points[j], sum[l], mu[l]);
                }
                //cout << "S=" <<S;
                //FC->ME.exp[i].resize(countP);
                FC->ME.exp[i][clouds[q].points[j].NumP]=w[i]*parametr_of_distribution(clouds[q].points[j], sum[i], mu[i])/S;
                //cout <<"w="<<w[i]<<"p="<<parametr_of_distribution(clouds[q].points[j], sum[i], mu[i])/S;
                //cout << endl;
                //cout <<"res==" <<FC->ME.exp[i][clouds[q].points[j].NumP];cout << endl;
                //cout <<"i=" <<i << "num=" << clouds[q].points[j].NumP;cout << endl;
            }
        }
    }

    for(int i=0; i<k; i++){ //M step
        S=0;
        
        for(int q=0; q<countP; q++){
            S=FC->ME.exp[i][q]+S;
        }
        
        klop=0;
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
            klop=FC->ME.exp[i][clouds[q].points[j].NumP]*clouds[q].points[j].x+klop;
            }
        }
        mu[i][0]=klop/S;
        klop=0;
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
                klop=FC->ME.exp[i][clouds[q].points[j].NumP]*clouds[q].points[j].y+klop;
            }
        }
        mu[i][1]=klop/S;
        
        klop=0;
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
            klop=FC->ME.exp[i][clouds[q].points[j].NumP]*(clouds[q].points[j].x-mu[i][0])*(clouds[q].points[j].x-mu[i][0])+klop;
            }
        }
        sum[i][0][0]=klop/S;
        
        klop=0;
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
            klop=FC->ME.exp[i][clouds[q].points[j].NumP]*(clouds[q].points[j].x-mu[i][0])*(clouds[q].points[j].y-mu[i][1])+klop;
            }
        }
        sum[i][0][1]=klop/S;
        sum[i][1][0]=sum[i][0][1];
        klop=0;
        for(int q=0; q<countC; q++){
            for(int j=0; j<clouds[q].countP; j++){
            klop=FC->ME.exp[i][clouds[q].points[j].NumP]*(clouds[q].points[j].y-mu[i][1])*(clouds[q].points[j].y-mu[i][1])+klop;
            }
        }
        sum[i][1][1]=klop/S;
        
        w[i]=S/countP;
        cout << "mux=" <<mu[i][0] <<"muy="<<mu[i][1] <<"w="<<w[i] <<"sum="<<sum[i][0][0]<<"sum="<<sum[i][1][1]<< endl;
    }
        
        for(int i=0; i<k; i++){
            write_elips_to_file(sum[i], mu[i], i+1, out_e);
        }
        out_e<<endl << endl;
        razmetka_for_EM(k);
        for(int i=0; i<k; i++){
            group.clear();
            group=find_group(i, group);
            FC->clasters[i].points=group;
        }
        FC->colorize();
        write_dots_in_iteration(out_p);
        out_p <<endl << endl;
    }
    fin_cl.push_back(*FC);
}

vector<vector<double>> field::matrix_mult(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C;
    C.resize (A.size());
    unsigned long m, n,  p;
    double sum=0;
    m=A.size();
    n=B.size();
    p=B[0].size();
    
    
    for(int i=0; i<m; i++){
        for(int j=0; j<p; j++){
            for(int str_b=0; str_b<n; str_b++){
                    sum=A[i][str_b]*B[str_b][j]+sum;
            }
            C[i].push_back(sum);
            sum=0;
        }
    }
    return C;
}

double field::mah_dis(vector<vector<double>> sum, vector<double> mu, point a){
    mu[0]=a.x-mu[0];
    mu[1]=a.y-mu[1];
    sum=mat_inv(sum);
    //cout <<"0="<<sum[0][1]<<"1="<<sum[1][0]<<"res="<<mu[0]*(mu[0]*sum[0][0]+mu[1]*sum[0][1])+mu[1]*(mu[0]*sum[1][0]+mu[1]*sum[1][1])<<"ol";
    //cout << endl;
    return mu[0]*(mu[0]*sum[0][0]+mu[1]*sum[1][0])+mu[1]*(mu[0]*sum[1][0]+mu[1]*sum[1][1]);
}

double field::parametr_of_distribution(point a, vector<vector<double>> sum, vector<double> mu){
    double p;
    p=(1/(sqrt(6.28*mat_D(sum))))*exp(mah_dis(sum, mu, a)*(-0.5));
    //cout << "mah" <<exp(mah_dis(sum, mu, a)*(-0.5))<<" ";
    return p;
}

double field::mat_D(vector<vector<double>> sum){
    return sum[1][1]*sum[0][0]-sum[1][0]*sum[0][1];
}

vector<vector<double>> field::mat_inv(vector<vector<double>> a){ 
    double b, f;
    f=1/mat_D(a);
    b=a[0][0];
    a[0][0]=a[1][1]*f;
    a[1][1]=b*f;
    a[0][1]=a[0][1]*f*(-1);
    a[1][0]=a[1][0]*f*(-1);
    return a;
}

void field::write_elips_to_file(vector<vector<double> > a, vector<double> mu, int Num, ofstream &out){
    double angel;
    double l1, l2; //sobstveniye znacheniya
    vector<double> vl1, vl2;
    double D;
    
    D=(a[1][1]+a[0][0])*(a[1][1]+a[0][0])-4*(a[0][0]*a[1][1]-a[1][0]*a[1][0]);
    l1=(a[1][1]+a[0][0]+sqrt(D))/2;
    l2=(a[1][1]+a[0][0]-sqrt(D))/2;
    vl1.push_back(l1-a[1][1]);
    vl1.push_back(a[0][1]);
    vl2.push_back(a[0][1]);
    vl2.push_back(a[1][1]-l1);
    if((vl1[0]>0)&&(vl1[1]<0)){
        vl1[0]=-vl1[0];
        vl1[1]=-vl1[1];
    }
    if((vl1[0]<0)&&(vl1[1]<0)){
        vl1[0]=-vl1[0];
        vl1[1]=-vl1[1];
    }
    angel=acos(vl1[0]/sqrt(vl1[0]*vl1[0]+vl1[1]*vl1[1])) * 180 / 3.14;
    
    out << mu[0] <<" " <<mu[1] <<" " << l1 <<" " << l2 <<" " <<angel<< endl;
    //out << endl;
}

void field::razmetka_for_EM(int k){
    double S;
    for(int q=0; q<countC; q++){
        for(int j=0; j<clouds[q].countP; j++){
            S=0;
            for(int i=0; i<k; i++){
                if(FC->ME.exp[i][clouds[q].points[j].NumP]>S){
                    S=FC->ME.exp[i][clouds[q].points[j].NumP];
                    clouds[q].points[j].metka=i;
                }
                cout << FC->ME.exp[i][clouds[q].points[j].NumP] <<" ";
            }
            cout << endl;
        }
    }
}

void field::write_dots_in_iteration(ofstream &out){ //zapis v fail
    for(int j=0; j<countC; j++){ //po kolichestvu oblakob
        for(int i=0; i<clouds[j].countP; i++){//po kolichestvu tochek
            out << clouds[j].points[i].x << " ";
            out << clouds[j].points[i].y << " ";
            out << clouds[j].points[i].color << endl;
            //out <<F->clouds[j].points[i].marker << endl;
        }
    }
}

void field::write_cores_to_file(vector<vector<point> > c, ofstream &out){
    for(int i=0; i<c.size(); i++){
        for(int j=0; j<c[i].size(); j++){
            c[i][j].color=FC->clasters[i].color;
            out << c[i][j].x << " ";
            out << c[i][j].y << " ";
            out << 0;
            out << endl;
        }
    }
    out << endl << endl;
}

void field::forel(vector<point *> dots, double R, int n){ //find clasters by forel, with radius - R, n times 
    zero_metka(dots);
    vector<point*> group;
    point A, priv_c;
    FC = new find_clasters;
    int k=0;
    long holop=0;
    
    ofstream out_c, out_centres, out_p;
    
    string name ="circle_forel"; //open circles file
    name =name+ to_string(n)+".txt";
    out_c.open(name);
    
    name ="centres_forel"; //open centers file
    name =name+ to_string(n)+".txt";
    out_centres.open(name);
    
    name ="dots_forel"; //open dots file
    name =name+ to_string(n)+".txt";
    out_p.open(name);
    
    vector<point> centers;
    vector<point*> ptr_centers;
    
    for(int i=0; i<dots.size(); i++){ //for every dot
        
        if(dots[i]->metka==0){
            A=*dots[i];
            group=turtle(dots, A, R);
            priv_c.x=A.x;
            priv_c.y=A.y;
            
            A=center_mass(group);
            
            while((priv_c.x!=A.x)||(priv_c.y!=A.y)){ //poka ne stabiliziruetca center
                group=turtle(dots, A, R);
                priv_c.x=A.x;
                priv_c.y=A.y;
                A=center_mass(group);
            }
            
            k++;
            
            for(int j=0; j<group.size(); j++){ //uberayem grup is mnojestva
                group[j]->metka=k; //196 43 62 67 63 8 17 22 3
                //holop=group.size()+holop;
            }
            holop=group.size()+holop;
            centers.push_back(A);
            //ptr_centers.push_back(&centers[k-1]);
        }
    }
    for(int i=0; i<centers.size(); i++){
        ptr_centers.push_back(&centers[i]);
    }
    
    for(int i=1; i<k; i++){
        FC->new_cluster();
        group.clear();
        group=find_group(i, group);
        FC->clasters[i].points=group;
    }
    FC->colorize();
    fin_cl.push_back(*FC);
    write_circle_to_file(out_c, centers, R);
    write_centers_to_file(out_centres, centers);
    write_dots_in_iteration(out_p);
    if(n>1) {forel(ptr_centers, R*2, n-1);
        cout <<"ol";
    }
}

void field::zero_metka(vector<point *> dots){
    for(int i=0; i<dots.size(); i++){
        dots[i]->metka=0;
    }
}

vector<point*> field::turtle(vector<point *> group, point c, double R){
    vector<point*> g;
    for(int i=0; i<group.size(); i++){
        if((D(*group[i],c)<R)&&(group[i]->metka==0)){ //find dots in cercle, whitch dont belong to another circle
            g.push_back(group[i]);
        }
    }
    return g;
}

vector<point*> field::find_all_points(){
    vector<point*> p;
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            p.push_back(&clouds[i].points[j]);
        }
    }
    return p;
}

void field::write_circle_to_file(ofstream &out, vector<point> c, double R){
    for(int i=0; i<c.size(); i++){
        out << c[i].x <<" " <<c[i].y <<" " << R << endl;
    }
}

vector<point*> field::find_group_in_group(vector<point *> group, int metka){
    vector<point *> res;
    for(int i=0; i<group.size(); i++){
        if(group[i]->metka==metka) res.push_back(group[i]);
    }
    return res;
}

void field::write_centers_to_file(ofstream &out, vector<point> c){
    for(int i=0; i<c.size(); i++){
        out << c[i].x <<" " <<c[i].y <<" " << 0 <<endl;
    }
}

vector<point*> field::turtle_for_all_dots(point c, double R){
    vector<point*> res;
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].countP; j++){
            if(D(clouds[i].points[j], c)<R) res.push_back(&clouds[i].points[j]);
        }
    }
    return res;
}

void field::ierarh(){
    FC = new find_clasters;
    point_numbering();
    vector<vector<double>> M;
    double min;
    int cl1, cl2;
    claster C;
    vector<double> buth;
    ofstream out_ierath, out_centers;
    out_ierath.open("ierarh_dots.txt");
    out_centers.open("ierarh_centers.txt");
    
    for(int i=0; i<countP; i++){ //put every point to claster
        FC->new_cluster();
        FC->clasters[i].points.push_back(find_point_by_number(i));
        FC->clasters[i].centr_mass=*FC->clasters[i].points[0]; //put every centermass as single point
        FC->clasters[i].Num=i; //numbering every claster
    }
    FC->clasters.erase(FC->clasters.begin() + FC->clasters.size()-1);
    FC->colorize();
    
    for(int i=0; i<FC->clasters.size(); i++){
        FC->clasters[i].centr_mass.color=FC->clasters[i].points[0]->color; //colorize every center mass like this single point
    }
    
    gen_distant_M(); //build distant matrix
    M=DM->M;
    for(int i=0; i<M.size(); i++){
        M[i][i]=-1;
    }
    
    while (FC->clasters.size()>2) {
        min=M[0][1]; cl1=0; cl2=1;
        for(int i=0; i<M.size(); i++){
            for(int j=0; j<M.size(); j++){
                if((M[i][j]<min)&&(M[i][j]!=-1)){ //find nearest clasters
                    min=M[i][j];
                    cl1=i;
                    cl2=j;
                }
            }
            //cout << "ok";
        }
        /*for(int i=0; i<M.size(); i++){
            for(int j=0; j<M.size(); j++){
                cout <<M[i][j] <<" ";
            }
            cout << endl;
        }*/
        
        C=merge_clasters(*find_claster_by_number(cl1), *find_claster_by_number(cl2)); //merge 2 clasters
        C.Num=FC->clasters.size()-2;
        
        
        FC->clasters.erase(FC->clasters.begin() + cl1); //erase priv 2 clasters
        FC->clasters.erase(FC->clasters.begin() + cl2-1);
        
        for(int i=0; i<FC->clasters.size(); i++){ //renumbering
            FC->clasters[i].Num=i;
        }
        //cout << "ok";
        for(int i=0; i<M.size(); i++){
            M[i].erase(M[i].begin()+cl1);
            M[i].erase(M[i].begin()+cl2-1);
        }
        M.erase(M.begin()+cl1);
        M.erase(M.begin()+cl2-1);
        //cout << "ok";
        /*for(int i=0; i<M.size(); i++){
            for(int j=0; j<M.size(); j++){
                cout <<M[i][j] <<" ";
            }
            cout << endl;
        }*/
        
        C.centr_mass=center_mass(C.points); //new center mass
        C.centr_mass.color=C.color;
        FC->clasters.push_back(C);
        
        buth.clear();
        for(int i=0; i<M.size(); i++){ //add distance vector to matrix
            M[i].push_back(D_clasters(*find_claster_by_number(i), C));
            buth.push_back(D_clasters(*find_claster_by_number(i), C));
        }
        buth.push_back(-1);
        M.push_back(buth);
        /*for(int i=0; i<M.size(); i++){
            for(int j=0; j<M.size(); j++){
                cout <<M[i][j] <<" ";
            }
            cout << endl;
        }*/
        //cout << "ok";
        FC->countClas=FC->clasters.size();
        write_dots_in_iteration(out_ierath);
        out_ierath << endl << endl;
        for(int i=0; i<FC->clasters.size(); i++){
            out_centers << FC->clasters[i].centr_mass.x <<" "<<FC->clasters[i].centr_mass.y <<" " <<FC->clasters[i].centr_mass.color<< endl;
        }
        out_centers  << endl << endl;
    }
  
}

claster field::merge_clasters(claster A, claster B){
    claster C;
    for(int i=0; i<A.points.size(); i++){
        C.points.push_back(A.points[i]);
    }
    for(int i=0; i<B.points.size(); i++){
        C.points.push_back(B.points[i]);
    }
    if(A.points.size()>=B.points.size()) C.color=A.color;
    else C.color=B.color;
    for(int i=0; i<C.points.size(); i++){
        C.points[i]->color=C.color;
    }
    return C;
}

double field::D_clasters(claster A, claster B){
    return D(A.centr_mass, B.centr_mass);
}

claster* field::find_claster_by_number(int n){
    for(int i=0; i<FC->clasters.size(); i++){
        if(FC->clasters[i].Num==n) return &FC->clasters[i];
    }
    return &FC->clasters[0];
}

void field::put_cloud_in_buth(int N){
    buff.B.clear();
    for(int i=0; i<clouds[N].points.size(); i++){
        buff.B.push_back(clouds[N].points[i]);
    }
}

void field::put_field_in_buth(){
    buff.B.clear();
    for(int i=0; i<countC; i++){
        for(int j=0; j<clouds[i].points.size(); j++){
            buff.B.push_back(clouds[i].points[i]);
        }
    }
}

void field::shift_buth(point A){
    buff.shift(A);
}

void field::homothety_buth(double k){
    buff.homothety(k);
}

void field::write_buffer_to_cloud(){
    cloud C;
    for(int i=0; i<buff.B.size(); i++){
        C.points.push_back(buff.B[i]);
    }
    C.Numcl=(clouds.size()+1)%1000;
    C.countP=C.points.size();
    clouds.push_back(C);
}
