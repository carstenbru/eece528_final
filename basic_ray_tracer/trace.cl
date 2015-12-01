typedef struct {
	float x;
	float y;
	float z;
} Vec3f;

typedef struct {
	Vec3f center;                           /// position of the object

	float radius, radius2;

	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
	float reflection;      /// surface reflectivity
} Sphere;

__kernel void example( __global Sphere* scene, int scene_size, __global unsigned int* frame ){
       int column = get_global_id(0);
       int row = get_global_id(1);
       int screenWidth = get_global_size(0);
       int screenHeight = get_global_size(1);
       
       //printf("hi, I'm row %d and column %d!\n", row, column);
       /*printf("center: %f %f %f\n", scene->center.x,scene->center.y,scene->center.z);
       printf("radius2: %f\n", scene->radius2);
       printf("objects: %d\n", scene_size);*/
       
       *(frame + column + row*screenWidth) = column << 8 + row; //TODO test
}