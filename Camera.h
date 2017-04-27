 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Apr 03 2017
                                      SDLGame

 File Name:     Camera.h
 Description:   Renders a certain viewport of the overall game area.
 *****************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  public:
    Camera(int x, int y, int width, int height);
    ~Camera();

    void setPos(int x, int y);
    void addX(int a);
    void addY(int a);

    int getX();
    int getY();
    int getWidth();
    int getHeight();

  private:
    int x;
    int y;
    int width;
    int height;
};

#endif /* CAMERA_H */