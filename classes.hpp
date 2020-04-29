#include <iostream>
#include <vector>
#include <string>
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
  int power(double x, unsigned p) {
    double result=1;
    for(int i=1; i<=p; i++) result*=x;
    return result;
  }
  static int abs(int x) {
    return x<0 ? -x : x;
  }
  void opp(bool &cond) {
    if(cond) cond=false;
    else cond=true;
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
  void assign(vector<int> &v, int x) {
    vector<int> temp; v.clear(); bool flag=false;
    if(x<0) flag=true; x=abs(x);
    if(x==0) temp.push_back(0);
    for(; x!=0; x/=10) temp.push_back(x%10);
    for(auto i=temp.rbegin(); i!=temp.rend(); ++i) v.push_back(*i);
    if(flag) v[0]=-v[0];
  }
  void fix(vector<int> &v1, vector<int> &v2) {
    if(v1.size()<v2.size()) v1.swap(v2); 
  }
  bool greaterv(vector<int>::iterator i, vector<int>::iterator endi, vector<int>::iterator j, vector<int>::iterator endj) {
    if(distance(i, endi)==distance(j, endj)) {    
      if(*i>*j) return true;
      else if(*i<*j) return false;
      else return greaterv(i+1, endi, j+1, endj);
    }
    else {
      if(*i<0) return false;
      if(*j<0) return true;
      return distance(i, endi)>distance(j, endj);
    }
  }
  void substract(vector<int> &vmain, vector<int> &vsub) {
    bool flag=false;
    fix(vmain, vsub);
    if(!greaterv(vmain.begin(), vmain.end(), vsub.begin(), vsub.end())) vmain.swap(vsub);
    vector<int> absvmain(vmain), absvsub(vsub);
    absvmain[0]=abs(absvmain[0]); absvsub[0]=abs(absvsub[0]);
    if(!greaterv(absvmain.begin(), absvmain.end(), absvsub.begin(), absvsub.end())) {flag=true; vmain.swap(vsub);}
    vmain[0]=abs(vmain[0]); vsub[0]=abs(vsub[0]);

    vector<int> temp;
    int c=0;
    vector<int>::reverse_iterator i=vmain.rbegin();
    for(vector<int> ::reverse_iterator j=vsub.rbegin(); j!=vsub.rend(); j++, i++) {
      int sum=*i-(*j)-c; c=0;
      if(sum<0) {sum+=10; c=1;}
      temp.push_back(sum);
    }
    for(; i!=vmain.rend(); i++) {
      int sum=*i-c; c=0;
      if(sum<0) {sum=10+sum; c=1;}
      temp.push_back(sum);
    }
    while(*(temp.rbegin())==0 && temp.size()>1) temp.pop_back();
    vmain.clear();
    for(vector<int>::reverse_iterator j=temp.rbegin(); j!=temp.rend(); j++) {
      vmain.push_back(*j);
    }
    if(flag) vmain[0]=-vmain[0];
  }
  void add(vector<int> &vmain, vector<int> &vsub) {
    bool flag=false;
    if(vmain[0]<0 && vsub[0]<0) {
      flag=true;
      vmain[0]=abs(vmain[0]); 
      vsub[0]=abs(vsub[0]);
      vector<int> temp;
      fix(vmain, vsub);
      vector<int>::reverse_iterator i=vmain.rbegin();
      int c=0;
      for(vector<int>::reverse_iterator j=vsub.rbegin(); j!=vsub.rend(); j++, i++) {
        int sum=c+(*i)+(*j);
        temp.push_back(sum%10);
        c=sum/10;
      }
      for(; i!=vmain.rend(); i++) {
        int sum=*i+c;
        temp.push_back(sum%10);
        c=sum/10;
      }
      if(c!=0) temp.push_back(c);
      vmain.clear();
      for(vector<int>::reverse_iterator j=temp.rbegin(); j!=temp.rend(); j++) {
        vmain.push_back(*j);
      }
      if(flag) vmain[0]=-vmain[0];
    }
    else if(vmain[0]<0 || vsub[0]<0) substract(vmain, vsub);
    else { 
      vector<int> temp;
      fix(vmain, vsub);
      vector<int>::reverse_iterator i=vmain.rbegin();
      int c=0;
      for(vector<int>::reverse_iterator j=vsub.rbegin(); j!=vsub.rend(); j++, i++) {
        int sum=c+(*i)+(*j);
        temp.push_back(sum%10);
        c=sum/10;
      }
      for(; i!=vmain.rend(); i++) {
        int sum=*i+c;
        temp.push_back(sum%10);
        c=sum/10;
      }
      if(c!=0) temp.push_back(c);
      vmain.clear();
      for(vector<int>::reverse_iterator j=temp.rbegin(); j!=temp.rend(); j++) {
        vmain.push_back(*j);
      }
      if(flag) vmain[0]=-vmain[0];
    }
  }
  void multiply(vector<int> &v, int x) {
    bool flag=false;
    if(x<0) opp(flag);
    if(v[0]<0) opp(flag);
    v[0]=abs(v[0]); x=abs(x);

    vector<int> temp;
    int c=0;
    for(vector<int>::reverse_iterator i=v.rbegin(); i!=v.rend(); i++) {
      int sum=*i*x+c;
      temp.push_back(sum%10);
      c=sum/10;
    }
    for(; c!=0; c/=10) temp.push_back(c%10);
    v.clear();
    for(vector<int>::reverse_iterator i=temp.rbegin(); i!=temp.rend(); i++) {
      v.push_back(*i);
    }
    if(flag) v[0]=-v[0];
  }
  double print(vector<int> v) {
    if(v.size()>6) {
      int j=1;
      for(auto i=v.begin(); j<=6; j++, i++) {
        cout<<*i;
        if(i==v.begin()) cout<<".";
      }
      if(v.size()-1<10) cout<<"e+0";
      else cout<<"e+";
      return v.size()-1;
    }
    else {
      for(auto i=v.begin(); (i)!=v.end(); i++) {
        if((i+1)==v.end()) return *i;
        cout<<*i;
      }
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
    vector<int> main, result;
    assign(result, 0);
    for(Term *t=greater; t!=nullptr; t=t->next) {
      if(t->exponent!=0) assign(main, x); 
      else assign(main, 1);
      for(int i=1; i<t->exponent; ++i) {
        multiply(main, x);
      }
      multiply(main, t->coefficient);
      add(result, main);
    }

    int a[result.size()];
    for(int i=0; i<result.size(); i++) a[i]=result[i];
    string total;
    for(int i=0; i<result.size(); ++i) {
      string temp=to_string(a[i]);
      total.append(temp);
    }
    string::size_type sz;
    return stod(total, &sz);
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