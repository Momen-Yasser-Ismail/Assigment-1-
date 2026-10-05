// Header 

// Adham Abdelrahman  id: 20250078  Filters: Grayscale, Flip
// Ali Yasser         id: 20250407  Filters: Black and white, Rotate
// Yehia Nabil        id: 20250742  Filters: Invert, lighten_darken
// Mo'men Yasser      id: 20251441  Filters: Frame, Resize

// File Details:
// The file contatins the C++ code of Assigment 1, we included the libaries then we put the functions and we specifed which one did which function
// The main function has the display menu function in it which contains the filter functions 
// All functions are under main for easy access of the main function

#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Adham filters
void grayscale(Image &image);
void flip(Image &image, bool h);
void sepia(Image &image);

// Ali filters
void rotate(Image &img);
void black_and_white(Image &img);
void Detact_Image_Edges(Image &img);
void televisions(Image &img);

// Yehia filters
void Invert(Image &img);
void lighten_darken(Image &img);

// Mo'men filters 
void frame (Image &image);
void resize(Image &image);

// Bounes filters
void OilPainting(Image& image, int radius, int numLevels) ;

void displaymenu(Image &image, string& name);
void save(Image &image, string &name);
bool validname(const string& filename);

int main () 
{
    string filename;

    while(true)
    {
        cout << "Pls enter image name to filter it: ";
        cin >> filename;
        if(validname(filename)){
            break;
        }
    }
    
    Image image(filename);
    displaymenu(image, filename);

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

        int base = min(image.width, image.height);

        int outerThick  = base * 0.03;
        int innerOffset = outerThick + static_cast<int>(base * 0.02);
        int lineThick   = max(1, static_cast<int>(base * 0.01));
        int cornerSize  = base * 0.08;

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
        return;
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
        return;
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
        return;
    }
    cout << "Invalid input :( Try again form the menu\n";
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
        factor = pow(factor, -1);
        for (int i = 0; i < img.width; ++i){
            for (int j = 0; j < img.height; ++j){
                for (int k = 0; k < img.channels; ++k){
                    int color_value = img(i, j, k);
                    int new_color_value = color_value * factor;
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
                    int new_color_value = color_value * factor;
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

void sepia(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
                image(i, j, 0) = min((int)(image(i, j, 0)*1.2+20), 255);
                image(i, j, 1) = min((int)(image(i, j, 1)*1.1+10), 255);
                image(i, j, 2) = max((int)(image(i, j, 2)*0.8), 0);
        }
    }
    return;
}

void OilPainting(Image& image, int radius = 2, int numLevels = 20) {
    int width = image.width;
    int height = image.height;

    Image original = image;

    vector<int> intensityCount(numLevels);
    vector<int> sumR(numLevels);
    vector<int> sumG(numLevels);
    vector<int> sumB(numLevels);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            fill(intensityCount.begin(), intensityCount.end(), 0);
            fill(sumR.begin(), sumR.end(), 0);
            fill(sumG.begin(), sumG.end(), 0);
            fill(sumB.begin(), sumB.end(), 0);

            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        int r = original(nx, ny, 0);
                        int g = original(nx, ny, 1);
                        int b = original(nx, ny, 2);

                        int intensity = (r + g + b) / 3;
                        int bucket = (intensity * numLevels) / 256;
                        if (bucket >= numLevels) {
                            bucket = numLevels - 1;
                        }

                        intensityCount[bucket]++;
                        sumR[bucket] += r;
                        sumG[bucket] += g;
                        sumB[bucket] += b;
                    }
                }
            }
            int maxBucket = 0;
            int maxCount = 0;
            for (int i = 0; i < numLevels; ++i) {
                if (intensityCount[i] > maxCount) {
                    maxCount = intensityCount[i];
                    maxBucket = i;
                }
            }
            if (maxCount > 0) {
                image(x, y, 0) = sumR[maxBucket] / maxCount;
                image(x, y, 1) = sumG[maxBucket] / maxCount;
                image(x, y, 2) = sumB[maxBucket] / maxCount;
            }
        }
    }
}

void Detact_Image_Edges(Image &img)
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
        }
    }
    Image new_image(img.width, img.height);
    int different = 30;
    for (int i = 0; i < img.width - 1; i++)
    {
        for (int j = 0; j < img.height - 1; j++)
        {
            int diffX = abs(img(i, j, 0) - img(i + 1, j, 0));
            int diffY = abs(img(i, j, 0) - img(i, j + 1, 0));

            if (diffX > different || diffY > different)
            {
                new_image(i, j, 0) = 0;
                new_image(i, j, 1) = 0;
                new_image(i, j, 2) = 0;
            }
            else
            {
                new_image(i, j, 0) = 255;
                new_image(i, j, 1) = 255;
                new_image(i, j, 2) = 255;
            }
        }
    }
    img = new_image;
}

void televisions(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {

            for (int k = 0; k < 3; k++)
            {
                if (j % 4 == 0)
                {
                    img(i, j, k) = img(i, j, k) * 0.5;
                }
            }
        }
    }
}

