/*
shapes.cpp
October 13th, 2015
Blake Kershaw
kershaw
*/

#include <iostream>
#include <cmath>
#include <shapes.h>

Box::Box() :
  length_(0), width_(0), height_(0), verbose_(0){
}

Box::Box(float length, float width, float height, bool verbose) :
  length_(length), width_(width), height_(height), verbose_(verbose) {

if (Box::verbose_)
  std::cout << "Box()\n";
}

Box::~Box() {
if (Box::verbose_)
  std::cout << "~Box()\n";
}

float Box::Volume() const {
  return length_ * width_ * height_;
}

Cylinder::Cylinder() :
  length_(0), radius_(0), verbose_(0) {
}

Cylinder::Cylinder(float length, float radius, bool verbose) :
  length_(length), radius_(radius), verbose_(verbose) {

if (Cylinder::verbose_)
  std::cout << "Cylinder()\n";
}
Cylinder::~Cylinder() {
if (Cylinder::verbose_)
  std::cout << "~Cylinder()\n";
}
float Cylinder::Volume() const {
  return M_PI * (radius_ * radius_) * length_; //v = PI * r^2 * h
}

Plane::Plane() :
  length_(0), width_(0), verbose_(0) {
}

Plane::Plane(float length, float width, bool verbose) :
  length_(length), width_(width), verbose_(verbose) {

if (Plane::verbose_)
std::cout << "Plane()\n";
}

Plane::~Plane() {
if (Plane::verbose_)
  std::cout << "~Plane()\n";
}

float Plane::Area() const {
  return length_ * width_;
}
