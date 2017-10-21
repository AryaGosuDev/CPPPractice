#include "Sales_data.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <numeric>
#include <list>
#include <algorithm>
#include <iterator>
#include <exception>
#include <fstream>
#include <utility>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <memory>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

class Folder ;

class Message {

  public :

    explicit Message ( const string & str = "") : contents ( str )  {}

    Message ( const Message &) ;
    Message & operator= ( const Message & ) ;

    ~Message() ;

    void save ( Folder &);
    void remove ( Folder & );

  private :
    string contents ;
    std::set<Folder*> folders ;

    void add_to_folders ( const Message &  ) ;
    void remove_from_folders(  );
};

  Message::~Message () {
    remove_from_folders();


  }

  

  

  Message::Message( const Message & msg) : 
    contents ( msg.contents ) , folders ( msg.folders)  {
      add_to_folders ( msg );
  }

  Message & Message::operator= ( const Message & rhs ) {

    remove_from_folders ();
    contents = rhs.contents ;
    folders =  rhs.folders;
    add_to_folders ( rhs );
    return *this ;
  }

  

  class Folder {

    public :
      Folder () = default ;
      Folder( Folder & ) ;
      Folder & operator= ( const Folder & )  ;

      void addMsg ( Message * msg ) ;
      void removeMsg ( Message * msg ) ;

      ~Folder() ;

    private :

      std::set<Message*> msgs ;
      void remove_msgs_in_folder ();
  };

  Folder::Folder ( Folder & f ) : msgs ( f.msgs) {

  }

  Folder & Folder::operator= ( const Folder & rhs ) {

    msgs.clear();
    for ( auto msg : rhs.msgs)
      this->msgs.insert ( msg ) ;

    return *this ;

  }

  void Folder::addMsg ( Message * msg ) {

    this->msgs.insert ( msg ) ;
  }

  void Folder::removeMsg ( Message * msg ) {
    this->msgs.erase ( msg ) ;
  }

  void Folder::remove_msgs_in_folder () {
    msgs.clear();

  }

  void Message::save ( Folder & folder ) {
    folders.insert(&folder);
    folder.addMsg ( this );
  }

  void Message::remove ( Folder & folder ) {
    folders.erase ( &folder );
    folder.removeMsg ( this );

  }

  void Message::remove_from_folders ( ) {
    for ( auto f : this->folders)
      f->removeMsg(this);
    this->folders.clear();
  }

  void Message::add_to_folders ( const Message & msg ) {
    for ( auto f : msg.folders)
      f->addMsg(this);

  }

int main ( void ) {

  try {
    Message m1 ( "fff" );

    Message m2 ( m1 ) ;


  	
  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
