#include <iostream>
using namespace std;
#include "Image_Class.h"

void black_and_white(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {

            unsigned int r = img(i, j, 0);
            unsigned int g = img(i, j, 1);
            unsigned int b = img(i, j, 2);

            unsigned int gray = (r + g + b) / 3;
            img(i, j, 0) = gray;
            img(i, j, 1) = gray;
            img(i, j, 2) = gray;
            if (gray > 128)
            {
                img(i, j, 0) = 255;
                img(i, j, 1) = 255;
                img(i, j, 2) = 255;
            }
            else
            {
                img(i, j, 0) = 0;
                img(i, j, 1) = 0;
                img(i, j, 2) = 0;
            }
        }
    }
}

int main () {
        string img_name;
    cin >> img_name;

    Image img(img_name);
    black_and_white(img);
    img.saveImage("img.png");
}