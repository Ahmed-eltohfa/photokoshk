// main app to add filters to images
#include <iostream>
#include "Image_Class.h"
using namespace std;

void grayScaling()
{
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; // Initialize average value

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

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
}

void darken()
{
    string filename;
    cout << "Pls enter colored image name to turn to darken: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) -= image(i, j, k) / 2;
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
}

void lighten()
{
    string filename;
    cout << "Pls enter colored image name to turn to lighten: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                unsigned int rqm = image(i, j, k) * .5;
                if (image(i, j, k) + rqm < 255)
                {
                    image(i, j, k) += rqm;
                }
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
}
void blackandwhite() {
    
    //take image name
    string filename;
    cout << "Pls enter colored image name to turn to blackandwhite: ";
    cin >> filename;
    Image image(filename);

    //for loop that make the image blackandwhite
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; 
            //for loop that sum every pixels three colors 
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); 
            }
            avg /= 3; // Calculate average
            for (int k = 0; k < 3; ++k) {
                if (avg >= 128){
                    //if sum pf every pixels three colors > 128 make the pixel white
                    image(i, j, k)=255;
                }
                else{
                    image(i, j, k)=0;
                    //if sum pf every pixels three colors > 128 make the pixel black
                }
            } 
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);
}
void flipped() {
    //take char from user and make sure that he choose valid 
    char x;
    cout<<"which flip do u want\nA)flip vetical\nB)flip Horizontal\n";
    cin>>x;
    while((x !='a') and (x !='b') and (x!='A') and (x!='B')){
        cout<<"\nplease enter valid char\nwhich flip do u want\nA)flip vetical\nB)flip Horizontal\n";
        cin>>x;
    }
    //take image name
    string filename;
    cout << "Pls enter image name to be flipped : ";
    cin >> filename;
    Image image(filename);

    // image2 is a white copy photo from the orignal that we will ass pixel pixel from orignal to image2
    Image image2(filename);
    for (unsigned int i = 0; i < image.width; ++i) {
        for (unsigned int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
               image2(i, j, k)=255; 
            }
        }
    }
    //for loop that flip every pixel then add it to image to 
    for (unsigned int i = 0; i < image.width; ++i) {
        for (unsigned int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
               int temp;
               if(x=='a' or x=='A'){
                    //if temp = i that flip vertical
                    temp=i;
               }else{
                    //if temp = i that flip horizontal
                    temp=image.width-i-1;
               }
               //add every  flipped pixel from orignal image to image2 
               image2(i, j, k)=image(temp,image.height-j-1,k); 
            }
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image2.saveImage(filename);
}


int main()
{
    
    return 0;
}
