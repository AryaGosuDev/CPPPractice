//Arya Mahini
//time spend : 7 hours
//compiled using g++ -std=c++11
//approach : initially I was designing my own hashing system in which I limited the
//name of the room to 3 letters in order to have each room create a unique ID :
/*
static unsigned int calcUniqueId ( const char * const _name) {
  unsigned int result = 0 ;
  for ( size_t i = 0 ; _name[i] != 0 ; ++ i ) {
    result += (_name[i] - 'a') * (int)pow ( 26.0, (double)i) ;
  }
  return result ;
}
*/
//however, designing a more advanced hashing system in order to take in strings of greater size
//would be more time consuming and complex. I used a simple map hash data structure to ensure each room
//was a unique room in the maze. This maze creates
//a DCG ( directed cyclic graph ) and so to find the connectedness of any 2 nodes, a proper BFS needs to
//be executed. To avoid being trapped in a cycle, nodes are only visited once. Newly discovered nodes are added to a
//queue and further searched through the graph. The shortest path in a DCG is coincidently discorved by the BFS.
//Certain rooms can also path to themselves, so the starting room and ending room are not necessarily pathed together.
//There must be a path from one room to another, even the same start and end rooms.
//runtime : O ( v + e) // vertex + edges
//future / advancement : introduing smart pointers to help ensure the cleanup of heap memory. Topological ordering.

#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;

struct Room ;

static constexpr unsigned int DOORS_PER_ROOM = 4 ;
enum doorDirection { North, South, West, East} ;

//a structure for linked-list queue for the BFS
struct QueueLinkedList {

  //a structure for a node on the Queue Linked List
  struct RoomQueueNode {
    RoomQueueNode * next ;
    Room * room ;
    RoomQueueNode ( ) = default ;
    RoomQueueNode ( Room * _room) : room ( _room ) {} ;
    ~RoomQueueNode () = default ;
  };

  QueueLinkedList () = default ;

  QueueLinkedList ( Room * _room ) {
    current = tail = head = new RoomQueueNode(_room);
    head->next = NULL ;
  }
  ~QueueLinkedList();
  RoomQueueNode * head ;
  RoomQueueNode * current ;
  RoomQueueNode * tail ;

  void advanceLinkedList ( Room * _room );
};

struct Maze {
  Maze () = default ;
  ~Maze () ;
  inline void deleteMaze () ;

  bool addRoom ( const char * _name  ) ;
  bool addRoomWithConnection (const char * _name, const char * _existingRoomName, const doorDirection _directionOfDoor ) ;
  inline void printRooms () ;

  static std::map<std::string, Room *> uniqueMapRooms  ;

  static Room * returnRoom ( const char * _name ) {
    std::string nameOfRoom ( _name );
    return (uniqueMapRooms.find (nameOfRoom ) == uniqueMapRooms.end()) ? NULL : (*(uniqueMapRooms.find (nameOfRoom ))).second ;
  }

  static bool doesRoomAlreadyExistInMaze ( const char * _name ) {
    return returnRoom ( _name);
  }
};

std::map<std::string, Room *> Maze::uniqueMapRooms = {} ;

struct Room {
  std::string nameOfRoom ;
  bool visited ;
  Room * Door[DOORS_PER_ROOM] = {} ;

  Room() = default;

  inline Room ( const char * _name )
  : visited ( false ){
      if ( _name == NULL ) throw std::runtime_error  ( "No name given to create a new Room.");
      nameOfRoom = _name ;
      Maze::uniqueMapRooms.insert ( {nameOfRoom, this });
  }

  ~Room() = default ;

  bool PathExistsTo( const char * endingRoomName ) ;
  //strongly connected graph components are vertices in which there is a path from u -> v and v -> u
  static bool PathStronglyConnected ( const char * RoomA, const char * RoomB );

  //make a connection between this room and another room through a door
  Room * addConnection ( const char * _roomToAdd, const doorDirection _doorDirection  ) {
    if ( _roomToAdd != NULL && Maze::doesRoomAlreadyExistInMaze(_roomToAdd) )
      Door[_doorDirection] = Maze::returnRoom (_roomToAdd ) ;
    return this;
  }

  void ResetRooms () {
    for ( auto & roomsInMap : Maze::uniqueMapRooms )
      roomsInMap.second->visited = false;
  }
};

bool Maze::addRoom ( const char * _name  ) {
  if ( _name == NULL || Maze::doesRoomAlreadyExistInMaze (_name )) return false;
  Room * tempRoom = new Room ( _name );
  uniqueMapRooms.insert ( {tempRoom->nameOfRoom, tempRoom });
  return true;
}

bool Maze::addRoomWithConnection (const char * _name, const char * _existingRoomName, const doorDirection _directionOfDoor ) {
  if (_existingRoomName == NULL || _name == NULL || !Maze::doesRoomAlreadyExistInMaze(_existingRoomName) || Maze::doesRoomAlreadyExistInMaze(_name) ) return false;
  Room * existingRoom = Maze::returnRoom (_existingRoomName ) ;
  Room * newRoom = new Room ( _name ) ;
  newRoom->Door[_directionOfDoor] = existingRoom ;
  return true;
}

