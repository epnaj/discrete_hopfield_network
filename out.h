#ifndef out_h
#define out_h

#define ull unsigned long long
#include <iostream>
#include <string>

bool isWhite(const unsigned char *colourPointer, const int &c_size){
    for(int i=0; i<c_size; ++i){
        if(colourPointer[i] != 255)
            return false;
    }
    return true;
}

template <typename T>
void print2dImg(T *arr, ull rows, ull cols){
    for(ull i=0; i<rows; ++i){
        for(ull j=0; j<cols; ++j){
            std::cout << (arr[i*rows + j] > 0 ? 'x' : ' ');
        }
        std::cout << std::endl;
    }
}

#endif