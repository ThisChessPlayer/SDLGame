 /*****************************************************************************

                                                         Author: Jason Ma
                                                         Date:   Apr 03 2017
                                      SDLGame

 File Name:     Camera.cpp
 Description:   Renders a certain viewport of the overall game area.
 *****************************************************************************/

#include "Camera.h"

Camera::Camera(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

Camera::~Camera() {
  
}

void Camera::setPos(int x, int y) {
  this->x = x;
  this->y = y;
}

void Camera::addX(int a) {
  this->x += a;
}

void Camera::addY(int a) {
  this->y += a;
}

int Camera::getX() {
  return x;
}

int Camera::getY() {
  return y;
}

int Camera::getWidth() {
  return width;
}

int Camera::getHeight() {
  return height;
}