#include <iostream>
using namespace std;


class INPUT {
protected:
	int n = 0;
public:
	virtual int input() = 0;
};

class INT : public INPUT {		// 분모가 0일때 제외
public:
	virtual int input() override {
		int a;

		n++;		
		do {
			cout << " 입력 : ";
			cin >> a;
		} while (a == 0 && n > 1);
		
		return a;
	}
};

//class CHAR : public INPUT {			// 문자 배제 어떻게?
//	virtual char* input() override {
//		int a;
//		char b[10];
//
//		n++;
//		do {
//			cout << " 입력 : ";
//			cin.getline(b,10);
//		} while (a == 0 && n > 1);
//
//		return b;
//	}
//};


class Division {
public:
	void div(const int A, const int B) {
		cout << A << " / " << B << " = " << (double)(A / B) << endl;
	}
};

int main()
{
	int A, B;
	
	INT in;

	A = in.input();
	B = in.input();
	
	Division Div;
	Div.div(A, B);
	
}