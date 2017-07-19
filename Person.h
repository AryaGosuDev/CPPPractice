#ifndef _PERSON_
#define _PERSON_

#include <string>

class Person{


  friend std::istream & read (std::istream &, Person & );
  friend std::ostream & print ( std::ostream &, const Person & );

public:
  Person() = default;
  Person( std::istreeam & is );
  std::string name() const { return name ;}
  std::string address() const { return address ;}
  void setName (std::string _name) { name = _name;}
  void setAddress (std::string _addy) { address = _addy;}

private:
  std::string name;
  std::string address;
};

std::istream &read ( std::istream &is, Person &person){
	is >> person.name >> person.address ;
	return is;
}

std::ostream & print ( std::ostream &os, const Person & person){
	os << person.name() << " " << person.address() << std::endl ;
	 return os;
}

Person::Person ( std::isteream & is) {
  read ( is, *this );
}

#endif
