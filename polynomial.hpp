#include <iostream>
#include <vector>
#include <string>
#include "calculator.hpp"
using namespace std;

class Polynomial {
protected:
  class Term {
  protected:
    int exponent;
    int coefficient;
    Term *next;
    Term(int exp, int coeff, Term *n): exponent(exp), coefficient(coeff), next(n) {}
    friend class Polynomial;
    friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
    friend Polynomial operator*(const Polynomial &p, const Polynomial &q);
    friend ostream& operator<<(ostream &out, const Polynomial &p);
  };

private:
  Term *greater; 
  number power(double x, unsigned p) {
    number result(1);
    for(int i=1; i<=p; i++) result*=x;
    return result;
  }
  static int abs(int x) {
    return x<0 ? -x : x;
  }
  void copy(const Polynomial &p) {
    for(Term *t=p.greater; t!=nullptr; t=t->next)
    addTerm(t->exponent, t->coefficient);
  }
  void purge() {
    Term *p=greater;
    while(p!=nullptr) {
      Term *q=p;
      p=p->next;
      delete q;
    }
  }

public:
  Polynomial(): greater(nullptr) {}
  Polynomial(const Polynomial &p): greater(nullptr) {copy(p);}
  ~Polynomial() {purge();}

  Polynomial &operator=(const Polynomial &p) {
    purge();
    greater=nullptr;
    copy(p);
    return *this;
  }

  void addTerm(int expon, int coeff) {
    if(greater!=nullptr) {
      if(expon<=greater->exponent) {
        Term *p;
        for(p=greater; p->next!=nullptr && p->next->exponent>expon; p=p->next);
        if(p->exponent!=expon) {
          Term *q=p->next;
          if(q==nullptr || q->exponent!=expon) {
            if(coeff!=0) {
              Term *t=new Term(expon, coeff, q);
              p->next=t;
            }
          }
          else if(q->exponent==expon) {
            q->coefficient+=coeff;
            if(q->coefficient==0) {
              Term *u=q->next;
              p->next=u;
              delete q;
            }
          }
        }
        else {
          p->coefficient+=coeff;
          if(p->coefficient==0) {
            Term *u=p->next;
            greater=u;
            delete p;
          }
        }
      }
      else {
        Term *t=new Term(expon, coeff, greater);
        greater=t;
      }
    }
    else {
      if(coeff!=0) greater=new Term(expon, coeff, nullptr);
    }
  }

  double evaluate(double x) {
    number result;
    for(Term *t=greater; t!=nullptr; t=t->next) {
      result+=power(x, t->exponent)*t->coefficient;
    }
    return result.getnumber();
  }

  friend Polynomial operator+(const Polynomial &p, const Polynomial &q) {
    if(p.greater==nullptr) {Polynomial poly(q); return poly;}
    if(q.greater==nullptr) {Polynomial poly(p); return poly;}

    Polynomial poly(q);
    for(Term *t=p.greater; t!=nullptr; t=t->next) 
    poly.addTerm(t->exponent, t->coefficient);  
    return poly;
  }
  friend Polynomial operator*(const Polynomial &p, const Polynomial &q) {
    Polynomial poly;
    if(p.greater==nullptr || q.greater==nullptr) {
      poly.addTerm(0, 0);
      return poly;
    }

    for(Term *t=p.greater; t!=nullptr; t=t->next) {
      for(Term *u=q.greater; u!=nullptr; u=u->next) {
        poly.addTerm(t->exponent+u->exponent, t->coefficient*u->coefficient);
      }
    }
    return poly;
  }

  friend ostream& operator<<(ostream &out, const Polynomial &p) {
    if(p.greater!=nullptr) {
      for(Term *t=p.greater; t!=nullptr; t=t->next) {        
        if(t->coefficient<0) out<<"- ";
        else if(t->coefficient>0 && t!=p.greater) out<<"+ ";
        if(abs(t->coefficient)!=1 || t->exponent==0) out<<abs(t->coefficient);
        if(t->exponent>0) out<<"x";
        if(t->exponent>1) out<<"^"<<t->exponent;
        if(t->next!=nullptr) cout<<" ";
      }
    }
    else out<<"0";
    return out;
  }
};