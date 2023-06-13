#include "tgaimage.h"
#include "parser.h"
#include "geometry.h"
#include <iostream>

void triangle(vec3f t0, vec3f t1, vec3f t2, TGAImage &image, TGAColor color);
matrix lookat(vec3f eye, vec3f center, vec3f up);
matrix viewport(int x, int y, int w, int h);

const int width  = 800;
const int height = 800;
const int depth  = 255;

Model *model = NULL;
int *zbuffer = NULL;

vec3f eye{1,1,3};
vec3f center{0,0,0};
vec3f up{1,0,0};
vec3f light_dir = eye.normalized();

int main(int argc, char** argv) {
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }
	
	matrix ModelView  = lookat(eye, center, up);
	matrix Projection = matrix();
	matrix ViewPort   = viewport(width/8, height/8, width*3/4, height*3/4);
	Projection[3][2] = -1.f/(eye-center).norm();

	zbuffer = new int[width*height];
    for (int i=0; i<width*height; i++) {
        zbuffer[i] = std::numeric_limits<int>::min();
    }

    TGAImage image(width, height, TGAImage::RGB);
	for (int i=0; i<model->nfaces(); i++) {
		if(i%16 == 0) {
		std::cout << i << '/' << model->nfaces() << '\n';
		}
		std::vector<int> face = model->face(i);
		vec3f screen_coords[3];
		vec3f world_coords[3];
		for (int j=0; j<3; j++) {
			vec3f v = model->vert(face[j]);
			screen_coords[j] = ViewPort*(Projection*ModelView*(v));
			world_coords[j]  = v;
		}
		vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
		n = n.normalized();
		float intensity = -(n*light_dir);
		if (intensity>0) {
			triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
		}
		else {
			triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(1, 1, 1, 255));
		}
	}


    image.flip_vertically();
    image.write_tga_file("output.tga");
	std::cout << "Finish!!";
    delete model;
    return 0;
}


matrix viewport(int x, int y, int w, int h) {
    matrix m = matrix();
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = depth/2.f;

    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = depth/2.f;
    return m;
}

matrix lookat(vec3f eye, vec3f center, vec3f up) {
    vec3f z = (center-eye).normalized();
    vec3f x =  (up^z).normalized();
    vec3f y =  (z^x).normalized();
    matrix res = matrix();
    for (int i=0; i<3; i++) {
        res[0][i] = -x[i];
        res[1][i] = y[i];
        res[2][i] = -z[i];
        res[i][3] = -center[i];
    }
    return res;
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
			if (P.x>=width||P.y>=height||P.x<0||P.y<0) continue;
            if (zbuffer[idx]<P.z) {
                zbuffer[idx] = P.z;
                image.set(int(P.x+0.5), int(P.y+0.5), color);
            }
        }
    }
}