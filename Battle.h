 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Apr 29 2017
                                      SDLGame

 File Name:     Battle.h
 Description:   Contains logic for game and actions.
 *****************************************************************************/

#ifndef BATTLE_H
#define BATTLE_H

class Battle {
  public:
    Battle(int x, int y);
    void init();
    void loadMap(char * filename);
    void addUnit(Unit u, int x, int y);
    void killUnit(int x, int y);

    void moveUnit(int x1, int y1, int x2, int y2);

    void getUnit(int x, int y);
    int width;
    int height;
}

#endif /* BATTLE_H */