#pragma once

#include "Image_Class.h"

void grayscale(Image &image);//D

void black_and_white(Image &img);//D

void Invert(Image &img);//D

void frame (Image &image, int type_of_frame, int R, int G, int B);//D

void flip(Image &image, bool h);//D

void rotate(Image &img, int rotation);//D

void lighten_darken(Image &img, int change, int rate_of_change);//D

void resize(Image &image, int new_width, int new_height);//D

void merge(Image &image, Image &image2, bool apply_resize);//D

void sepia(Image &image);//D

void Detact_Image_Edges(Image &img);//D

void crop(Image &img, int x, int y, int width, int height);//D

void televisions(Image &img);//D

void blur(Image &image, double percentage);//D

void purple_effect(Image &img, int power_of_effect);//D

void infrared(Image &image);//D

void OilPainting(Image& image, int radius = 2, int numLevels = 20);//D

void skewImage(Image& image, double degree);//D

void contrast(Image &image, double factor);//D

void saturation(Image &image, double factor);//D

void wave(Image &image);//D

void pixelated(Image &img, int power_of_pixelated);//D

void vignette(Image &img , double power);//D

void RGB(Image &img, int slider, int channel);





