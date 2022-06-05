#include <iostream>
#include <filesystem>
#include "hop.h"
#include "out.h"
#include "bmpLib/EasyBMP.h"

// assume array size is equal to img dementions
template <typename T>
void convertToArray(BMP &img, T *arr){
    for(ull i=0; i<img.TellHeight(); ++i){
        for(ull j=0; j<img.TellWidth(); ++j){
            unsigned char colour[3] = {
                (unsigned char) img(j, i)->Red,
                (unsigned char) img(j, i)->Green,
                (unsigned char) img(j, i)->Blue
            };
            arr[i*img.TellHeight() + j] = isWhite(colour, 3) ? -1 : 1;
        }
    }
}

int main(){
    std::cout << "All images from './patterns' are going to be used to train the network.\n";
    std::cout << "Make sure, that all images are the same dimentions and please enter them (x, y of image)\n";
    ull a, b;
    std::cin >> a >> b;
    // choose floating point type : float32, double ...
    Network <float> net(a, b);
    float *arr = new float [a*b];
    
    BMP img;
    std::string stringPath = "patterns";
    std::cout << "Files loaded :\n";
    std::filesystem::path path(stringPath.c_str());
    std::string extention, userPath;
    for( auto &iter : std::filesystem::directory_iterator(stringPath.c_str()) ){
        if(!iter.is_directory()){
            std::cout << iter.path().string()  << std::endl;
            if(iter.path().string().size() > 3){
                extention = iter.path().string().substr(iter.path().string().size()-4, iter.path().string().size()-1);
                if(extention == ".bmp"){
                    img.ReadFromFile(iter.path().string().c_str());
                    convertToArray(img, arr);
                    net.push(arr, a*b);
                    net.applyHebbRule();
                    print2dImg(arr, a, b);
                }
            }
        }
    }

    std::cout << "Enter path to any file you like to process, remember about size!(q to quit)\n"; 
    while(userPath != "q"){
        std::cin >> userPath;
        if(userPath.size() > 3){
            extention = userPath.substr(userPath.size()-4, userPath.size()-1);
            if(extention == ".bmp"){ 
                img.ReadFromFile(userPath.c_str());
                convertToArray(img, arr);
                std::cout << "Image to process : \n";
                print2dImg(arr, a, b);
                net.pushForward(arr, a*b);
            }
        }
    }

    delete [] arr;

    return 0;
}