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
    void setXScale(float x);
    void setYScale(float y);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    float getXScale();
    float getYScale();

    int gToL(int coord, bool axis);
    int lToG(int coord, bool axis);

  private:
    int x;
    int y;
    int width;
    int height;

    float x_scale;
    float y_scale;
};

#endif /* CAMERA_H */