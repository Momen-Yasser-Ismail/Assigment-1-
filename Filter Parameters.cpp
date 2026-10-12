#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void grayscale(Image &image)
{
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) 
            {
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
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
}

void frame (Image &image, int type_of_frame, int color_of_the_frame, int R, int G, int B)
{
    if (type_of_frame == 1)
    {
        int minDimension = min(image.width, image.height);
        double framePercentage = 0.03; 
        int framewidth = max(1, static_cast<int>(minDimension * framePercentage));

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

void flip(Image &image, bool h)
{
    if(h)
    {
        for(int i = 0;i < image.width; i++)
        {
            for(int j = 0; j * 2 < image.height; j++)
            {
                swap(image(i, j, 0), image(i, image.height - 1 - j, 0));
                swap(image(i, j, 1), image(i, image.height - 1 - j, 1));
                swap(image(i, j, 2), image(i, image.height - 1 - j, 2));
            }
        }
        return;
    }

    for(int i = 0;i * 2 < image.width; i++)
    {
        for(int j = 0; j < image.height; j++)
        {
            swap(image(i, j, 0), image(image.width-i-1, j, 0));
            swap(image(i, j, 1), image(image.width-i-1, j, 1));
            swap(image(i, j, 2), image(image.width-i-1, j, 2));
        }
    }
}

void rotate(Image &img, int rotation)
{
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
}

void lighten_darken(Image &img, int change, int rate_of_change)
{
    double factor = rate_of_change / 100.0;

    if (change == 1) // Lighten the image
    { 
        factor = pow(factor, -1);

        for (int i = 0; i < img.width; ++i)
        {
            for (int j = 0; j < img.height; ++j)
            {
                for (int k = 0; k < img.channels; ++k)
                {
                    int color_value = img(i, j, k);
                    int new_color_value = color_value * factor;
                    img(i, j, k) = min(new_color_value, 255);
                }
            }
        }
    }
    else if (change == 2) // Darken the image
    { 
        for (int i = 0; i < img.width; ++i)
        {
            for (int j = 0; j < img.height; ++j)
            {
                for (int k = 0; k < img.channels; ++k)
                {
                    int color_value = img(i, j, k);
                    int new_color_value = color_value * factor;
                    img(i, j, k) = max(new_color_value, 0);
                }
            }
        }
    }
}

void resize(Image &image, int new_width, int new_height)
{
    int old_width = image.width;
    int old_height = image.height;

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

void merge(Image &image, Image &image2, bool apply_resize)
{
    if(apply_resize)
    {
        int height = max(image.height, image2.height);
        int width = max(image.width, image2.width);

        resize(image, width, height);
        resize(image2, width, height);
    }

    int height = min(image.height, image2.height);
    int width = min(image.width, image2.width);

    Image res(width, height);

    for(int i = 0;i  < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                res(i, j, k) = (image(i, j, k) + image2(i, j, k))/2;
            }
        }
    }

    image = res;
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

void crop(Image &img, int x, int y, int width, int height) // X & Y are Coordinates 
{
    Image cropped_img(width, height);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < img.channels; ++k)
            {
                cropped_img(i, j, k) = img(x + i, y + j, k);
            }
        }
    }

    img = cropped_img;
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

void blur(Image &image, double percentage)
{
    int width = image.width;
    int height = image.height;

    if (percentage <= 0) return; // No blur needed

    int maxRadius = max(1, min(width, height) / 20); 
    int radius = max(1, static_cast<int>((percentage / 100.0) * maxRadius));
    int kernel1D = 2 * radius + 1; 

    Image temp = image;
    Image result = image;

    // PASS 1: Fast Horizontal Blur (O(1) per pixel via sliding window)
    for (int j = 0; j < height; ++j) 
    {
        int sumR = 0, sumG = 0, sumB = 0;

        // Initialize window sum for the first pixel (i = 0)
        for (int r = -radius; r <= radius; ++r) 
        {
            int sampleI = max(0, min(r, width - 1));
            sumR += image(sampleI, j, 0);
            sumG += image(sampleI, j, 1);
            sumB += image(sampleI, j, 2);
        }

        temp(0, j, 0) = sumR / kernel1D;
        temp(0, j, 1) = sumG / kernel1D;
        temp(0, j, 2) = sumB / kernel1D;

        // Slide the window across row j
        for (int i = 1; i < width; ++i) 
        {
            int addI = min(i + radius, width - 1);
            int removeI = max(0, i - radius - 1);

            sumR += image(addI, j, 0) - image(removeI, j, 0);
            sumG += image(addI, j, 1) - image(removeI, j, 1);
            sumB += image(addI, j, 2) - image(removeI, j, 2);

            temp(i, j, 0) = sumR / kernel1D;
            temp(i, j, 1) = sumG / kernel1D;
            temp(i, j, 2) = sumB / kernel1D;
        }
    }

    // PASS 2: Fast Vertical Blur (O(1) per pixel via sliding window)
    for (int i = 0; i < width; ++i) 
    {
        int sumR = 0, sumG = 0, sumB = 0;

        // Initialize window sum for the top pixel (j = 0)
        for (int r = -radius; r <= radius; ++r) 
        {
            int sampleJ = max(0, min(r, height - 1));
            sumR += temp(i, sampleJ, 0);
            sumG += temp(i, sampleJ, 1);
            sumB += temp(i, sampleJ, 2);
        }

        result(i, 0, 0) = sumR / kernel1D;
        result(i, 0, 1) = sumG / kernel1D;
        result(i, 0, 2) = sumB / kernel1D;

        // Slide the window down column i
        for (int j = 1; j < height; ++j) 
        {
            int addJ = min(j + radius, height - 1);
            int removeJ = max(0, j - radius - 1);

            sumR += temp(i, addJ, 0) - temp(i, removeJ, 0);
            sumG += temp(i, addJ, 1) - temp(i, removeJ, 1);
            sumB += temp(i, addJ, 2) - temp(i, removeJ, 2);

            result(i, j, 0) = sumR / kernel1D;
            result(i, j, 1) = sumG / kernel1D;
            result(i, j, 2) = sumB / kernel1D;
        }
    }

    image = result;
}

