// Почечура Артемий Андреевич

// М8О-206Б-20

// Вариант 10: создать класс Angle для работы с углами на плоскости, задаваемыми величиной в градусах и минутах. 
// Обязательно должны быть реализованы: перевод в радианы, приведение к диапазону 0–360, сложение и вычитание углов, 
// деление углов, получение значений тригонометрических функций, сравнение углов.

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
 
using namespace std;

const double pi=atan(1.0)*4;
 
class Angle{
	
private:

	double degree, minute;

public:

	Angle(){
		degree=0;
		minute=0;
	}

	Angle(double new_degree, double new_minute){
		degree=new_degree;
		minute=new_minute;
	}

	double get_degree(){
		return degree;
	}

	double get_minute(){
		return minute;
	}

	void set_degree(double a){
		degree=a;
	}

	void set_minute(double a){
		minute=a;
	}

	double degree_to_radian(){
		double b;
		if(get_degree()>0){
			b=get_degree()+get_minute()/60;
		} else {
			b=get_degree()-get_minute()/60;
		}
		return pi*b/180;
	}

	void bringing_to_0_360(){
		Angle b;
		int q,c,l;
		if(get_degree()<0){
			set_minute(get_minute()*(-1));
		}
		q=get_minute()/60;
		set_degree(get_degree()+q);
		c=get_degree()/360;
		b.set_minute(get_minute()-q*60);
		if(get_degree()>=0){
			b.set_degree(get_degree()-c*360);
		} else {
			b.set_degree(get_degree()+(c*(-1)+1)*360);
			if(b.get_minute()!=0){
				b.set_minute(60+b.get_minute());
				b.set_degree(b.get_degree()-1);
			}
		}
		set_degree(b.get_degree());
		set_minute(b.get_minute());
	}

	double Sin(){
		return sin(degree_to_radian());
	}

	double Cos(){
		return cos(degree_to_radian());
	}

	double Tan(){
		return Sin()/Cos();
	}

	double Arctan(){
		return Cos()/Sin();
	}
};

Angle operator+(Angle a, Angle b){
	if(a.get_degree()<0){
		a.set_minute(a.get_minute()*(-1));
	}
	if(b.get_degree()<0){
		b.set_minute(b.get_minute()*(-1));
	}
	double c=a.get_degree()*60+a.get_minute()+b.get_degree()*60+b.get_minute();
	int C=c/60;
	double m=c-C*60;
	Angle g((c-m)/60,m);
	if(g.get_degree()<0){
		g.set_minute(g.get_minute()*(-1));
	}
	return g;
}

Angle operator-(Angle a, Angle b){
	if(a.get_degree()<0){
		a.set_minute(a.get_minute()*(-1));
	}
	if(b.get_degree()<0){
		b.set_minute(b.get_minute()*(-1));
	}
	double c=a.get_degree()*60+a.get_minute()-b.get_degree()*60-b.get_minute();
	int C=c/60;
	double m=c-C*60;
	Angle g((c-m)/60,m);
	if(g.get_degree()<0){
		g.set_minute(g.get_minute()*(-1));
	}
	return g;
}

Angle operator/(Angle a, int b){
	if(a.get_degree()<0){
		a.set_minute(a.get_minute()*(-1));
	}
	int y=(a.get_minute())/60;
	Angle c((a.get_degree()+y)/b, (a.get_minute()-y*60)/b);
	return c;
}

bool operator>(Angle a, Angle b){
	double A=a.degree_to_radian();
	double B=b.degree_to_radian();
	if(A>B){
		return true;
	}
	return false;
}

bool operator==(Angle a, Angle b){
	double A=a.degree_to_radian();
	double B=b.degree_to_radian();
	if(A==B){
		return true;
	}
	return false;
}

// минуты не могут быть отрицательными и зависят от знака градусов

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	Angle a1,a2;
	double b,c,d,e,f;
	cout << "Select the values of first angle:\n";
	if(!(cin >> b >> c)){
		cout << "Wrong values";
		return 0;
	}
	cout << "Select the values of second angle:\n";
	if(!(cin >> d >> e)){
		cout << "Wrong values";
		return 0;
	}
	cout << "Select constant:\n";
	if(!(cin >> f)){
		cout << "Wrong values";
		return 0;
	}
	a1.set_degree(b);
	a1.set_minute(c);
	a2.set_degree(d);
	a2.set_minute(e);
	cout << "Shifting the first angle in range 0-360:\n";
	Angle A=a1;
	A.bringing_to_0_360();
	cout << A.get_degree() << " " << A.get_minute() << "\n";
	cout << "Shifting the first angle in radian:\n";
	A=a1;
	cout << A.degree_to_radian() << "\n";
	cout << "Sum and difference of angles:\n";
	Angle B;
	A=a1+a2;
	B=a1-a2;
	cout << A.get_degree() << " " << A.get_minute() << "\n";
	cout << B.get_degree() << " " << B.get_minute() << "\n";
	cout << "Division of first angle and constant:\n";
	A=a1/f;
	cout << A.get_degree() << " " << A.get_minute() << "\n";
	cout << "Trigonometric functions of first angle:\n";
	cout << a1.Sin() << " " << a1.Cos() << " " << a1.Tan() << " " << a1.Arctan() << "\n";
	cout << "Comparison of angles:\n";
	if(a1>a2){
		cout << " >";
	} else if (a1==a2){
		cout << " =";
	} else {
		cout << " <";
	}
}