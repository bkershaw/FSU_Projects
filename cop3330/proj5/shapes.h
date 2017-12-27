/*
shapes.h
October 13th, 2015
Blake Kershaw
kershaw
*/



#ifndef SHAPES_H_
#define SHAPES_H_

class Box {
public:
  Box          ();
  Box          ( float, float, float, bool );
  virtual ~Box ();

  float Volume() const; //returns volume of box object

private:
  float length_;
  float width_;
  float height_;
  bool verbose_;
};

class Cylinder {
public:
  Cylinder          ();
  Cylinder          ( float, float, bool);
  virtual ~Cylinder ();

  float Volume() const; //returns volume of cylinder object

private:
  float length_;
  float radius_;
  bool  verbose_;

};

class Plane {
public:
  Plane          ();
  Plane          ( float, float, bool );
  virtual ~Plane ();

  float Area() const; //returns area of plane object

private:
  float length_;
  float width_;
  bool  verbose_;

};
#endif /* SHAPES_H_ */
