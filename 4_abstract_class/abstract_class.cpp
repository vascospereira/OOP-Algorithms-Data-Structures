// abstract base class
#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    Polygon(int w, int h): width(w), height(h){}
    virtual ~Polygon(){};
    virtual int area() = 0;
};

class Output {
  public:
    static void print (int i);
};

void Output::print (int i) {
  cout << i << '\n';
}

class Rectangle: public Polygon, public Output {
  public:
	Rectangle(int w,int h): Polygon(w,h){}
    int area ()
      { return width*height; }
};

class Triangle: public Polygon, public Output {
  public:
	Triangle(int w, int h): Polygon(w,h){}
    int area ()
      { return width*height/2; }
};

int main () {
	Polygon *poly1 = new Rectangle(3,4);
	Polygon *poly2 = new Triangle(5,6);
	Rectangle::print(poly1->area());
	Triangle::print(poly2->area());
	return 0;
}