inline void Maze::printRooms () {
  cout << "Rooms : " ;
  for ( auto & roomsInMap : Maze::uniqueMapRooms)
    cout << "<" << roomsInMap.second->nameOfRoom << "> " ;
  cout << endl;
}

inline void Maze::deleteMaze () {
   for ( auto & roomsInMap : uniqueMapRooms ) {
     delete roomsInMap.second ;
     roomsInMap.second = NULL ;
   }
}

Maze::~Maze () {
   cout << "Deleting Maze." << endl;
   deleteMaze();
}

//perform a breadth first search starting from the starting s room to the ending room with name endingRoomName
bool Room::PathExistsTo(const char* endingRoomName) {
  if ( endingRoomName == NULL || !Maze::doesRoomAlreadyExistInMaze(endingRoomName) ) return false;

  Room * endRoom = Maze::returnRoom(endingRoomName );
  Room * startRoom = this  ;

  //initial head of the queue
  //dont visit the initial room. Need to find a path to all rooms, even the starting room.
  std::unique_ptr<QueueLinkedList> queueLinkedList ( new QueueLinkedList (startRoom )) ;
  //while there are no nodes left to explore
  while ( queueLinkedList->current != NULL) {

    //if room is found, reset the rooms so this function can run on the maze once again, return true, destruction of the unique ptr will delete the queue linked list
    if ( queueLinkedList->current->room == endRoom && queueLinkedList->current->room->visited == true ) {
      ResetRooms () ;
      return true;
    }
    //add successive rooms to explore that have not been visited yet. Visit all possible doors in the room.
    for ( size_t i = 0 ; i < DOORS_PER_ROOM ; ++ i ) {
      if ( queueLinkedList->current->room->Door[i] != NULL && queueLinkedList->current->room->Door[i]->visited == false )
        queueLinkedList->advanceLinkedList(queueLinkedList->current->room->Door[i]) ;
    }

    queueLinkedList->current = queueLinkedList->current->next ;
  }

  //reset the rooms if we choose to traverse the maze again
  ResetRooms () ;

  return false;
}

bool Room::PathStronglyConnected (const char * _RoomA, const char * _RoomB ){
  return Maze::returnRoom ( _RoomA )->PathExistsTo ( _RoomB) && Maze::returnRoom ( _RoomB )->PathExistsTo ( _RoomA) ;
}

void QueueLinkedList::advanceLinkedList( Room * _room ) {
  RoomQueueNode * temp = new RoomQueueNode ( _room );
  tail = tail->next = temp ;
  temp->next = NULL ;
  temp->room->visited = 1;
}

QueueLinkedList::~QueueLinkedList() {

  cout << "Deleting QueueLinkedList : " ;
  while ( head != NULL) {
    RoomQueueNode * temp = head ;
    head = head->next ;
    cout << "<" << temp->room->nameOfRoom << "> " ;
    delete temp ;
    temp = NULL ;
  }
  cout << endl;

}

int main () {

  try {
      Maze mz ;

      mz.addRoom ( "a") ;
      mz.addRoom ( "b") ;
      mz.addRoom ( "c") ;
      mz.addRoom ( "d") ;
      mz.addRoom ( "e") ;
      mz.addRoom ( "f") ;

      if ( mz.addRoomWithConnection( "g", "g", doorDirection::North) ) cout << "Added room g" << endl ;
      if ( mz.addRoomWithConnection( "h", "f", doorDirection::North) ) cout << "Added room h" << endl ;
      if ( mz.addRoomWithConnection( "i", "not", doorDirection::West)) cout << "Added room i" << endl ;

      if ( Maze::doesRoomAlreadyExistInMaze ( "a") ) Maze::returnRoom ( "a")->addConnection ( "b",doorDirection::West)->addConnection ( "d",doorDirection::East)->addConnection ( "f",doorDirection::South);

      if ( Maze::doesRoomAlreadyExistInMaze ( "b") ) Maze::returnRoom ( "b")->addConnection ( "c",doorDirection::West);

      if ( Maze::doesRoomAlreadyExistInMaze ( "c") ) Maze::returnRoom ( "c")->addConnection ( "b",doorDirection::South);

      if ( Maze::doesRoomAlreadyExistInMaze ( "d") ) Maze::returnRoom ( "d")->addConnection ( "f",doorDirection::South)->addConnection ( "e",doorDirection::East);

      if ( Maze::doesRoomAlreadyExistInMaze ( "e") ) Maze::returnRoom ( "e")->addConnection ( "e",doorDirection::East);

      if ( Maze::doesRoomAlreadyExistInMaze ( "efghfg") ) Maze::returnRoom ( "efghfg")->addConnection ( "e",doorDirection::East);

      if ( Maze::returnRoom ( "a")->PathExistsTo ( "e")) cout << "True" << endl;
      if ( Maze::returnRoom ( "a")->PathExistsTo ( "e")) cout << "True" << endl;
      if ( Maze::returnRoom ( "d")->PathExistsTo ( "c")) cout << "True" << endl;

      cout << Room::PathStronglyConnected ("b", "c" ) << endl ;

      mz.printRooms () ;
    }
  catch ( std::exception ex) {
    cout << ex.what() << endl;
  }

  return 0 ;
}