void purple_effect(Image &img, int power_of_effect) // Power of effect is the percenatage of the effect of the filter 
{
    float ratio = power_of_effect / 100.0;

    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            int R = img(i, j, 0);
            int G = img(i, j, 1);
            int B = img(i, j, 2);

            int target_R = min((int)((R * 1.15)+10), 255);
            int target_G = max((int)((G * 0.75)), 0);
            int target_B = min((int)((B * 1.30)+20), 255);

            img(i, j, 0) = (int)(R*(1 - ratio) + (target_R*ratio));
            img(i, j, 1) = (int)(G*(1 - ratio) + (target_G*ratio));
            img(i, j, 2) = (int)(B*(1 - ratio) + (target_B*ratio));
        }
    }
}

void infrared(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int r = image.getPixel(i, j, 0); 
            int g = image.getPixel(i, j, 1); 
            int b = image.getPixel(i, j, 2); 

            image.setPixel(i, j, 0, 255);             
            image.setPixel(i, j, 1, 255 - g);    
            image.setPixel(i, j, 2, 255 - b);
        }
    }
}

void OilPainting(Image& image, int radius = 2, int numLevels = 20) 
{
    int width = image.width;
    int height = image.height;

    Image original = image;

    vector<int> intensityCount(numLevels);
    vector<int> sumR(numLevels);
    vector<int> sumG(numLevels);
    vector<int> sumB(numLevels);

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            fill(intensityCount.begin(), intensityCount.end(), 0);
            fill(sumR.begin(), sumR.end(), 0);
            fill(sumG.begin(), sumG.end(), 0);
            fill(sumB.begin(), sumB.end(), 0);

            for (int dy = -radius; dy <= radius; ++dy) 
            {
                for (int dx = -radius; dx <= radius; ++dx) 
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) 
                    {
                        int r = original(nx, ny, 0);
                        int g = original(nx, ny, 1);
                        int b = original(nx, ny, 2);

                        int intensity = (r + g + b) / 3;
                        int bucket = (intensity * numLevels) / 256;

                        if (bucket >= numLevels) 
                        {
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

            for (int i = 0; i < numLevels; ++i) 
            {
                if (intensityCount[i] > maxCount) 
                {
                    maxCount = intensityCount[i];
                    maxBucket = i;
                }
            }
            if (maxCount > 0) 
            {
                image(x, y, 0) = sumR[maxBucket] / maxCount;
                image(x, y, 1) = sumG[maxBucket] / maxCount;
                image(x, y, 2) = sumB[maxBucket] / maxCount;
            }
        }
    }
}

void skewImage(Image& image, double degree)
{
    double rad = degree * (3.14159265358979323846 / 180.0);
    double tan_rad = tan(rad);

    int maxOffset = static_cast<int>(image.height * tan_rad);

    int newWidth = image.width + maxOffset;
    int newHeight = image.height;

    Image skewedImage(newWidth, newHeight);
    for (int j = 0; j < newHeight; ++j) 
    {
        for (int i = 0; i < newWidth; ++i) 
        {
            skewedImage.setPixel(i, j, 0, 255);
            skewedImage.setPixel(i, j, 1, 255);
            skewedImage.setPixel(i, j, 2, 255);
        }
    }

    for (int j = 0; j < image.height; ++j) 
    {
        int shifti = static_cast<int>((image.height - 1 - j) * tan_rad);

        for (int i = 0; i < image.width; ++i) 
        {
            int newi = i + shifti;

            if (newi >= 0 && newi < newWidth) 
            {
                skewedImage.setPixel(newi, j, 0, image.getPixel(i, j, 0)); //[cite: 2]
                skewedImage.setPixel(newi, j, 1, image.getPixel(i, j, 1)); //[cite: 2]
                skewedImage.setPixel(newi, j, 2, image.getPixel(i, j, 2)); //[cite: 2]
            }
        }
    }

    image = skewedImage;
}



