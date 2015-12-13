#include "Raytracer.hpp"
#include "Raytracer_int.hpp"
#include "Raytracer_pthreads.hpp"
#include "Raytracer_OpenMP.hpp"
#include "OpenCL_Raytracer.hpp"
#include "Sphere.hpp"
#include "timer.h"

#include <iostream>
#include <sstream>
using namespace std;

#define USE_SDL 1

#if (USE_SDL == 1)
#include "AdrizDrawing/AdrizDrawing.h"
extern "C" SDL_Surface * create_surface(int w, int h);
extern "C" SDL_Surface * Show_screen(int w, int h, char * name_window);
extern "C" int print_string(int horiz_offset, int vert_offset, int color,
		char *font, void* display, const char* string);
#endif

#define USE_OPENCL 0
#define USE_PTHREADS 0
#define USE_OPENMP 0


//[comment]
// In the main function, we will create the scene which is composed of 5 spheres
// and 1 light (which is also a sphere). Then, once the scene description is complete
// we render that scene, by calling the render() function.
//[/comment]
int main(int argc, char **argv) {
	const int width = 800;
	const int height = 600;

#if (USE_SDL == 1)
	IBMP * frame;
	frame = create_surface(width, height);
#endif

#if (USE_OPENCL == 1)
	OpenCL_Raytracer raytracer(width, height);
#else
#if (USE_PTHREADS == 1)
	Raytracer_pthreads raytracer(width, height);
#else
#if (USE_OPENMP == 1)
	Raytracer_OpenMP raytracer(width, height);
#else
	Raytracer_int raytracer(width, height);
#endif
#endif
#endif
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
				ofs << (unsigned char) ((pixel >> 16) & 255)
						<< (unsigned char) ((pixel >> 8) & 255)
						<< (unsigned char) ((pixel) & 255);
			}
		}
		ofs.close();
	} else {
#if (USE_SDL == 1)
		IBMP * screen;
		screen = Show_screen(frame->w, frame->h, "Ultimate Ray Tracer");

		int quitting = 0;
		SDL_Event event;
		ClockTimer timer;
		stringstream sstream;
		while (!quitting) {
			timer.reset();

			while (SDL_PollEvent(&event))
				switch (event.type) {
				case SDL_QUIT:
					quitting = 1;
					break;
				}

			raytracer.render((unsigned int*) frame->pixels);

			double elapsed_secs = timer.get_elapsed() / 1000.0f;
			sstream.str("");
			sstream << 1 / elapsed_secs << " fps" << endl;
			print_string(10, 10, RED_24, cour10_font, frame, sstream.str().c_str());

			SDL_BlitSurface(frame, NULL, screen, NULL);
			SDL_Flip(screen);
		}

		SDL_Quit();
#else
		cout << "error: compiled without SDL, provide a image file as parameter for output!" << endl;
#endif
	}

	return 0;
}
