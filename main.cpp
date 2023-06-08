#include "tgaimage.h"

TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
void drow_line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor& color);


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	drow_line(0, 0, 99, 99, image, white);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}



void drow_line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor& color) {
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
