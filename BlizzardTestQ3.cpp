#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;

struct Room ;

//needs to be able hold every possible unique room with a unique ID without collisions.
//26 possible letters, max 3 letters per room name = 26 ^ 3 = 17576
//Room * unique_map[17576] = {}  ;
std::map<std::string, Room *> unique_map = {} ;
std::vector<Room *> roomTable (0)  ;

struct RoomQueueNode {
  RoomQueueNode * next ;
  Room * room ;

  RoomQueueNode ( ) = default ;
  RoomQueueNode ( Room * _room) : room ( _room ) {} ;

  ~RoomQueueNode () { };

};

struct Room {
  std::string nameOfRoom[4] ;
  unsigned int unique_id ;
  bool visited ;

  Room * RoomNorth ;
  Room * RoomSouth ;
  Room * RoomWest ;
  Room * RoomEast ;

  Room ( char * _name, Room * _north = NULL, Room * _south = NULL, Room * _west = NULL, Room * _east = NULL )
  : visited ( 0 ),
    RoomNorth (_north),
    RoomSouth ( _south),
    RoomWest ( _west),
    RoomEast ( _east){

    if ( _name == NULL ) return ;

    //copy name of room
    for ( size_t i = 0 ; i < _name[i]!= 0 ; ++ i ) {
      nameOfRoom[i] = _name[i] ;
    }

    unique_id = calcUniqueId( nameOfRoom ) ;
  }

  bool PathExistsTo(const char* endingRoomName) ;

  static unsigned int calcUniqueId ( const char * const _name) {
    unsigned int result = 0 ;
    for ( size_t i = 0 ; _name[i] != 0 ; ++ i ) {
      result += (_name[i] - 'a') * (int)pow ( 26.0, (double)i) ;
    }
    return result ;
  }

  void addConnections ( char * _northRoom = 0, char * _southRoom = 0, char * _westRoom = 0, char * _eastRoom = 0 ) {
    if ( _northRoom != 0) {
      (unique_map[calcUniqueId(_northRoom)]) ? RoomNorth = unique_map[calcUniqueId(_northRoom)] : NULL ;
    }
    if ( _southRoom != 0) {
      (unique_map[calcUniqueId(_southRoom)]) ? RoomSouth = unique_map[calcUniqueId(_southRoom)] : NULL ;
    }
    if ( _westRoom != 0) {
      (unique_map[calcUniqueId(_westRoom)]) ? RoomWest = unique_map[calcUniqueId(_westRoom)] : NULL ;
    }
    if ( _eastRoom != 0) {
      (unique_map[calcUniqueId(_eastRoom)]) ? RoomEast = unique_map[calcUniqueId(_eastRoom)] : NULL ;
    }

  }
};

struct Maze {
  Maze ( ) = default ;

  ~Maze () {
    cout << "Deleting Maze" << endl;
    deleteMaze();
  }

  inline void deleteMaze () {
    for ( auto & val : roomTable ) {
      delete val ;
      val = NULL ;
    }
  }

  bool addRoom ( char * _name  ) {
    if ( strlen ( _name) > 3) _name[4] = 0;
    unsigned int indx = Room::calcUniqueId ( _name ) ;
    if ( unique_map[indx] != NULL ) {
      cout << "Room with name : " << _name << " already exists." << endl ;
      return 0;
    }
    else {
      Room * tempRoom = new Room ( _name );
      unique_map[tempRoom->unique_id] = tempRoom ;
      roomTable.push_back (tempRoom ) ;
      return 1;
    }
  }

  bool addRoomWithConnection (char * _name, char * _existingRoomName, bool northDoor = false, bool southDoor = false, bool westDoor = false, bool eastDoor = false ) {
    Room * _existingRoom = unique_map[Room::calcUniqueId(_existingRoomName)] ;
    if (_existingRoom == NULL ) return 0;
    if ( unique_map[_existingRoom->unique_id] == NULL ){
      cout << "Existing room is not part of this maze" << endl;
      return 0;
    }
    if ( unique_map[Room::calcUniqueId(_name)] != NULL ) {
      cout << "Room with name : " << _name << " already exists within maze." << endl;
      return 0;
    }
    Room * tempRoom = new Room ( _name, (northDoor) ? _existingRoom : NULL,(southDoor) ? _existingRoom : NULL,(westDoor) ? _existingRoom : NULL,(eastDoor) ? _existingRoom : NULL ) ;

    unique_map[tempRoom->unique_id] = tempRoom ;
    roomTable.push_back (tempRoom ) ;
    return 1;
  }

  static Room * returnRoom ( const char * _name ) {
    return unique_map[Room::calcUniqueId(_name)] ;
  }

  void printRooms () {
    for ( auto & val : roomTable ) {
      cout << val->nameOfRoom << " " << val->unique_id << endl  ;
    }
  }
};

//perform a breadth first search starting from the starting (s) room to the ending room with name endingRoomName
bool Room::PathExistsTo(const char* endingRoomName) {
  if ( unique_map[Room::calcUniqueId ( endingRoomName )] == NULL ) return 0;
  if ( unique_map[ this->unique_id ] == NULL ) return 0;

  Room * endRoom = unique_map[Room::calcUniqueId ( endingRoomName )] ;
  Room * startRoom = this;

  if ( endRoom == startRoom ) return 1 ;

  RoomQueueNode * head = new RoomQueueNode (startRoom ) ;
  RoomQueueNode * tail = head ;
  head->room->visited = 1 ;
  head->next = NULL ;

  while ( head != NULL) {

    if ( head->room == endRoom ) {

      //must delete the rest of the queue
      while ( head != NULL) {
        RoomQueueNode * temp = head ;
        head = head->next ;
        delete temp ;
        temp = NULL ;
      }
      return 1;

    }
    if ( head->room->RoomNorth != NULL && head->room->RoomNorth->visited == 0 ) {
      RoomQueueNode * temp = new RoomQueueNode ( head->room->RoomNorth );
      tail->next = temp ;
      temp->next = NULL ;
      temp->room->visited = 1;

    }
    if ( head->room->RoomSouth != NULL && head->room->RoomSouth->visited == 0 ) {
      RoomQueueNode * temp = new RoomQueueNode ( head->room->RoomSouth );
      tail->next = temp ;
      temp->next = NULL ;
      temp->room->visited = 1;

    }
    if ( head->room->RoomWest != NULL && head->room->RoomWest->visited == 0 ) {
      RoomQueueNode * temp = new RoomQueueNode ( head->room->RoomWest );
      tail->next = temp ;
      temp->next = NULL ;
      temp->room->visited = 1;

    }
    if ( head->room->RoomEast != NULL && head->room->RoomEast->visited == 0 ) {
      RoomQueueNode * temp = new RoomQueueNode ( head->room->RoomEast );
      tail->next = temp ;
      temp->next = NULL ;
      temp->room->visited = 1;

    }
    RoomQueueNode * temp = head ;
    head = head->next ;
    delete temp ;
    temp = NULL ;
  }

  for ( auto & val : roomTable ) {
    val->visited = 0;
  }

  return 0;
}

int main () {

  Maze mz ;

  char room1[] = "a";
  char room2[] = "b";
  char room3[] = "c";
  char room4[] = "d";
  char room5[] = "e";
  char room6[] = "f";

  mz.addRoom ( room1) ;
  mz.addRoom ( room2) ;
  mz.addRoom ( room3) ;
  mz.addRoom ( room4) ;
  mz.addRoom ( room5) ;
  mz.addRoom ( room6) ;

  mz.returnRoom (room1 )->addConnections (room2, room6,0, room4  );

  mz.printRooms () ;

  return 0 ;
}
