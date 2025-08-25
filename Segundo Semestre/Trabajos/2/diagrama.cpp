#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    const int width = 1200;
    const int height = 800;
    const double r_min = 2.5;
    const double r_max = 4.0;
    const int iterations = 1000;
    const int last = 200;

    vector<unsigned char> img(width * height, 0);

    for (int col = 0; col < width; col++) {
        double r = r_min + (r_max - r_min) * col / (width - 1);
        double x = 0.5;

        for (int i = 0; i < iterations - last; i++) {
            x = r * x * (1 - x);
        }

        for (int i = 0; i < last; i++) {
            x = r * x * (1 - x);
            int row = (int)(x * height);
            if (row < 0) row = 0;
            if (row >= height) row = height - 1;

            int idx = (height - 1 - row) * width + col;
            img[idx] = 255;
        }
    }

    ofstream file("bifurcacion.ppm", ios::binary);
    file << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width * height; i++) {
        unsigned char v = img[i];
        file.put(v); // R
        file.put(v); // G
        file.put(v); // B
    }
    file.close();

    return 0;
}
