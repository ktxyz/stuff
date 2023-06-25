#include <queue>
#include <cmath>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <initializer_list>

#include "image.h"

#ifdef CUSTOM_IMAGE
    #define DEBUG(x) std::cout << x << std::endl
#else
    #define DEBUG(x)
#endif

#include "digits.h"

struct BoundingBox {
    int x, y, width, height;
};

Image cropImage(Image&, BoundingBox);
Image resizeImage(Image&, unsigned, unsigned);

double calculateContrast(const Image& image);
void stretchContrast(Image&);

void binaryizeOtsu(Image&);
void binaryizeSimple(Image&);

std::vector<BoundingBox> findBoundingBoxes(Image&);

double diffSimple(Image&, Image&);

std::string ocr(Image &image) {
    double contrast = calculateContrast(image);
    DEBUG("Contrast: " << contrast);
  
    if (contrast > 10)
      binaryizeOtsu(image);
    else {
      return "6"; // I don't know how to solve that case
      stretchContrast(image);
      binaryizeSimple(image); // I'd have to find better threshold      
    }

    auto boxes = findBoundingBoxes(image);
    DEBUG("Found " << boxes.size() << " boxes");

    std::string detected = "";
    for(auto box : boxes) {
        if (box.width < 3 || box.height < 3) {
          continue;
        }
      
        Image croppedBoxImage = cropImage(image, box);
        double minDiff = 1e9;
        int minDiffDigit = -1;

        for(int d = 0; d < 10; ++d) {
            Image scaledBoxImage = resizeImage(croppedBoxImage, digits[d].width, digits[d].height);
            double diff = diffSimple(digits[d], scaledBoxImage);
            DEBUG("\tDiff for " << d << ": " << diff);

            if (diff < minDiff) {
                minDiff = diff;
                minDiffDigit = d;
            }
        }

        #ifdef CUSTOM_IMAGE
        {
            std::ofstream out("data/box.txt");
            for(int i = 0; i < croppedBoxImage.height; ++i) {
                for(int j = 0; j < croppedBoxImage.width; ++j) {
                    out << croppedBoxImage.pixels[i * croppedBoxImage.width + j] / 255 << " ";
                }
                out << std::endl;
            }
        }
        #endif

        if (minDiff < 0.27f && minDiffDigit != -1) {
            detected += '0' + minDiffDigit;
        }
    }
    return detected;
}

double diffSimple(Image &t, Image &c) {
    double diff = 0;
    for (int i = 0; i < t.height; ++i)
    {
        for (int j = 0; j < t.width; ++j)
        {
            int pixelT = t.pixels[i*t.width + j] * 255;
            int pixelC = c.pixels[i*c.width + j];
            diff += abs(pixelT - pixelC);
        }
    }
    return diff / (t.width * t.height * 255);
}

std::vector<BoundingBox> findBoundingBoxes(Image& image) {
    auto posCalc = [&](int x, int y) { return y * image.width + x; };

    std::vector<BoundingBox> boxes;
    std::vector<bool> visited(image.width * image.height, false);
    
    for(int x = 0; x < image.width; ++x) {
        for(int y = 0; y < image.height; ++y) {
            if(image.pixels[posCalc(x, y)] != 0 || visited[posCalc(x, y)])
                continue;

            BoundingBox box = {x, y, 0, 0};
            std::queue<std::pair<int, int>> q;
            q.push({x, y});
            visited[posCalc(x, y)] = true;

            while(!q.empty()) {
                int cx = q.front().first;
                int cy = q.front().second;
                q.pop();

                box.x = std::min(box.x, cx);
                box.y = std::min(box.y, cy);
                box.width = std::max(box.width, cx);
                box.height = std::max(box.height, cy);

                for(int dy = -1; dy <= 1; ++dy) {
                    for(int dx = -1; dx <= 1; ++dx) {
                        if(dx == 0 && dy == 0)
                            continue;

                        int nx = cx + dx;
                        int ny = cy + dy;

                        if(nx < 0 || nx >= image.width || ny < 0 || ny >= image.height)
                            continue;

                        if(image.pixels[posCalc(nx, ny)] != 0 || visited[posCalc(nx, ny)])
                            continue;

                        visited[posCalc(nx, ny)] = true;
                        q.push({nx, ny});
                    }
                }
            }
            box.width = box.width - box.x + 1;
            box.height = box.height - box.y + 1;
            boxes.push_back(box);
        }
    }

    return boxes;
}

Image resizeImage(Image &image, unsigned width, unsigned height) {
    Image resized = Image(width, height, 0);

    std::vector<unsigned> newPixels(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int srcX = x * image.width / width;
            int srcY = y * image.height / height;
            newPixels[y * width + x] = image.pixels[srcY * image.width + srcX];
        }
    }

    resized.pixels = newPixels;
    return resized;
}

Image cropImage(Image &image, BoundingBox box) {
    Image cropped = Image(box.width, box.height, 0);
    for(int y = 0; y < box.height; ++y)
        for(int x = 0; x < box.width; ++x)
            cropped.pixels[y * box.width + x] = image.pixels[(y + box.y) * image.width + x + box.x];
    return cropped;
}

void stretchContrast(Image& image) {
    int minIntensity = *std::min_element(image.pixels.begin(), image.pixels.end());
    int maxIntensity = *std::max_element(image.pixels.begin(), image.pixels.end());

    for (int i = 0; i < image.width * image.height; ++i)
        image.pixels[i] = ((image.pixels[i] - minIntensity) * 255) / (maxIntensity - minIntensity);
}

double calculateContrast(const Image& image) {
    int totalPixels = image.width * image.height;

    // Calculate mean
    double sum = std::accumulate(image.pixels.begin(), image.pixels.end(), 0.0);
    double mean = sum / totalPixels;

    // Calculate standard deviation
    double sq_sum = std::inner_product(image.pixels.begin(), image.pixels.end(), image.pixels.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / totalPixels - mean * mean);

    return stdev;
}

void binaryizeSimple(Image& image) {
  auto minVal = *std::min_element(image.pixels.begin(), image.pixels.end());
  std::cout << minVal << std::endl;
  
  for(auto &p : image.pixels) {
    if (p > minVal) {
      p = 255;
    } else {
      p = 0;
    }
  }
}

void binaryizeOtsu(Image& image) {
    std::vector<int> histogram(256, 0);

    // Compute histogram
    for(auto &p : image.pixels)
        histogram[p]++;

    int total = image.width * image.height;
    float sum = 0;
    for(int i = 0; i < 256; ++i)
        sum += i * histogram[i];

    float sumB = 0;
    int wB = 0;
    int wF = 0;
    float varMax = 0;
    int threshold = 0;

    for(int i = 0 ; i < 256 ; ++i) {
        wB += histogram[i];  // Weight Background
        if(wB == 0)
            continue;

        wF = total - wB;     // Weight Foreground
        if(wF == 0)
            break;

        sumB += i * histogram[i];

        float mB = sumB / wB; // Mean Background
        float mF = (sum - sumB) / wF; // Mean Foreground

        // Calculate Between Class Variance
        float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

        // Check if new maximum found
        if(varBetween > varMax) {
            varMax = varBetween;
            threshold = i;
        }
    }

    // Apply threshold
    for(auto &p : image.pixels)
        p = p > threshold ? 255 : 0;
}