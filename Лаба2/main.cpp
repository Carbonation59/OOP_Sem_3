// ѕочечура јртемий јндреевич

// ћ8ќ-206Ѕ-20

// Ћабораторна€ работа є2

// ¬ариант 10: создать класс Angle дл€ работы с углами на плоскости, задаваемыми величиной в градусах и минутах. 
// ќб€зательно должны быть реализованы: перевод в радианы, приведение к диапазону 0Ц360, сложение и вычитание углов, 
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

	double get_degree() const{
		return degree;
	}

	double get_minute() const{
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
		set_degree(get_degree()+q);                           //получаем чистые градусы
		c=get_degree()/360;
		b.set_minute(get_minute()-q*60);                      //получаем чистые минуты
		if(get_degree()>=0){
			b.set_degree(get_degree()-c*360);
		} else {
			b.set_degree(get_degree()+(c*(-1)+1)*360);        //т.к. числа отрицательные в данном случае, делаем ещЄ один лишний круг
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
	double c=a.get_degree()*60+a.get_minute()+b.get_degree()*60+b.get_minute();  // переводим всЄ в минуты
	int C=c/60;                                                                  // минуты в градусы
	double m=c-C*60;                                                             // остаток минут
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
	if(b!=0){
		if(a.get_degree()<0){
			a.set_minute(a.get_minute()*(-1));
		}
		int y=(a.get_minute())/60;
		Angle c((a.get_degree()+y)/b, (a.get_minute()-y*60)/b);
		return c;
	} else {
		throw invalid_argument("Error: Division on zero\n");
	}
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

ostream& operator <<(ostream& stream, const Angle& a) {
	cout << a.get_degree() << " " << a.get_minute();
	return stream;
}

istream& operator >>(istream& stream, Angle& a) {
	double b,c;
	if(!(cin >> b >> c)){
		throw invalid_argument("Error: Wrong values");
	} else {
		a.set_degree(b);
		a.set_minute(c);
	}
	return stream;
}

// минуты не могут быть отрицательными и завис€т от знака градусов

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	Angle a1,a2;
	double b,c,d,e,f;
	int N;
	cout << "Select the number of tests:\n";
	if(!(cin >> N)){
		cout << "Error: Wrong values\n";
	}
	for(int i=0;i<N;i++){
		try{
			cout << "\nSelect the values of first angle:\n";
			cin >> a1;
			cout << "Select the values of second angle:\n";
			cin >> a2;
			cout << "Select constant:\n";
			if(!(cin >> f)){
				cout << "Wrong values";
				continue;
			}
			Angle A,B;
			cout << "Shifting the first angle in range 0-360:\n";
			A=a1;
			A.bringing_to_0_360();
			cout << A << "\n";
			cout << "Shifting the first angle in radian:\n";
			A=a1;
			cout << A.degree_to_radian() << "\n";
			cout << "Sum and difference of angles:\n";
			A=a1+a2;
			B=a1-a2;
			A.bringing_to_0_360();
			B.bringing_to_0_360();
			cout << A << "\n";
			cout << B << "\n";
			cout << "Division of first angle and constant:\n";
			A=a1/f;
			A.bringing_to_0_360();
			cout << A << "\n";
			cout << "Trigonometric functions of first angle:\n";
			cout << a1.Sin() << " " << a1.Cos() << " " << a1.Tan() << " " << a1.Arctan() << "\n";
			cout << "Comparison of angles:\n";
			a1.bringing_to_0_360();
			a2.bringing_to_0_360();
			if(a1>a2){
				cout << "First angle larger than second angle\n";
			} else if (a1==a2){
				cout << "Angles is equal\n";
			} else {
				cout << "First angle smaller than second angle\n";
			}
		} catch(invalid_argument const& arg){
			cout << arg.what() << "\n";
			return -1;
		}
	}
	return 0;
}