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
		cout << "�߿�" << endl;
	}
};

class Dog :public Animal{
public:
	virtual void speak() const override {
		cout << "��" << endl;
	}
};

class Cow :public Animal{
public:
	virtual void speak() const override {
		cout << "����" << endl;
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
		//pAnimal++;	������ ������ �̿��ؼ� �����͸� �����ϸ� ������ ���� �߻��ϰ� ����(const)
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
FP_CALC calc;	//������ ������

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

	typedef int (*p)(const int, const int);	//�Լ� ������ ����
	//typedef -> �������� ���ο� type(��)���� ����



	//debug-> �Լ��� ���� ������ : runtime�� �����, ����� ������ ����� �ȿ� ���Ե�
	//release -> ����ȭ�� �����ڵ�� ������ sum=30
	//����(exe �����) : �Ϲ����� ��� debug ��尡 exe ������ ���� ������
	//���� : �Ϲ������� release ����� ������� ������
	//ũ�� : debug ��尡 ũ��, release ��尡 ���� debug ��� ��� 1/4 ���� �۴�
	//sum = add(a, b);	//��Ÿ�� �ڵ� ���
	//�Ϲ�ȭ / Ư��ȭ
	//pointer -> indirect -> virtual function, ������ ����, ocp
	//framework


	//sum = 10 + 20;	//Ư��ȭ
	//sum = a + b;		//�Ϲ�ȭ
	
	/*sum = a + b;
	sum = c + d;
	sum = e + f;*/		//������ ������ ����, Ư��ȭ


	int* p1 = &a;
	int* p2 = &b;
	sum = *p1 + *p2;	//����� �ּҷ� ��, �Ϲ�ȭ(�������̶�� ����� ������ ���ֱ� ���Ѱ�)
	
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
	result = calc(a, b);	//�Լ�������(function pointer)�� Ȱ���� �Ϲ�ȭ - ��Ÿ�ӿ� ����ǹǷ� indirect, 
							//�� ���� �ɸ����� ������ ������ ������� �ʾƵ� �ȴٴ� ����


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


	//���Ӱ� �߰��� �κ�, MyCalc ����Ǵ°� ����, ���ο� ��� �ڿ������� ������ �� ����	
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