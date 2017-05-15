 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Apr 29 2017
                                      SDLGame

 File Name:     Battle.cpp
 Description:   Contains logic for game and actions.
 *****************************************************************************/

#include ifstream
#include "Battle.h"

Battle::Battle(int x, int y) {
  this.width = x;
  this.height = y;
}

void Battle::init() {

}

void Battle::loadMap(char * filename) {
  std::ifstream infile(filename);

  int tileType, 
  while(infile >> )
}

void Battle::addUnit(Unit u, int x, int y) {

}

void Battle::killUnit(int x, int y) {

}

void moveUnit(int x1, int y1, int x2, int y2) {
  Unit u = this.getUnit(x1, y1);
}

void getUnit(int x, int y) {
  
}