// source https://apxml.com/courses/introduction-to-computer-vision/chapter-3-basic-image-processing-techniques/point-operations-contrast-adjustment

void contrast(Image &image, double factor)
{
    
    double alpha = 1 + factor/100;
    double beta = 128*(1-alpha);

    for(int i = 0;i  < image.width; i++)
    {
        for(int j = 0; j < image.height; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image(i, j, k) = clamp((int)round(alpha * (image(i, j, k)) + beta), 0, 255);
            }
        }
    }
}

void saturation(Image &image, double factor)
{
    
    double alpha = 1 + factor/100;

    for(int i = 0;i  < image.width; i++)
    {
        for(int j = 0; j < image.height; j++)
        {
            double gray = 0.299 * image(i, j, 0) + 0.587 * image(i, j, 1) + 0.114 * image(i, j, 2);

            for(int k = 0; k < 3; k++)
            {
                image(i, j, k) = clamp((int)(gray + (image(i, j, k) - gray) * alpha), 0, 255);            
            }
        }
    }
}

void wave(Image &image)
{ 
    Image newImage(image);
    for(int i = 0; i < image.width; i++)
    {
        for(int j = 0; j < image.height; j++)
        {
            int srci = i + 10.0 * sin(2 * 3.14159265358979323846 * j / 80.0);
            int srcj = j;


            if(srci >= image.width)srci = image.width - 1;
            if(srci < 0)srci = 0;

            if(srcj >= image.height)srcj = image.height - 1;
            if(srcj < 0)srcj = 0;

            for(int c = 0; c < 3; c++)
                newImage(i, j, c) = image(srci, srcj, c);
        }
    }
    
    image = newImage;
}

void pixelated(Image &img, int power_of_pixelated)
{
    int i_w = img.width;
    int i_h = img.height;
    int d_w = max(4, i_w / max((50-power_of_pixelated/2),10));
    int d_h = max(4, i_h / max((50-power_of_pixelated/2),10));
    int new_width = i_w/d_w;
    int new_height = i_h/d_h;

    Image resized_img(new_width, new_height);

    for (int i = 0; i < new_width; ++i)
    {
        for (int j = 0; j < new_height; ++j)
        {
            for (int k = 0; k < img.channels; ++k)
            {
                resized_img(i, j, k) = img(min(i * d_w, i_w - 1), min(j * d_h, i_h - 1), k);
            }
        }
    }

    int new_width2 = i_w;
    int new_height2 = i_h;

    Image resized_img2(new_width2, new_height2);

    for (int i = 0; i < new_width2; ++i)
    {
        for (int j = 0; j < new_height2; ++j)
        {
            for (int k = 0; k < img.channels; ++k)
            {
                resized_img2(i, j, k) = resized_img((min(i / d_w, new_width - 1)), (min(j / d_h, new_height - 1)), k);
            }
        }
    }

    img = resized_img2;
}

void vignette(Image &img , double power)
{
    double factor = ((power)/50.0);
    double centerX = img.width / 2.0;
    double centerY = img.height / 2.0;

    double maxDistance = sqrt(centerX * centerX + centerY * centerY); // distance between center and corners

    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            double dx = i - centerX; // distance in x axis
            double dy = j - centerY; // distance in y axis

            double distance = sqrt(dx * dx + dy * dy); // full distance eq
            double ratio = distance / maxDistance;

            double factor2 = 1.0 - factor * ratio * ratio;

            for (int k = 0; k < img.channels; ++k)
            {
                img(i, j, k) = clamp((int)(img(i, j, k) * factor2),0, 255);
            }
        }
    }
}

void RGB(Image &img, int slider, int channel)
{
    int r_slider = 0;
    int g_slider = 0;
    int b_slider = 0;

    if(channel == 0)
    {
        r_slider = slider + 100;
    } 
    else if(channel == 1)
    {
        g_slider = slider + 100;
    }
    else 
    {
        b_slider = slider + 100;
    }

    double r_ratio = r_slider /100.0  ;
    double g_ratio = g_slider /100.0 ;
    double b_ratio = b_slider /100.0 ;

    for(int i = 0; i<img.width; ++i)
    {
        for(int j = 0; j<img.height; ++j)
        {
            int r = img(i, j, 0) * r_ratio ; 
            int g = img(i, j, 1) * g_ratio ; 
            int b = img(i, j, 2) * b_ratio ; 
            
            img(i, j, 0) = clamp(r, 0, 255) ;
            img(i, j, 1) = clamp(g, 0, 255) ;
            img(i, j, 2) = clamp(b, 0, 255) ;
        }
    }
}
