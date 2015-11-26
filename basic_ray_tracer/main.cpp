#include "Raytracer.hpp"
#include "Sphere.hpp"

#include <iostream>
using namespace std;

//[comment]
// In the main function, we will create the scene which is composed of 5 spheres
// and 1 light (which is also a sphere). Then, once the scene description is complete
// we render that scene, by calling the render() function.
//[/comment]
int main(int argc, char **argv) {
	Raytracer raytracer;
	raytracer.loadScene("abc.xml");
	raytracer.render();

	cout << "finished" << endl;

	return 0;
}
