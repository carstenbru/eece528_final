#include "Raytracer.hpp"
#include "Sphere.hpp"

#include <iostream>
using namespace std;

#include "AdrizDrawing/AdrizDrawing.h"
extern "C" SDL_Surface * create_surface(int w, int h);
extern "C" SDL_Surface * Show_screen(int w, int h, char * name_window);

//[comment]
// In the main function, we will create the scene which is composed of 5 spheres
// and 1 light (which is also a sphere). Then, once the scene description is complete
// we render that scene, by calling the render() function.
//[/comment]
int main(int argc, char **argv) {
	const int width = 640;
	const int height = 480;

	IBMP * frame;
	frame = create_surface(width, height);

	Raytracer raytracer;
	raytracer.loadScene("scene/simple.xml");
	//raytracer.generateSimpleScene();
	raytracer.render((unsigned int*) frame->pixels);

	IBMP * screen;
	screen = Show_screen(frame->w, frame->h, "Ultimate Ray Tracer");
	SDL_BlitSurface(frame, NULL, screen, NULL);
	SDL_Flip(screen);

	SDL_Delay(10000);

	SDL_Quit();

	return 0;
}
