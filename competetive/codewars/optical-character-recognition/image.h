#pragma once
#include <initializer_list>
#include <vector>

#define CUSTOM_IMAGE

struct Image
{
 int width, height;
 std::vector<unsigned> pixels;

 Image(int w, int h, unsigned pixval);
 Image(int w, int h, std::initializer_list<unsigned> data);
 Image(int w, int h, std::vector<unsigned> data);
};

Image::Image(int w, int h, unsigned pixval)
 : width(w), height(h), pixels(std::vector<unsigned>(w*h, pixval))
{}

Image::Image(int w, int h, std::initializer_list<unsigned> data)
 : width(w), height(h), pixels(data)
{}

Image::Image(int w, int h, std::vector<unsigned> data)
 : width(w), height(h), pixels(data)
{}