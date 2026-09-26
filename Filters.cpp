#include <bits/stdc++.h>
using namespace std;
#include "Image_Class.h"

void grayscale(Image &image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void flip(Image &image, bool h){
    if(h){
        for(int i = 0;i < image.width; i++){
            for(int j = 0; j * 2 < image.height; j++){
                swap(image(i, j, 0), image(i, image.height - 1 - j, 0));
                swap(image(i, j, 1), image(i, image.height - 1 - j, 1));
                swap(image(i, j, 2), image(i, image.height - 1 - j, 2));
            }
        }
        return;
    }
    for(int i = 0;i * 2 < image.width; i++){
        for(int j = 0; j < image.height; j++){
            swap(image(i, j, 0), image(image.width-i-1, j, 0));
            swap(image(i, j, 1), image(image.width-i-1, j, 1));
            swap(image(i, j, 2), image(image.width-i-1, j, 2));
        }
    }
}


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
    string filename;
    cout << "Pls enter colored image name to filter it: ";
    cin >> filename;

    Image image(filename);
    
    vector<string> filters = {"Grayscale", "Black and White", "Invert Colors", "Frame", "Flip", "Rotate",
         "Brightness Adjustment", "Resize", "Merge Images", "Edge Detection", "Crop", "Blur", "Sunlight Effect", 
         "Old TV Effect", "Purple Tint", "infrared", "Skew", "Oil Painting"};

    for(int i = 0; i < 8; i++){
        cout << i+1 << "." << filters[i] << "\n";
    }
    cout << "Pls enter the number filter: ";
    int filter_num;
    cin >> filter_num;

    switch(filter_num){
        case 1:
            grayscale(image);
            break;
        case 2:
            black_and_white(image);
            break;
        case 3:
            // Invert colors function (Yehia)
            break;
        case 4:
            // cout << 1 << ".simple\n";
            // cout << 2 << ".Fancy\n";
            // int x; cin >> x;
            // Frame (Mo'men)
            break;
        case 5:
            int c;
            cout << 1 << ".Horizontally\n" << 2 << ".Vertically\n";
            cout << "Enter your choice: ";
            cin >> c;
            flip(image, c);
            break;
        case 6:
            // Rotate (Ali)
            break;
        case 7:
            // Darken and Lighten (Yehia)
            break;
        case 8:
            // resize (Mo'men)
            break;
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";


    cin >> filename;

    image.saveImage(filename);

    return 0;
}
