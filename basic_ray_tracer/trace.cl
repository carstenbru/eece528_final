
typedef struct {
	void* parent;
        int a; 
} control_port_t;

__kernel void example( __global char* buf, __global char* buf2 ){
       int id = get_global_id(0);
       printf("hi, I'm number %d!\n", id);

       control_port_t b;
       b.a = 8;
       buf2[id] = buf[id];

}