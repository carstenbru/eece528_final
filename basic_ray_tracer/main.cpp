#include "Raytracer.hpp"
#include "OpenCL_Raytracer.hpp"
#include "Sphere.hpp"

#include <iostream>
#include <sstream>
using namespace std;

#include "AdrizDrawing/AdrizDrawing.h"
extern "C" SDL_Surface * create_surface(int w, int h);
extern "C" SDL_Surface * Show_screen(int w, int h, char * name_window);
extern "C" int print_string(int horiz_offset, int vert_offset, int color,
		char *font, void* display, const char* string);

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

	//OpenCL_Raytracer raytracer(width, height);
	Raytracer raytracer(width, height);
	raytracer.loadScene("scene/simple.xml");
	//raytracer.generateSimpleScene();

	if (argc > 1) {
		unsigned int frame[width][height];
		raytracer.render(&frame[0][0]);

		std::ofstream ofs(argv[1], std::ios::out | std::ios::binary);
		ofs << "P6\n" << width << " " << height << "\n255\n";
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				int pixel = frame[i][j];
			ofs << (unsigned char) ((pixel >> 16)& 255)
					<< (unsigned char) ((pixel >> 8) & 255)
					<< (unsigned char) ((pixel) & 255) ;
			}
		}
		ofs.close();
	} else {
		IBMP * screen;
		screen = Show_screen(frame->w, frame->h, "Ultimate Ray Tracer");

		int quitting = 0;
		SDL_Event event;
		clock_t begin, end;
		stringstream sstream;
		while (!quitting) {
			begin = clock();

			while (SDL_PollEvent(&event))
				switch (event.type) {
				case SDL_QUIT:
					quitting = 1;
					break;
				}

			raytracer.render((unsigned int*) frame->pixels);

			end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			sstream.str("");
			sstream << 1 / elapsed_secs << " fps" << endl;
			print_string(10, 10, RED_24, cour10_font, frame, sstream.str().c_str());

			SDL_BlitSurface(frame, NULL, screen, NULL);
			SDL_Flip(screen);
		}

		SDL_Quit();
	}

	return 0;
}
