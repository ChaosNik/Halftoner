#include <iostream>
#include <fstream>
#include "bitmap.h"
int main()
{
    int contrast_threshold;
    int widen_ammount;
    std::ifstream conf("conf.txt", std::ios::in);
    std::string dump;
    //Read comment
    getline(conf, dump);
    //Read value
    getline(conf, dump);
    contrast_threshold = stoi(dump);
    //Read comment
    getline(conf, dump);
    //Read value
    getline(conf, dump);
    widen_ammount = stoi(dump);

    int patterns [10][3][3];
    std::ifstream pat_in("patterns", std::ios::in);
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 3; ++j)
            for(int k = 0; k < 3; ++k)
                pat_in >> patterns[i][j][k];


    // for(int i = 0; i < 10; std::cout << std::endl, ++i)
    //     for(int j = 0; j < 3; std::cout << std::endl, ++j)
    //         for(int k = 0; k < 3; ++k)
    //             std::cout << patterns[i][j][k] << " ";

    Bitmap input;
    input.open("input.bmp");
    PixelMatrix old_pixels = input.toPixelMatrix();

    int grayscale_min = 255;
    int grayscale_max = 0;
    for(int i = 0; i < old_pixels.size(); ++i)
        for(int j = 0; j < old_pixels[i].size(); ++j)
        {
            int r = old_pixels[i][j].red;
            int g = old_pixels[i][j].green;
            int b = old_pixels[i][j].blue;
            int average = (r + g + b) / 3;

            if(average < grayscale_min)
                grayscale_min = average;
            if(average > grayscale_max)
                grayscale_max = average;
        }

    float multiplicator = 255.0 / (grayscale_max - grayscale_min);
    for(int i = 0; i < old_pixels.size(); ++i)
        for(int j = 0; j < old_pixels[i].size(); ++j)
        {
            int r = old_pixels[i][j].red;
            int g = old_pixels[i][j].green;
            int b = old_pixels[i][j].blue;
            int average = (r + g + b) / 3;

            old_pixels[i][j].red = (average - grayscale_min) * multiplicator;
        }

    PixelMatrix new_pixels = PixelMatrix();
    for(int i = 0; i < old_pixels.size(); ++i)
    {
        std::vector<Pixel> new_row1 = std::vector<Pixel>();
        std::vector<Pixel> new_row2 = std::vector<Pixel>();
        std::vector<Pixel> new_row3 = std::vector<Pixel>();
        for(int j = 0; j < old_pixels[i].size(); ++j)
        {
            int average = old_pixels[i][j].red;

            //int contrast_threshold = 126;
            if(average < contrast_threshold)
                average -= widen_ammount;
            else
                average += widen_ammount;
            if(average < 0)
                average = 0; 
            if(average > 255)
                average = 255;

            int black = 255;
            new_row1.push_back(Pixel(patterns[average / 26][0][0] * 255, patterns[average / 26][0][0] * 255 , patterns[average / 26][0][0] * 255));
            new_row1.push_back(Pixel(patterns[average / 26][0][1] * 255, patterns[average / 26][0][1] * 255 , patterns[average / 26][0][1] * 255));
            new_row1.push_back(Pixel(patterns[average / 26][0][2] * 255, patterns[average / 26][0][2] * 255 , patterns[average / 26][0][2] * 255));

            new_row2.push_back(Pixel(patterns[average / 26][1][0] * 255, patterns[average / 26][1][0] * 255 , patterns[average / 26][1][0] * 255));
            new_row2.push_back(Pixel(patterns[average / 26][1][1] * 255, patterns[average / 26][1][1] * 255 , patterns[average / 26][1][1] * 255));
            new_row2.push_back(Pixel(patterns[average / 26][1][2] * 255, patterns[average / 26][1][2] * 255 , patterns[average / 26][1][2] * 255));

            new_row3.push_back(Pixel(patterns[average / 26][2][0] * 255, patterns[average / 26][2][0] * 255 , patterns[average / 26][2][0] * 255));
            new_row3.push_back(Pixel(patterns[average / 26][2][1] * 255, patterns[average / 26][2][1] * 255 , patterns[average / 26][2][1] * 255));
            new_row3.push_back(Pixel(patterns[average / 26][2][2] * 255, patterns[average / 26][2][2] * 255 , patterns[average / 26][2][2] * 255));
        }
        new_pixels.push_back(new_row1);
        new_pixels.push_back(new_row2);
        new_pixels.push_back(new_row3);
    }

    for(auto row : new_pixels)
    {
        //std::cout << row.size();
        //for(auto pix : row)
        //    std::cout << "(" << pix.red << ", " << pix.green << ", " << pix.blue << ")";
        //std::cout << std::endl;
    }
    
    Bitmap output;
    output.fromPixelMatrix(new_pixels);
    output.save("output.bmp");
    system("pause");
}