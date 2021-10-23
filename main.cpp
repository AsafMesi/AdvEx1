#include <iostream>
#include "anomaly_detection_util.h"

//int main() {
//    float  arr1[] = {10.5, 9.2, 8.1, 7.6, 6.2};
//    float arr2[] = {1.2, 2.1, 3.1, 4.6, 5.2};
//
//    // should be =~ -2.1108
//    std :: cout << cov(arr1, arr2, 5) << std :: endl;
//
//    // should be =~ 2.1176
//    std :: cout << var(arr1, 5) << std :: endl;
//
//    // should be =~ 2.2344
//    std :: cout << var(arr2, 5) << std :: endl;
//
//    // should be =~ -0.970386...
//    std :: cout << pearson(arr1, arr2, 5) << std :: endl;

using namespace std;

bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
	const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

	Point* ps[N];
	for(int i=0;i<N;i++)
		ps[i]=new Point(x[i],y[i]);

	Line l=linear_reg(ps,N);
	Point p(4,8);

	float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
	float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};

    for (int i = 0; i < 7;i++) {
        cout << v[i] << ", ";
    }

    cout << "\n";

	for(int i=0;i<7;i++)
		if(wrong(v[i],e[i]))
			cout<<"error for check "<<i<<" (-14)"<<endl;


	for(int i=0;i<N;i++)
		delete ps[i];

	cout<<"done"<<endl;
	return 0;
}
