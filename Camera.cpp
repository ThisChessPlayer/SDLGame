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
  this->x_scale = 1;
  this->y_scale = 1;
}

Camera::~Camera() {
  
}

void Camera::setPos(int x, int y) {
  this->x = x;
  this->y = y;
}

void Camera::setXScale(float x) {
  this->x_scale = x;
}

void Camera::setYScale(float y) {
  this->y_scale = y;
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

float Camera::getXScale() {
  return x_scale;
}

float Camera::getYScale() {
  return y_scale;
}

int Camera::gToL(int coord, bool axis) {
  if(axis) //x
    return (coord - x) / x_scale;
  else //y
    return (coord - y) / y_scale;
}

int Camera::lToG(int coord, bool axis) {
  if(axis) //x
    return (coord + x) / x_scale;
  else //y
    return (coord + y) / y_scale;
}