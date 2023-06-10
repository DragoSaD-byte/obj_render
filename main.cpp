#include "tgaimage.h"
#include "geometry.hpp"
#include "parser.h"

void triangle(vec3f t0, vec3f t1, vec3f t2, TGAImage &image, TGAColor color);

const int width  = 800;
const int height = 800;
const int depth  = 255;

Model *model = NULL;
int *zbuffer = NULL;
vec3f light_dir{0,0,-1};


int main(int argc, char** argv) {
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }

	zbuffer = new int[width*height];
    for (int i=0; i<width*height; i++) {
        zbuffer[i] = std::numeric_limits<int>::min();
    }

    TGAImage image(width, height, TGAImage::RGB);
	for (int i=0; i<model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		vec3f screen_coords[3];
		vec3f world_coords[3];
		for (int j=0; j<3; j++) {
			vec3f v = model->vert(face[j]);
			screen_coords[j] = vec3f{(v.x+1.)*width/2., (v.y+1.)*height/2., (v.z+1.)*255/2.};
			world_coords[j]  = v;
		}
		vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
		n = n.normalized();
		float intensity = n*light_dir;
		if (intensity>0) {
			triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
		}
	}


    image.flip_vertically();
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}


void triangle(vec3f t0, vec3f t1, vec3f t2, TGAImage &image, TGAColor color) {
    if (t0.y==t1.y && t0.y==t2.y) return; 
    if (t0.y>t1.y) std::swap(t0, t1);
    if (t0.y>t2.y) std::swap(t0, t2);
    if (t1.y>t2.y) std::swap(t1, t2);
    float total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        float segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; 
        vec3f A =               t0 + (t2-t0)*alpha;
        vec3f B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (int j=A.x; j<=B.x; j++) {
            float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
            vec3f P = (A) + (B-A)*phi;
            int idx = int(P.x)+int(P.y)*width;
            if (zbuffer[idx]<P.z) {
                zbuffer[idx] = P.z;
                image.set(int(P.x+0.5), int(P.y+0.5), color);
            }
        }
    }
}



void drow_line(vec2i t0, vec2i t1, TGAImage& image, TGAColor& color) {
	int x0{t0.x};
	int x1{t1.x};
	int y0{t0.y};
	int y1{t1.y};
	
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x=x0; x<=x1; x++) {
        float t = (x-x0)/(float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        if (steep) {
            image.set(y, x, color); 
        } else {
            image.set(x, y, color);
        }
    }
}

