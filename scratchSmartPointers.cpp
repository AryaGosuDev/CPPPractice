#include <iostream>
#include <vector>
#include <memory>

using std::cout ;
using std::endl ;
using std::shared_ptr ;
using std::vector ;
using std::unique_ptr ;

/************** Self Deleting Linked List Data Structure ***************
************************************************************************/

template <typename T>
class Shared_LL {
  typedef std::pair<Shared_LL &, bool> Shared_LL_return ;
  public :
    class LLNode {
      friend class Shared_LL ;
      public :
        LLNode() = default ;
        LLNode( T _data ) : data ( new T(_data)) {} 
        ~LLNode() {
          cout << "Deleting LLNode " << endl ;
        }
      private :
        unique_ptr<LLNode> next ;
        T * data ;
    };
  private :
    int size ;
    unique_ptr<LLNode> root ;
    LLNode * head ;
    LLNode * tail ;
  public :
    Shared_LL () : size ( 0 ) , head ( NULL), tail ( NULL ) {} 
    explicit Shared_LL ( const T & _data ) : Shared_LL() {
      root.release() ;
      root = unique_ptr<LLNode> ( new LLNode(_data)) ;
      tail = head = root.get() ;
      size++ ;
    }
    ~Shared_LL () {
      cout << "Deleting LL " << endl;

    }
    Shared_LL_return add ( T & _data ) {
      LLNode * currentLastNode = tail ;
      currentLastNode->next = unique_ptr<LLNode> ( new LLNode(_data));
      tail = currentLastNode->next.get();
      size++ ;
      return Shared_LL_return ( *this, true ) ;
    }
    Shared_LL_return add ( T && _data ) {
      LLNode * currentLastNode = tail ;
      currentLastNode->next = unique_ptr<LLNode> ( new LLNode(_data));
      tail = currentLastNode->next.get();
      size++ ;
      return Shared_LL_return ( *this, true ) ;
    }
    Shared_LL_return removeLastNode () {
      if ( size == 0 ) return Shared_LL_return( *this, false ) ;
      LLNode * tempCurrent = head ;
      LLNode * tempPrevious = NULL ;
      while ( tempCurrent->next.get() != NULL ) { tempPrevious = tempCurrent ; tempCurrent = tempCurrent->next.get() ; }
      if ( tempPrevious == NULL ) {
        root.release() ;
        tempCurrent->next.release() ;
        delete tempCurrent ;
        head = tail = NULL ;
        --size;
        return Shared_LL_return ( *this, true );
      }
      if ( tempCurrent != tail) throw std::runtime_error ( "Improper LL structure");
      tempPrevious->next.release() ;
      tempCurrent->next.release();
      delete tempCurrent ;
      size--;
      tail = tempPrevious ;
      return Shared_LL_return ( *this, true);
    }
    Shared_LL_return removeNode ( LLNode * _nodeToRemove, LLNode * _nodePrevious) {
      if ( _nodeToRemove == NULL ) return Shared_LL_return ( *this, false );
      if ( _nodeToRemove == head) {
        root.release() ;
        root = unique_ptr<LLNode> ( head->next.get());
        head->next.release() ;
        delete head ;
        --size;
        head = root.get();
        if ( size == 0) tail = root.get() ;
        return Shared_LL_return ( *this,true );
      }
      _nodePrevious->next.release() ;
      _nodePrevious->next = unique_ptr<LLNode> ( _nodeToRemove->next.get());
      _nodeToRemove->next.release() ;
      if ( _nodeToRemove->next.get() == NULL ) tail = _nodePrevious ;
      delete _nodeToRemove ;
      size--;
      return Shared_LL_return ( *this, true );
    }
    Shared_LL_return removeValue ( const T &  _data ) {
      if ( head == NULL ) return Shared_LL_return ( *this, false);
      if ( head == tail && *head->data == _data) return removeLastNode() ;
      LLNode * tempCurrent = head ;
      LLNode * tempPrevious = NULL ;
      while ( tempCurrent != NULL && *tempCurrent->data != _data) {
        tempPrevious = tempCurrent ;
        tempCurrent = tempCurrent->next.get() ;
      }
      return removeNode ( tempCurrent, tempPrevious ) ;
    }
    Shared_LL_return printLL () {
      LLNode * tempCurrent = head ;
      cout << "Printing LL : " << endl;
      while ( tempCurrent != NULL ) {
        cout << *tempCurrent->data << endl;
        tempCurrent = tempCurrent->next.get() ;
      }
      return Shared_LL_return ( *this, true );
    }
};

int main() {
  try {
    unique_ptr<Shared_LL<int>> p = unique_ptr<Shared_LL<int>>(new Shared_LL<int>(4)) ;
    p->add(5).first.add(6).first.add(7).first.removeValue(5 ) ;
    
    p->printLL() ;
    p->printLL() ;

  }
  catch ( std::exception ex ) {
    cout << "Error : " << ex.what() << endl;
  }

  return 0 ;

}
