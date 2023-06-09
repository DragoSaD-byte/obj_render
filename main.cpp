#include "tgaimage.h"
#include "geometry.hpp"

TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);

void drow_line(vec t0, vec t1, TGAImage &image, TGAColor& color);
void triangle(vec t0, vec t1, vec t2, TGAImage &image, TGAColor color);


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	triangle(vec{1, 1}, vec{1, 50}, vec{50, 1}, image, white);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}


void triangle(vec t0, vec t1, vec t2, TGAImage &image, TGAColor color) {
    if (t0.y()==t1.y() && t0.y()==t2.y()) return;
    if (t0.y()>t1.y()) std::swap(t0, t1);
    if (t0.y()>t2.y()) std::swap(t0, t2);
    if (t1.y()>t2.y()) std::swap(t1, t2);
    int total_height = t2.y()-t0.y();
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y()-t0.y() || t1.y()==t0.y();
        int segment_height = second_half ? t2.y()-t1.y() : t1.y()-t0.y();
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y()-t0.y() : 0))/segment_height; 
        vec A = t0 + (t2-t0)*alpha;
        vec B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
        if (A.x()>B.x()) std::swap(A, B);
        for (int j=A.x(); j<=B.x(); j++) {
            image.set(j, t0.y()+i, color); 
        }
    }
}



void drow_line(vec t0, vec t1, TGAImage& image, TGAColor& color) {
	int x0{t0.x()};
	int x1{t1.x()};
	int y0{t0.y()};
	int y1{t1.y()};
	
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

