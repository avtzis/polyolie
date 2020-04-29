#include <iostream>
#include "classes.hpp"
using namespace std;

/*int main() {
  Polynomial p;
  p.addTerm(2, 1);
  p.addTerm(3, 3);
  p.addTerm(4, 1);
  p.addTerm(1, -1);
  p.addTerm(0, -2);
  p.addTerm(3, -1);
  p.addTerm(4, 1);
  p.addTerm(0, 0);
  p.addTerm(4, -2);
  cout<<"p(x) = "<<p<<endl;
  cout<<"p(2) = "<<p.evaluate(100)<<endl;

  Polynomial q;
  q.addTerm(2, 1);
  q.addTerm(1, 1);
  cout<<"(p+q)(x) = "<<p+q<<endl;

  Polynomial w;
  w.addTerm(2, -1);
  w.addTerm(1, -1);
  cout<<"w(x) = "<<w<<endl;
  cout<<"q(x) = "<<q<<endl;
  cout<<"(q+w)(x) = "<<q+w<<endl; 

  Polynomial v;
  cout<<"v(x) = "<<v<<endl;
  cout<<"(w+v)(x) = "<<w+v<<endl;  
  cout<<"(v+w)(x) = "<<v+w<<endl; 

  cout<<"(q*w)(x) = "<<q*w<<endl;
  cout<<"(v*p)(x) = "<<v*p<<endl;
  cout<<"(p*v)(x) = "<<p*v<<endl;

  Polynomial pol1;
  pol1.addTerm(3, 1);
  cout<<"pol1(x) = "<<pol1<<endl;
  Polynomial pol2=pol1;
  pol2.addTerm(0, 5);
  cout<<"pol2(x) = "<<pol2<<endl;
  cout<<"(pol1+pol2)(3) = "<<(pol1+pol2).evaluate(3)<<endl; 

  Polynomial a, b;
  a.addTerm(2, 1);
  a.addTerm(1, 1);
  b.addTerm(2, 0);
  cout<<"a(x) = "<<a<<endl;
  cout<<"b(x) = "<<b<<endl;
  cout<<"(a*b)(x) = "<<a*b<<endl;
  cout<<"(a*b)(5) = "<<(a*b).evaluate(5)<<endl;
}

int main() {
	Polynomial p;
	p.addTerm(1, 3);
	p.addTerm(2, 1);
	p.addTerm(0, -1);
	
	Polynomial q(p);
	q.addTerm(1, -3);
	
	cout<<"P(x) = "<<p<<endl;
	cout<<"P(1) = "<<p.evaluate(1)<<endl;
	cout<<"Q(x) = "<<q<<endl;
	cout<<"Q(1) = "<<q.evaluate(1)<<endl;
	cout<<"(P+Q)(x) = "<<p+q<<endl;
	cout<<"(P*Q)(x) = "<<p*q<<endl;
}*/

/*int main() {
  Polynomial p;
  p.addTerm(10, 1);
  p.addTerm(6, -22);
  p.addTerm(2, 4);
  cout<<"P(x) = "<<p<<endl;

  Polynomial q;
  q.addTerm(2, -9);
  q.addTerm(1, 8);
  q.addTerm(0, 7);
  cout<<"Q(x) = "<<q<<endl;

  cout<<"(P+Q)(x) = "<<p+q<<endl;
  cout<<"(P*Q)(x) = "<<p*q<<endl;

  cout<<"(P*Q)(0) = "<<(p*q).evaluate(0)<<endl;
  cout<<"(P*Q)(1) = "<<(p*q).evaluate(1)<<endl;
  cout<<"(P*Q)(3) = "<<(p*q).evaluate(3)<<endl;
  cout<<"(P*Q)(-8) = "<<(p*q).evaluate(-8)<<endl;
}*/

/*int main() {
  Polynomial p;
  p.addTerm(1, 6);
  p.addTerm(0, 5);

  cout<<"P(x) = "<<p<<endl<<endl;
  //cout<<"P(0) = "<<p.evaluate(0)<<endl;
  //cout<<"P(-1) = "<<p.evaluate(-1)<<endl;
  cout<<"P(-25) = "<<p.evaluate(-25)<<endl;
  //cout<<"P(44) = "<<p.evaluate(44)<<endl;
}*/

/*int main() {
  Polynomial p;
  p.addTerm(1, 1);
  p.addTerm(0, -1);
  cout<<"P(x) = "<<p<<endl;
  cout<<"P(0) = "<<p.evaluate(0)<<endl;
  cout<<"P(1) = "<<p.evaluate(1)<<endl;
  cout<<"P(15) = "<<p.evaluate(15)<<endl;
  cout<<"P(1500) = "<<p.evaluate(1500)<<endl;

  Polynomial q;
  q.addTerm(1, 1);
  q.addTerm(0, 1);
  cout<<"Q(x) = "<<q<<endl;
}*/

int main() {
  Polynomial p;
  p.addTerm(9, 9);
  p.addTerm(8, -18);
  p.addTerm(5, 51);
  p.addTerm(4, -102);
  p.addTerm(3, -7);
  p.addTerm(2, 14);
  p.addTerm(1, 456);
  p.addTerm(0, -912);

  cout<<"P(x) = "<<p<<endl;
  cout<<"P(2) = "<<p.evaluate(2)<<endl;
  cout<<"P(-3) = "<<p.evaluate(-3)<<endl;
}