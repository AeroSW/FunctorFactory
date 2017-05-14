#include "FunctorFactory.h"
#include <iostream>

using namespace std;

struct derived_1 : public Base{
	derived_1(int i, int j, float f){
		cout << "Derived 1:\t" << i * j + f << endl;
	}
};
FF_MACRO(name_1, derived_1, int,int,float);

struct derived_2 : public Base{
	derived_2(int i, int j){
		cout << "Derived 2:\t" << i + j << endl;
	}
};
FF_MACRO(name_2, derived_2, int,int);

int main(){
	derived_1 * d_1 = static_cast<derived_1*>(FunctorFactory::createObject<int, int, float>("name_1", 8, 8, 3.0));
	if(d_1 == nullptr) cout << "The function being requested must either have different parameters or a different key." << endl;
	else{
		delete d_1;
	}
	return 0;
}

