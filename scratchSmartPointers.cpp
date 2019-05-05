#include <iostream>
#include <vector>
#include <memory>

using std::cout ;
using std::endl ;
using std::shared_ptr ;
using std::vector ;
using std::unique_ptr ;

template < typename T, typename LL_Delete_Function_Type, typename LLNode_Delete_Function_Type >
class Shared_LL {
      class LLNode {
        friend class Shared_LL ;
        public :
          LLNode () =  default ;
          LLNode ( T _data , bool _visited = false , unique_ptr < LLNode > _next = NULL ) :
            data ( new T (_data ) ) , visited ( _visited ) , next ( _next ) { }
          LLNode ( T * _data , bool _visited = false , unique_ptr < LLNode > _next = NULL ) :
            data ( _data ) , visited ( _visited ) , next ( _next ) { }
          ~LLNode () {
            LL_Node_Delete () ;
          }
        private :
          T * data ;
          bool visited ;
          unique_ptr<LLNode > next ;
          LLNode_Delete_Function_Type LL_Node_Delete ;
  };
  typedef std::pair<Shared_LL & , bool > shared_LL_Return_Pair ;
  private :
    unique_ptr<LLNode > root ;
    LL_Delete_Function_Type LL_Delete ;
    LLNode_Delete_Function_Type LL_Node_Delete ;
    LLNode * head ;
    LLNode * current ;
    LLNode * tail ;
  public :
    Shared_LL () = default ;
    explicit Shared_LL ( LL_Delete_Function_Type _f, LLNode_Delete_Function_Type _f_Node ) : LL_Delete ( _f ) , LL_Node_Delete ( _f_Node ) {
      root = unique_ptr<LLNode> (new LLNode(NULL) , _f_Node ) ;
      tail = current = head = root.get() ;
    }
    explicit Shared_LL ( T * _data, LL_Delete_Function_Type _f, LLNode_Delete_Function_Type _f_Node ) : Shared_LL ( _f, _f_Node ) {
      root.reset () ;
      root = unique_ptr < LLNode > ( new LLNode ( _data), _f_Node ) ;
      tail = current = head = root.get() ;
    }
    explicit Shared_LL ( T _data, LL_Delete_Function_Type _f , LLNode_Delete_Function_Type _f_Node ) :
      Shared_LL ( new T ( _data ), _f, _f_Node ) {}

    Shared_LL & add ( T * _data ) {
      LLNode * currentLastNode = tail ;
      currentLastNode->next = unique_ptr<LLNode> ( new LLNode ( _data, false, NULL) , LL_Node_Delete ) ;
      tail = currentLastNode->next.get() ;
    }

    shared_LL_Return_Pair removeNode ( T & _dataToDelete) {
      if ( *(head->data) == _dataToDelete ) {
        LLNode * tempHead = head ;
        root.release () ;
        root = unique_ptr<LLNode>(tempHead->next.get(), LL_Node_Delete);
        tempHead->next.release();
        delete tempHead ;
        return shared_LL_Return_Pair( *this, true );
      }
      LLNode * currentTemp = head ;
      while ( currentTemp->next != NULL && *(currentTemp->next.get()->data) != _dataToDelete ) {
        currentTemp = currentTemp->next.get() ;
      }
      if ( currentTemp->next != NULL) {
        LLNode * tempNodeToDelete = currentTemp->next.get() ;
        currentTemp->next.release() ;
        currentTemp->next = unique_ptr<LLNode>(tempNodeToDelete->next.get(), LL_Node_Delete);
        tempNodeToDelete->next.release() ;
        delete tempNodeToDelete ;
        return shared_LL_Return_Pair( *this, true );
      }
      return shared_LL_Return_Pair( *this, false  );
    }
};

int main() {
  int a = 0 ;
  auto f = [] ( ) { cout << "this " << endl;} ;
  cout << typeid ( f ).name ()  << endl;
  return 0;
}
