#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minCircle.h"
#include "anomaly_detection_util.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


Point** generate(Point center,int R, size_t size){
    Point** p =new Point*[size];
    for(size_t i=0;i<size;i++){

        // r is a number in range: 1 - R.
        float r=1+rand()%R;

        // calculate pi * x/180 -> x in range: 0-359 this is the degree of r
        float a=3.14159*(rand()%360)/180;

        // we generate point in a way that makes sure -r <= center.x, center.y <=r
        // which means that it will be inside the given circle
        float x=center.x+r*cos(a);
        float y=center.y+r*sin(a);
        p[i]=new Point(x,y);
    }
    return p;
}


void runTests(){

}

int main(){
    runTests();
    srand (time(NULL));
    const size_t N=250;

    // choose randomize radius in range: 10 - 1009
    float R=10+rand()%1000;

    // choose randomize center point in range: -500 - 500
    float cx=-500+rand()%1001;
    float cy=-500+rand()%1001;

    // generate points inside this circle
    Point** ps=generate(Point(cx,cy),R,N);

    // your working copy
    Point** ps_copy=new Point*[N];
    for(size_t i=0;i<N;i++)
        ps_copy[i]=new Point(ps[i]->x,ps[i]->y);

    auto start = high_resolution_clock::now();
    Circle c=findMinCircle(ps_copy,N);
    auto stop = high_resolution_clock::now();

    // we already know that R is the radius of the MEC, therfore, if our circle's radius is bigger, we are wrong.
    if((int)c.radius>(int)R)
        cout<<"you need to find a minimal radius (-40)"<<endl;

    bool covered=true;
    for(size_t i=0;i<N && covered;i++){
        float x2=(c.center.x-ps[i]->x)*(c.center.x-ps[i]->x);
        float y2=(c.center.y-ps[i]->y)*(c.center.y-ps[i]->y);
        float d=sqrt(x2+y2);
        if(d>c.radius+1)
            covered=false;
    }
    if(!covered)
        cout<<"all points should be covered (-45)"<<endl;

    auto duration = duration_cast<microseconds>(stop - start);
    int stime=duration.count();
    cout<<"your time: "<<stime<<" microseconds"<<endl;
    if(stime>3000){
        cout<<"over time limit ";
        if(stime<=3500)
            cout<<"(-5)"<<endl;
        else if(stime<=4000)
            cout<<"(-8)"<<endl;
        else if(stime<=6000)
            cout<<"(-10)"<<endl;
        else cout<<"(-15)"<<endl;
    }

    for(size_t i=0;i<N;i++){
        delete ps[i];
        delete ps_copy[i];
    }
    delete[] ps;
    delete[] ps_copy;

    cout<<"done"<<endl;
    return 0;
}

//
// Created by DanMa on 11/12/2021.
//