void displaymenu(Image &image, string &name)
{
    int input = 1;
    bool saved = true;
    do
    {
        // vector<string> filters = {"Grayscale            ", "Black and White      ", "Invert Colors        ", "Frame                ", "Flip                 ", "Rotate               ",
        //     "Brightness Adjustment", "Resize               ", "Merge Images", "Edge Detection", "Crop", "Blur", "Sunlight Effect", 
        //     "Old TV Effect", "Purple Tint", "infrared", "Skew", "Oil Painting"};
           
            cout << "########### Menu ############\n";
            cout << "*****************************\n";
            cout << "***1.Grayscale            ***\n";
            cout << "***2.Black and White      ***\n";
            cout << "***3.Invert Colors        ***\n";
            cout << "***4.Frame                ***\n";
            cout << "***5.flip                 ***\n";
            cout << "***6.rotate               ***\n";
            cout << "***7.Brightness Adjustment***\n";
            cout << "***8.Resize               ***\n";
            cout << "***9.Merge two Images     ***\n";
            cout << "***10.Edge Detection      ***\n";
            cout << "***11.Crop                ***\n";
            cout << "***12.Blur                ***\n";
            cout << "***13.Sunlight Effect     ***\n";
            cout << "***14.Old TV Effect       ***\n";
            cout << "***15.Purple Tint         ***\n";
            cout << "***16.Infrared Effect     ***\n";
            cout << "***17.Skew                ***\n";
            cout << "***18.Oil painting        ***\n";
            cout << "*****************************\n";
            cout << "***19.save image          ***\n";
            cout << "***20.Load new image      ***\n";
            cout << "***21.exit                ***\n";
            cout << "*****************************\n";
            cout << "Enter your choice: ";

            int filter_num;
            string s;
            cin >> s;

            if(s[0] - '0' >= 10 || s.size() > 2)
            {
                cout << "Invalid input :( Try again\n";
                continue;
            } 

            filter_num = stoi(s);
            
            switch(filter_num)
            {
                case 1:
                {
                    grayscale(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 2:
                {
                    black_and_white(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 3:
                {
                    Invert(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 4:
                {
                    frame(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;  
                }
                case 5:
                {
                    int c;
                    cout << 1 << ".Horizontally\n" << 2 << ".Vertically\n";
                    cout << "Enter your choice: ";
                    cin >> c;
                    flip(image, c-1);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }  
                case 6:
                {
                    rotate(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 7:
                {
                    lighten_darken(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 8:
                {
                    resize(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 9:
                {
                    //merge function Adham
                }
                case 10:
                {
                    Detact_Image_Edges(Image);
                }
                case 11:
                {
                    // Crop function Yehia
                }
                case 12:
                {
                    // Blur function Moamen
                } 
                case 13:
                {
                    sepia(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 14:
                {
                    televisions(Image);
                }
                case 15:
                {
                    // Purple Tint Yehia
                } 
                case 16:
                {
                    // Infrared Moamen
                }
                case 17:
                {
                    // Skew
                }
                case 18:
                {
                    OilPainting(image);
                    cout << "Filter applied successfully :)\n";
                    saved = false;
                    break;
                }
                case 19:
                {
                    save(image, name);
                    saved = true;
                    break;
                } 
                case 20:
                {
                    cout << "Do you want to save the changes to the current image before uploading a new one?\n";
                    cout << "1.Yes\n2.No\n";
                    cout << "Enter Your choice: ";
                    int x;
                    cin >> x;
                    if (x == 1){
                        save(image, name);
                    }
                    string filename;
                    while(true)
                    {
                        cout << "Pls enter new image name to filter it: ";
                        cin >> filename;
                        if(validname(filename))
                        {
                            break;
                        }
                        cout << "Invalid file name :(\n";
                    }
                    Image im(filename);
                    image = im;
                    name = filename;
                    break;
                }
                case 21:
                {
                    if (!saved)
                    {
                        cout << "1.Save current image\n";
                        cout << "2.Don't save\n";
                        cout << "Enter your choice: ";
                        int x;
                        cin >> x;

                        if(x == 1)
                        {
                            save(image, name);
                            return;
                        } 
                        else if (x == 2)
                        {
                            cout << "Thx \n";
                            return;
                        } 
                        else 
                        {
                            cout << "Invalid input :( Try again\n";
                        }
                    }
                    else 
                    {
                        cout << "Thx \n";
                        return;
                    }

                    break;
                }
                default:
                {
                    cout << "Pls enter valid number :(\nTry again :)\n";
                    break;
                }
            }
            
        } while (true);
}

void save(Image &image, string &name)
{
    cout << "1. Save on the same file (replace the original image)\n";
    cout << "2. Change file name\nEnter your choice: ";

    int x;
    cin >> x;

    if(x == 1)
    {
        image.saveImage(name);
        cout << "Image saved successfully :)\n";

    } 
    else if(x == 2) 
    {
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";

        string filename;
        cin >> filename;

        while (!validname(filename))
        {
            cout << "Pls enter a valid name!: ";
            cin >> filename;
        }

        name = filename;
        image.saveImage(filename);

        cout << "Image saved successfully :)\n";
    } 
    else 
    {
        cout << "Invalid input :(\nPls try again\n";
        save(image, name);
    }
}

bool validname(const string& filename) 
{
    const char* extension = strrchr(filename.c_str(), '.');
    if (extension == nullptr) 
    {
        cout << "Invalid filename: " << filename << endl;
        return false;
    }
    return true;
}
