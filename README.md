# discrete_hopfield_network

In this project I have used this library to read and load .bmp images : http://easybmp.sourceforge.net/ .
The way program reads an image, is if the pixel is not white, it's black - so active, if the pixel is white - it's inactive.
That's why in the example images with noise you may see green and red dots or curves instead of the purely black addition of "dust".
All images in patterns directory are complete and meant to be used for network training (reader can see only those that are 
in "patterns" folder, but doesn't search recursively), in "noisy" directory you can find images that are test images.

To complile use two files - main.cpp and bmpLib/EasyBMP.cpp.
