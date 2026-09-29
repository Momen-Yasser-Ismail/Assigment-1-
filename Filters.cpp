// Header 
// Adham Abdelrahman  id: 20250078  Filters: Grayscale, Flip,
// Ali Yasser         id: 20250406  Filters: Black and white, Rotate,
// Yehia Nabil        id: 20250742  Filters: Invert, lighten_darken,
// Mo'men Yasser      id: 20251441  Filters: Frame, Resize, 

#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Adham filters
void grayscale(Image &image);
void flip(Image &image, bool h);

// Ali filters
void rotate(Image &img);
void black_and_white(Image &img);

// Yehia filters
void Invert(Image &img);
void lighten_darken(Image &img);

// Mo'men filters 
void frame (Image &image);
void resize(Image &image);

int main () 
{
    string filename;
    cout << "Pls enter colored image name to filter it: ";
    cin >> filename;

    Image image(filename);
    
    vector<string> filters = {"Grayscale", "Black and White", "Invert Colors", "Frame", "Flip", "Rotate",
         "Brightness Adjustment", "Resize", "Merge Images", "Edge Detection", "Crop", "Blur", "Sunlight Effect", 
         "Old TV Effect", "Purple Tint", "infrared", "Skew", "Oil Painting"};

    for(int i = 0; i < 8; i++)
    {
        cout << i+1 << "." << filters[i] << "\n";
    }

    cout << "Pls enter the number filter: ";
    int filter_num;
    cin >> filter_num;

    switch(filter_num)
    {
        case 1:
            grayscale(image);
            break;
        case 2:
            black_and_white(image);
            break;
        case 3:
            Invert(image);
            break;
        case 4:
            frame(image);
            break;
        case 5:
            int c;
            cout << 1 << ".Horizontally\n" << 2 << ".Vertically\n";
            cout << "Enter your choice: ";
            cin >> c;
            flip(image, c);
            break;
        case 6:
            rotate(image);
            break;
        case 7:
            lighten_darken(image);
            break;
        case 8:
            resize(image);
            break;
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";


    cin >> filename;

    image.saveImage(filename);

    return 0;
}

void grayscale(Image &image)
{
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

void Invert(Image &img)
{
    for (int i = 0; i < img.width; ++i){
        for (int j = 0; j < img.height; ++j){
            for (int k = 0; k < 3; ++k){
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

void frame (Image &image)
{
    int type_of_frame; // Normal frame or Fancy frame
    cout << "Choose 1 for normal frame or 2 for fancy frame: ";
    cin >> type_of_frame;

    if (type_of_frame == 1)
    {
        int framewidth; // Width of the frame in pixels
        cout << "Please enter the frame width you want: ";
        cin >> framewidth;

        int color_of_the_frame; // Color of the frame
        cout << "Choose the color of the frame:" << endl;
        cout << "1.Black" << endl;
        cout << "2.White" << endl;
        cout << "3.Red" << endl;
        cout << "4.Green" << endl;
        cout << "5.Blue" << endl;
        cout << "6.Yellow" << endl;
        cout << "The number of the color: ";
        cin >> color_of_the_frame;

        int R, G, B;
        switch (color_of_the_frame) 
        {
            case 1: // Black
                R = 0;   G = 0;   B = 0;
                break;
            case 2: // White
                R = 255; G = 255; B = 255;
                break;
            case 3: // Red
                R = 255; G = 0;   B = 0;
                break;
            case 4: // Green
                R = 0;   G = 255; B = 0;
                break;
            case 5: // Blue
                R = 0;   G = 0;   B = 255;
                break;
            case 6: // Yellow
                R = 255; G = 255; B = 0;
                break;
            default:
                cout << "Invalid choice! Defaulting to Black.\n";
                R = 0;   G = 0;   B = 0;
                break;
        }

        for (int i = 0; i < image.width; i++) 
        {
            for (int j = 0; j < image.height; j++) 
            {
                if (i < framewidth/2 || i >= image.width - framewidth/2 || j < framewidth/2 || j >= image.height - framewidth/2) 
                {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
        }
    }
    else
    {
        int color_of_the_frame; // Color of the frame
        cout << "Choose the color of the frame:" << endl;
        cout << "1.Champagne Gold" << endl;
        cout << "2.Emerald Green" << endl;
        cout << "3.Rose Gold" << endl;
        cout << "4.Midnight Navy" << endl;
        cout << "The number of the color: ";
        cin >> color_of_the_frame;

        int R, G, B;
        switch (color_of_the_frame) 
        {
            case 1: // Champagne Gold
                R = 247; G = 231; B = 206;
                break;
            case 2: // Emerald Green
                R = 4;   G = 99;  B = 7;
                break;
            case 3: // Rose Gold
                R = 183; G = 110; B = 121;
                break;
            case 4: // Midnight Navy
                R = 10;  G = 25;  B = 47;
                break;
            default:
                cout << "Invalid choice! Defaulting to Black.\n";
                R = 0;   G = 0;   B = 0;
                break;
        }

        int outerThick = 10;
        int innerOffset = 15; 
        int lineThick = 6;
        int cornerSize = 40; 

        for (int i = 0; i < image.width; ++i) 
        {
            for (int j = 0; j < image.height; ++j) 
            {
                bool isOuter = (i < outerThick || i >= image.width - outerThick || j < outerThick || j >= image.height - outerThick);
                bool isInner = ((i >= innerOffset && i < innerOffset + lineThick) || (i >= image.width - innerOffset - lineThick && i < image.width - innerOffset) 
                || (j >= innerOffset && j < innerOffset + lineThick) || (j >= image.height - innerOffset - lineThick && j < image.height - innerOffset));
                if (isOuter || isInner) 
                {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }

                bool isTopLeft     = (i < cornerSize) && (j < cornerSize);
                bool isTopRight    = (i >= image.width - cornerSize) && (j < cornerSize);
                bool isBottomLeft  = (i < cornerSize) && (j >= image.height - cornerSize);
                bool isBottomRight = (i >= image.width - cornerSize) && (j >= image.height - cornerSize);
                if (isTopLeft || isTopRight || isBottomLeft || isBottomRight) 
                {
                    image(i, j, 0) = R;
                    image(i, j, 1) = G;
                    image(i, j, 2) = B;
                }
            }
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


void rotate(Image &img)
{

    cout << "enter Rotation you want(90,180,270): ";
    int rotation;
    cin >> rotation;

    if (rotation == 90)
    {
        Image rotated(img.height, img.width);

        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated(img.height - 1 - j, i, k) = img(i, j, k);
                }
            }
        }
        img = rotated;
    }
    if (rotation == 180)
    {
        Image rotated(img.width, img.height);
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated(img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
                }
            }
        }
        img = rotated;
    }
    if (rotation == 270)
    {
        Image rotated(img.height, img.width);

        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated(j, img.width - 1 - i, k) = img(i, j, k);
                }
            }
        }
        img = rotated;
    }
}

void lighten_darken(Image &img)
{

    int change;
    int rate_of_change;
    cout << "Enter 1 to lighten or 2 to darken: ";
    cin >> change;
    cout << "Enter the rate of change (0-100%): ";
    cin >> rate_of_change;
    double factor = rate_of_change / 100.0;

    if (change == 1){ // Lighten the image
        for (int i = 0; i < img.width; ++i){
            for (int j = 0; j < img.height; ++j){
                for (int k = 0; k < img.channels; ++k){
                    int color_value = img(i, j, k);
                    int new_color_value = color_value + (255 - color_value) * factor;
                    img(i, j, k) = min(new_color_value, 255);
                }
            }
        }
    }

    else if (change == 2){ // Darken the image
        for (int i = 0; i < img.width; ++i){
            for (int j = 0; j < img.height; ++j){
                for (int k = 0; k < img.channels; ++k){
                    int color_value = img(i, j, k);
                    int new_color_value = color_value * (1.0 - factor);
                    img(i, j, k) = max(new_color_value, 0);
                }
            }
        }
    }
}

void resize(Image &image)
{
    int way_of_input;

    cout << "Choose 1 to enter dimensions or 2 for a scale factor: ";
    cin >> way_of_input;

    int old_width = image.width;
    int old_height = image.height;

    int new_width, new_height;

    if (way_of_input == 1)
    {
        cout << "Enter new dimensions (e.g. 800x600): ";

        char separator;
        cin >> new_width >> separator >> new_height;
    }
    else
    {
        float scale;

        cout << "Enter scale factor (e.g. 0.5 for half, 2.0 for double): ";
        cin >> scale;

        if (scale <= 0)
        {
            cout << "Scale factor must be greater than 0!" << endl;
            return;
        }

        new_width = static_cast<int>(old_width * scale);
        new_height = static_cast<int>(old_height * scale);

    }

    float width_ratio = static_cast<float>(old_width) / new_width;
    float height_ratio = static_cast<float>(old_height) / new_height;

    Image new_image(new_width, new_height);

    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            int orig_x = static_cast<int>(j * width_ratio);
            int orig_y = static_cast<int>(i * height_ratio);

            // Safety: make sure coordinates are valid
            if (orig_x >= old_width) 
            {
                orig_x = old_width - 1;
            }

            if (orig_y >= old_height)
            {
                orig_y = old_height - 1;
            }

            unsigned char red = image.getPixel(orig_x, orig_y, 0);
            unsigned char green = image.getPixel(orig_x, orig_y, 1);
            unsigned char blue = image.getPixel(orig_x, orig_y, 2);

            new_image.setPixel(j, i, 0, red);
            new_image.setPixel(j, i, 1, green);
            new_image.setPixel(j, i, 2, blue);
        }
    }

    image = new_image;
}


