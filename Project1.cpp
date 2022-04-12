#include <iostream>
#include <vector>
using namespace std;


class Animal {
public:
	virtual void speak() const = 0;
};

class Cat :public Animal {
public:
	virtual void speak() const override {
		cout << "야옹" << endl;
	}
};

class Dog :public Animal{
public:
	virtual void speak() const override {
		cout << "멍" << endl;
	}
};

class Cow :public Animal{
public:
	virtual void speak() const override {
		cout << "음머" << endl;
	}
};

class Zoo {
private:
	/*Cat cat;
	Dog dog;
	Cow cow;*/
	vector<Animal*>array;

public:
	void addAnimal(Animal* const pAnimal) {
		//pAnimal++;	포인터 변수를 이용해서 포인터를 변경하면 컴파일 오류 발생하게 설정(const)
		array.push_back(pAnimal);
	}
	void speak() {
		/*Cat.cat_speak();
		Dog.dog_speak();
		Cow.cow_speak();*/
		for (const auto& pAnimal : array) {
			pAnimal->speak();
		}
	}
};

int add(const int a, const int b)
{
	return a + b;
}

int sub(const int a, const int b)
{
	return a - b;
}

typedef int (*FP_CALC)(const int, const int);
FP_CALC calc;	//포인터 변수명

class Calc {
public:
	virtual int calc(const int a, const int b) = 0;
};

class AddCalc:public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a + b;
	}
};

class SubCalc :public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a - b;
	}
};

class MulCalc :public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a * b;
	}
};

int MyCalc(Calc& obj, const int a, const int b) {
	return obj.calc(a, b);
}

bool InitInstance(Zoo* pZoo) {
	Cat cat;
	Dog dog;
	Cow cow;


	pZoo->addAnimal(&dog);
	pZoo->addAnimal(&cat);
	pZoo->addAnimal(&cow);

	return true;
}

bool Run(Zoo* pZoo) {
	pZoo->speak();
	return true;
}

bool ExitInstance(Zoo* pZoo) {
	return true;
}

int main(int argc, char** argv)
{
	int a, b;
	int sum;

	int c, d;
	int e, f;

	typedef int (*p)(const int, const int);	//함수 포인터 선언
	//typedef -> 변수명을 새로운 type(형)으로 정의



	//debug-> 함수로 정상 동작함 : runtime시 계산함, 디버깅 정보가 결과물 안에 포함됨
	//release -> 최적화로 정적코드로 동작함 sum=30
	//생성(exe 만들기) : 일반적인 경우 debug 모드가 exe 생성시 좀더 빠르다
	//실행 : 일반적으로 release 모드의 결과물이 빠르다
	//크기 : debug 모드가 크다, release 모드가 보통 debug 모드 대비 1/4 정도 작다
	//sum = add(a, b);	//런타임 코드 계산
	//일반화 / 특별화
	//pointer -> indirect -> virtual function, 의존성 역전, ocp
	//framework


	//sum = 10 + 20;	//특별화
	//sum = a + b;		//일반화
	
	/*sum = a + b;
	sum = c + d;
	sum = e + f;*/		//변수명에 제약을 받음, 특별화


	int* p1 = &a;
	int* p2 = &b;
	sum = *p1 + *p2;	//대상을 주소로 봄, 일반화(변수명이라는 대상의 제약을 없애기 위한것)
	
	p1 = &c;
	p2 = &d;
	sum = *p1 + *p2;

	p1 = &e;
	p2 = &f;
	sum = *p1 + *p2;	//data pointer
	
	sum = add(a, b);

	int result = 0;

	calc = add;
	result = calc(a, b);		

	calc = sub;
	result = calc(a, b);	//함수포인터(function pointer)를 활용한 일반화 - 런타임에 실행되므로 indirect, 
							//더 오래 걸리지만 기존의 로직이 변경되지 않아도 된다는 장점


	Calc* pCalc = new AddCalc();
	result = pCalc->calc(a, b);
	delete pCalc;

	pCalc = new SubCalc();
	result = pCalc->calc(a, b);
	delete pCalc;

	AddCalc addCalc;
	Calc& objA = addCalc;
	result = objA.calc(a, b);

	SubCalc subCalc;
	Calc& objB = subCalc;
	result = objB.calc(a, b);

	


	result = MyCalc(addCalc, 10, 20);
	result = MyCalc(subCalc, 10, 20);


	//새롭게 추가된 부분, MyCalc 변경되는것 없음, 새로운 기능 자연스럽게 실행할 수 있음	
	//OCP
	MulCalc objC;
	result = MyCalc(objC, 10, 20);

	
	vector<Calc*> arr = { &addCalc, &subCalc, &objC };
	for (auto& pCalc : arr) {
	
		MyCalc(*pCalc, a, b);
	}
	/*for (int i = 0; i < arr.size(); i++) {
		MyCalc(*arr[i], a, b);
	}*/

	cout << a << " + " << b << " = " << sum << endl;

	Zoo zoo;

	InitInstance(&zoo);

	Run(&zoo);

	ExitInstance(&zoo);

	return 0;
}