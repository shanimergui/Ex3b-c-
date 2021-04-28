#include "NumberWithUnits.hpp"

namespace ariel{

  unordered_map<string, unordered_map<string,double>> umap;

  double check_convert(NumberWithUnits const & a, NumberWithUnits const & b){
    if((a.u==b.u) && (umap.find(a.u) !=umap.end())) { return b.amount;}
    if((umap.find(a.u) != umap.end()) && (umap[a.u].find(b.u) != umap[a.u].end())){
        return b.amount*umap[b.u][a.u];
    }
      string message = string("Units do not match - [") +b.u+ string("] cannot be converted to [") +a.u+ string("]");
      __throw_invalid_argument(message.c_str());
    return -1;
  }

  bool NumberWithUnits::exsist(string const & s){
    if(umap.find(s) != umap.end()){
      return true; return false;
    }
    return false;
  }

  void NumberWithUnits::read_units(ifstream& units_file){
    //1 km = 1000 m
    double amount1=0;
    string u1;
    string temp;
    double amount2=0;
    string u2;
    while (units_file >> amount1 >> u1 >> temp >> amount2 >> u2)
    {
      //-> 1 km = 1000 m
      //--> 1 m = 1/1000 km
      //-> 1 m = 100 cm
      //--> 1 cm = 1/100 m
      umap[u1][u2]=amount2;
      umap[u2][u1]=amount1/amount2;

      for(auto &pa: umap[u1]){
        //pa.first <- string
        //pa.second <- double
        double temp=umap[u2][u1]*pa.second;
        umap[u2][pa.first] =temp;
        umap[pa.first][u2] =1/temp;
      }
      for(auto &pa: umap[u2]){
        //pa.first <- string
        //pa.second <- double
        double temp=umap[u1][u2]*pa.second;
        umap[u1][pa.first] =temp;
        umap[pa.first][u1] =1/temp;
      }
    }
  }

  // + , - , += , -= , (+) ,(-)
   //+

  NumberWithUnits NumberWithUnits::operator+( NumberWithUnits const & b ) {
      double ans_b=check_convert(*this,b);
    return NumberWithUnits(this->amount+ans_b,this->u);
  }
  //(+)
  NumberWithUnits NumberWithUnits::operator+( ) const{
    return NumberWithUnits(this->amount,this->u);
  }
  // -
  NumberWithUnits NumberWithUnits::operator-( NumberWithUnits const & b ){
    double ans_b=check_convert(*this,b);
    return NumberWithUnits(this->amount-ans_b,this->u);
  }
  // (-)
  NumberWithUnits NumberWithUnits::operator-( ) const{
    return NumberWithUnits(-1*(this->amount),this->u);
  }
  //  +=
  NumberWithUnits & NumberWithUnits::operator+=( NumberWithUnits const & b ){
    double ans_b=check_convert(*this,b);
    this->amount+=ans_b;
    return *this;
  }
  // -=
  NumberWithUnits & NumberWithUnits::operator-=( NumberWithUnits const & b ){
    double ans_b=check_convert(*this,b);
    this->amount-=ans_b;
    return *this;
  }


  // > >= < <= != ==
  //==
  bool operator==( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    const double eps=0.001;
    if( abs(a.amount-ans_b)<eps){
      return true; return false;
    }
    return false;
  }
  //!=
  bool operator!=( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount!=ans_b){
      return true; return false;
    }
    return false;
  }
  //<
  bool operator<( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount<ans_b){
      return true; return false;
    }
    return false;
  }
  //<=
  bool operator<=( NumberWithUnits const & a, NumberWithUnits const & b ){
    return a == b || a < b;
  }
  //>
  bool operator>( NumberWithUnits const & a, NumberWithUnits const & b ){
    double ans_b=check_convert(a,b);
    if(a.amount>ans_b){
      return true; return false;
    }
    return false;
  }
  //>=
  bool operator>=( NumberWithUnits const & a, NumberWithUnits const & b ){
    return a == b || a > b;
  }

  // prefix ++ --  postfix ++ ---
  //prefix
  NumberWithUnits & operator++( NumberWithUnits & value ){
    value.amount++;
    return value;
  }
  //postfix
  NumberWithUnits operator++( NumberWithUnits & value, int x){
    return NumberWithUnits(value.amount++,value.u);
  }
  //prefix
  NumberWithUnits & operator--( NumberWithUnits & value ){
    value.amount--;
    return value;
  }
  //postfix
  NumberWithUnits operator--( NumberWithUnits & value, int x){
    return NumberWithUnits(value.amount--,value.u);
  }

  //*
  NumberWithUnits operator*(NumberWithUnits const & a, double const & x){
    return NumberWithUnits(a.amount*x,a.u);
  }
  NumberWithUnits operator*(double const & x, NumberWithUnits const & a){
    return NumberWithUnits(a.amount*x,a.u);
  }

  // << >>
  ostream & operator<<(ostream& os, NumberWithUnits const & a){
    return os<<a.amount<<"["<<a.u<<"]";
    // 5.7[m]
  }

  istream & operator>>(istream& is,NumberWithUnits& a){
    // -    7000. 50    ["k     m" ] 700[km]
    string s;
    getline(is, s, ']');
    // -    7000. 5sadasd50    ["k""m" ]

    string amount;
    for(char& c1: s){
      if(c1=='['){
        break;
      }
        if((isdigit(c1)!=0) || c1=='-' || c1=='.'){
          amount+=c1;
        }
    }

    string u = s.substr(s.find('[')); //cut strin from index to end function find return index of "["

    string unit;
    for(char& c1: u){
        if((isalpha(c1)!=0) || c1=='_'){
          unit+=c1;
        }
    }
  if(! NumberWithUnits::exsist(unit)){__throw_invalid_argument("Not exsist");}

  a = NumberWithUnits(stod(amount),unit);
  return is;
  }
}
