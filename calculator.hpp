#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class number { //consts?????
private:
  string num;

  static int abs(int x) {return x<0 ? -x : x;}
  static bool negative(const vector<int> &v) {return v[0]<0;}
  static bool greater(vector<int>::iterator i, vector<int>::iterator endi, vector<int>::iterator j, vector<int>::iterator endj) {
    if(distance(i, endi)==distance(j, endj)) {
      if(i==endi) return false;
      if(*i>*j) return true;
      else if(*i<*j) return false;
      else return greater(i+1, endi, j+1, endj);
    }
    else {
      if(*i<0 && *j<0) return distance(i, endi)<distance(j, endj);
      if(*i<0) return false;
      if(*j<0) return true;
      return distance(i, endi)>distance(j, endj);
    }
  }
  static bool greater(vector<int> &v1, vector<int> &v2) {
    return greater(v1.begin(), v1.end(), v2.begin(), v2.end());
  }
  static bool fix(vector<int> &v1, vector<int> &v2, bool &flag) {
    if(!(negative(v1) || negative(v2))) {
      if(greater(v2, v1)) v1.swap(v2);
      return false;
    }
    else if((negative(v1) && negative(v2))) {
      v1[0]=abs(v1[0]); v2[0]=abs(v2[0]);
      flag=true;
      if(greater(v2, v1)) v1.swap(v2);
      return false;
    }
    else {
      if(greater(v2, v1)) v1.swap(v2);
      v1[0]=abs(v1[0]); v2[0]=abs(v2[0]);
      if(greater(v2, v1)) {
        flag=true;
        v1.swap(v2);
      }
      return true;
    }
  }
  
  static vector<int> assign(string n) {
    vector<int> v; bool flag=false;
    if(n.front()=='-') {flag=true; n.erase(n.begin());}
    while(n.front()=='0' && n.size()>1) n.erase(n.begin());
    for(size_t pos=0; pos<n.size(); pos++) v.push_back(stoi(n.substr(pos, 1)));
    if(flag) v[0]=-v[0];
    return v;
  }
  static vector<int> assign_negative(string n) {
    if(n.front()=='-') return assign(n.erase(0, 1));
    else return assign(n.insert(0, "-"));
  }
  static vector<int> reverse_assign(const vector<int> &v) {
    vector<int> result;
    for(auto i=v.rbegin(); i!=v.rend(); ++i) result.push_back(*i);
    return result;
  }

  static vector<int> add(vector<int> v1, vector<int> v2) { 
    vector<int> result;
    bool aggr=true, sign=false;
    if(fix(v1, v2, sign)) {aggr=false; result=substract(v1, v2);}
    if(aggr) {
      vector<int> temp; int c=0;
      vector<int>::reverse_iterator i=v1.rbegin();
      for(auto j=v2.rbegin(); j!=v2.rend(); i++, j++) {
        int semi=*i+(*j)+c;
        temp.push_back(semi%10);
        c=semi/10;
      }
      for(; i!=v1.rend(); i++) {
        int semi=*i+c;
        temp.push_back(semi%10);
        c=semi/10;
      }
      if(c!=0) temp.push_back(c);
      result=reverse_assign(temp);
    }
    if(sign) result[0]=-result[0];
    return result;
  }
  static vector<int> substract(vector<int> &v1, vector<int> &v2) {
    vector<int> temp; int c=0;
    vector<int>::reverse_iterator i=v1.rbegin();
    for(auto j=v2.rbegin(); j!=v2.rend(); i++, j++) {
      int semi=*i-(*j)-c; c=0;
      if(semi<0) semi+=10, c=1;
      temp.push_back(semi);
    }
    for(; i!=v1.rend(); i++) {
      int semi=*i-c; c=0;
      if(semi<0) semi+=10, c=1;
      temp.push_back(semi);
    }
    while(*(temp.rbegin())==0 && temp.size()>1) temp.pop_back();
    return reverse_assign(temp);
  }
  static vector<int> multiply(vector<int> v1, vector<int> v2) {
    vector<int> result; bool sign=false; int c=0, k=0;

    if(v1[0]<0 ^ v2[0]<0) sign=true;
    v1[0]=abs(v1[0]); v2[0]=abs(v2[0]); result.push_back(0);
    if(greater(v2, v1)) v1.swap(v2);

    for(auto i=v1.rbegin(); i!=v1.rend(); i++, k++) {
      vector<int> temp;
      for(int l=1; l<=k; l++) temp.push_back(0);
      for(auto j=v2.rbegin(); j!=v2.rend(); j++) {
        int semi=*i*(*j)+c;
        temp.push_back(semi%10);
        c=semi/10;
      }
      for(; c!=0; c/=10) temp.push_back(c%10);
      while(*(temp.rbegin())==0 && temp.size()>1) temp.pop_back();
      result=add(result, reverse_assign(temp));
    }
    if(sign) result[0]=-result[0];
    return result;
  }
  //static vector<int> divide(vector<int> &v1, vector<int> &v2) throw(logic_error);

  static double convert(const vector<int> &v) {
    string result;
    for(int i=0; i<v.size(); ++i) {
      string temp=to_string(v[i]);
      result.append(temp);
    }
    string::size_type sz;
    return stod(result, &sz);
  }

public:
  number(int n=0) {num=to_string(n);}
  number(double n) {
    num=to_string(n);
    while(num.back()=='0') num.pop_back();
    if(num.back()=='.') num.pop_back();
  }
  number(const number &n): num(n.num) {}
  ~number() {}
  const number& operator=(const number &n) {
    num=n.num;
    return *this;
  }

  friend istream& operator>>(istream &is, number &n) {
    return getline(is, n.num);
  }
  friend ostream& operator<<(ostream &out, const number &n) {
    out<<n.num;
    return out;
  }
  double getnumber() {
    return convert(assign(num));
  }
  string getnum() {
    return num;
  }

  friend number operator+(const number &n1, const number &n2) {
    return number(convert(add(assign(n1.num), assign(n2.num))));
  }
  friend number operator-(const number &n1, const number &n2) {
    return number(convert(add(assign(n1.num), assign_negative(n2.num))));
  }
  friend number operator*(const number &n1, const number &n2) {
    return number(convert(multiply(assign(n1.num), assign(n2.num))));
  }

  number& operator+=(const number &n) {
    num=number(convert(add(assign(num), assign(n.num)))).num;
    return *this;
  }
  number& operator-=(const number &n) {
    num=number(convert(add(assign(num), assign_negative(n.num)))).num;
    return *this;
  }
  number& operator*=(const number &n) {
    num=number(convert(multiply(assign(num), assign(n.num)))).num;
    return *this;
  }
};