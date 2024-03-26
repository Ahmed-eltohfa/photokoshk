// main app to add filters to images
#include <iostream>
#include <cmath>
#include "Image_Class.h"
using namespace std;

void save(Image sora)
{
    string name;
    cout << "enter the saving name with the extention to save the image: ";
    cin >> name;
    sora.saveImage(name);
}

void grayScaling(string filename)
{
    Image image(filename);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = avg;
            }
        }
    }
    save(image);
}

void darken(string filename)
{
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
    save(image);
}

void lighten(string filename)
{
    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                unsigned int rqm = 20;
                if (image(i, j, k) + rqm < 255)
                {
                    image(i, j, k) += rqm;
                }
            }
        }
    }
    save(image);
}

void blackandwhite(string filename)
{
    Image image(filename);

    // for loop that make the image blackandwhite
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            // for loop that sum every pixels three colors
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3; // Calculate average
            for (int k = 0; k < 3; ++k)
            {
                if (avg >= 128)
                {
                    // if sum pf every pixels three colors > 128 make the pixel white
                    image(i, j, k) = 255;
                }
                else
                {
                    image(i, j, k) = 0;
                    // if sum pf every pixels three colors > 128 make the pixel black
                }
            }
        }
    }
    save(image);
}

void flipped(string filename)
{
    // take char from user and make sure that he choose valid
    char x;
    cout << "which flip do u want\nA)flip vetical\nB)flip Horizontal\n";
    cin >> x;
    while ((x != 'a') and (x != 'b') and (x != 'A') and (x != 'B'))
    {
        cout << "\nplease enter valid char\nwhich flip do u want\nA)flip vetical\nB)flip Horizontal\n";
        cin >> x;
    }

    Image image(filename);

    // image2 is a white copy photo from the orignal that we will pass pixel pixel from orignal to image2
    Image image2(image.width, image.height);
    for (unsigned int i = 0; i < image2.width; ++i)
    {
        for (unsigned int j = 0; j < image2.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image2(i, j, k) = 255;
            }
        }
    }
    // for loop that flip every pixel then add it to image to
    for (unsigned int i = 0; i < image.width; ++i)
    {
        for (unsigned int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int temp;
                if (x == 'a' || x == 'A')
                {
                    // if temp = i that flip vertical
                    temp = i;
                }
                else
                {
                    // if temp = i that flip horizontal
                    temp = image.width - i - 1;
                }
                // add every  flipped pixel from orignal image to image2
                image2(i, j, k) = image(temp, image.height - j - 1, k);
            }
        }
    }
    save(image2);
}

void merge(string fileName)
{
    Image img1(fileName);
    cout << "enter the second image to merge: ";
    cin >> fileName;
    Image img2(fileName);
    int minW, minH;
    minW = min(img1.width, img2.width);
    minH = min(img1.height, img2.height);

    Image merged(minW, minH);
    int s1, s2, s3, s4;
    s1 = img1.width - minW;
    s2 = img1.height - minH;
    s3 = img2.width - minW;
    s4 = img2.height - minH;
    for (int i = 0; i < merged.width; i++)
    {
        for (int j = 0; j < merged.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                merged(i, j, k) = (img1(i + s1, j + s2, k) + img2(i + s3, j + s4, k)) / 2;
            }
        }
    }

    save(merged);
}

void crop(string filename)
{
    int x, y;
    cout << "Enter x and y input as the starting point:\n ";
    cin >> x >> y;

    int w, h;
    cout << "Enter w and h as the dimensions of the area to cut:\n ";
    cin >> w >> h;

    cin >> filename;

    Image image(filename);

    Image image2(w, h); // Create a new image to store the cropped region

    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                // Copy pixel values from the original image to the cropped image
                image2(i, j, k) = image(x + i, y + j, k);
            }
        }
    }

    save(image2);
}

void edges(string fileName)
{
    Image img(fileName);

    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += img(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k)
            {
                if (avg >= 128)
                {
                    img(i, j, k) = 255;
                }
                else
                {
                    img(i, j, k) = 0;
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i < img.width - 1; ++i)
    {
        for (int j = 1; j < img.height - 1; ++j)
        {
            if (img(i, j, 0) < 128)
            {
                int cnt = 0;
                if (img(i - 1, j, 0) < 128)
                {
                    cnt++;
                }
                if (img(i, j + 1, 0) < 128)
                {
                    cnt++;
                }
                if (img(i + 1, j, 0) < 128)
                {
                    cnt++;
                }
                if (img(i, j - 1, 0) < 128)
                {
                    cnt++;
                }
                if (cnt == 4)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        img(i, j, 1) = 255;
                    }
                }
            }
        }
    }
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            if (img(i, j, 1) > 150)
            {
                img(i, j, 0) = 255;
                img(i, j, 2) = 255;
            }
        }
    }
    save(img);
}


void ResizingImages(string filename) {
    Image image(filename);
    
    //take choice from user to Enter new dimensions or Enter ratio of reduction/increase
    string choice;
    cout << "Choose resizing option:\nA) Enter new dimensions\nB) Enter ratio of reduction/increase\nEnter your choice: " << endl;
    cin >> choice;
    //make sure that choice valid
    while(choice != "A" and choice != "a" and choice != "B" and choice != "b"){
        cout << "Pls enter valid option\nA) Enter new dimensions\nB) Enter ratio of reduction/increase\nEnter your choice:  " << endl;
        cin >> choice;
    }
    
    //if choice = a user Enter new dimensions else user Enter ratio of reduction/increase
    if (choice == "A" or choice == "a") {

        //define and take new width and height
        int newWidth, newHeight;
        cout << "Enter new width and new height: ";
        cin >> newWidth >> newHeight;
        //make new photo that have the new dimensions
        Image resizedImage(newWidth, newHeight);

        //for loop that edit and take every pixel to new photo
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                int srcX = static_cast<int>(x * static_cast<float>(image.width) / newWidth);
                int srcY = static_cast<int>(y * static_cast<float>(image.height) / newHeight);
                
                // change the dimensions and doesnot change the color
                for (int c = 0; c < image.channels; c++) {
                    resizedImage(x, y, c) = image(srcX, srcY, c);
                }
            }
        }

        save(image);


    } else {

        //take ratio of reduction/increase
        float ratio;
        cout << "Enter the ratio of reduction/increase: ";
        cin >> ratio;

        //set new Width and Height
        int newWidth = static_cast<int>(image.width * ratio);
        int newHeight = static_cast<int>(image.height * ratio);

        //make new photo that have the new dimensions
        Image resizedImage(newWidth, newHeight);
        
        //for loop that edit and take every pixel to new photo
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                int srcX = static_cast<int>(x / ratio);
                int srcY = static_cast<int>(y / ratio);

                // change the dimensions and doesnot change the color
                for (int c = 0; c < image.channels; c++) {
                    resizedImage(x, y, c) = image(srcX, srcY, c);
                }
            }
        }
        //save image
        string outputFilename;
        cout << "Enter the output filename: ";
        cin >> outputFilename;
        cout << "Image saved successfully." << endl;
        resizedImage.saveImage(outputFilename);
        
    }  
} 

void blur(string filename){
    Image image(filename);
    int n;
    cout<<"\nenter the level of blur from 1 to 10: ";
    cin>>n;
    int level=1;
    if(n<0||n>10){
        cout<<"different level Please\n";
        cin>>n;
    }
    while (level<=n){
        for(int i=1;i<image.width-1;i+=2){
            for(int j=1;j<image.height-1;j+=2){
                for(int k=0;k<3;k++){
                    int avg=(image(i-1,j,k)+image(i+1,j,k)+image(i,j-1,k)+image(i,j+1,k)+image(i-1,j-1,k)+image(i+1,j+1,k)+image(i-1,j+1,k)+image(i+1,j-1,k)+image(i,j,k)*2)/10;
                    image(i-1,j,k)=avg;
                    image(i+1,j,k)=avg;
                    image(i,j-1,k)=avg;
                    image(i,j+1,k)=avg;
                    image(i-1,j-1,k)=avg;
                    image(i+1,j+1,k)=avg;
                    image(i-1,j+1,k)=avg;
                    image(i+1,j-1,k)=avg;
                    image(i,j,k)=avg;
                }
            }
        }
        level++;
    }
    save(image);
}

void frame_filter(string filename){
    cout<<"\nwhice frame do you want\nA)white frame\nB)Zebra frame\n";
    string charr;
    getline(cin,charr);
    while (charr.length()!=1){
        cout<<"Please just insert one char\n";
        getline(cin,charr);
    }
    charr=toupper(charr[0]);
    while (charr!="A"&&charr!="B"){
        cout<<"Please just insert a valid char('A','B')\n";
        getline(cin,charr);
        charr=toupper(charr[0]);
    }
    Image image(filename);
    if(charr=="A"){
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                if(i<=20i>=image.width-21j<=20j>=image.height-21){
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k)=255;
                    }
                }
            }
    }
    save(image);
    }else if(charr=="B"){
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                if(i<=20i>=image.width-21j<=20j>=image.height-21){
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k)=255;
                    }
                }
                if(i==0i==5i==10i==image.width-1i==image.width-6i==image.width-11j==0j==5j==10j==image.height-1j==image.height-6||j==image.height-11){
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k)=0;
                    }
                }
            }
        }
        save(image);
    }
    
}

void rotate(string filename){
    cout<<"A)Rotate 90\nB)Rotate 180\nC)Rotate 270\n";
    string charr;
    getline(cin,charr);
    while (charr.length()!=1){
        cout<<"Please just insert one char\n";
        getline(cin,charr);
    }
    charr=toupper(charr[0]);
    while (charr!="A"&&charr!="B"&&charr!="C"){
        cout<<"Please just insert a valid char('A','B','C')\n";
        getline(cin,charr);
    }
    if(charr=="A"){
        Image image(filename);
        Image image2(image.height,image.width);
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                for (int k = 0; k < 3; ++k){
                    image2(i, j, k)=255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                //for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k){
                    image2(image.height-j-1,i,k)=image(i,j,k);
                }
            }
        }
        save(image2);
    }else if(charr=="B"){
        Image image(filename);
        Image image2(filename);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k){
                    image2(i, j, k)=255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                //for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k){
                    image2(image.width-i-1,image.height-j-1,k)=image(i,j,k);
                }
            }
        }
        save(image2);
    }else{
        Image image(filename);
        Image image2(image.height,image.width);
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                for (int k = 0; k < 3; ++k){
                    image2(i, j, k)=255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                //for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k){
                    image2(image.height-j-1,image.width-i-1,k)=image(i,j,k);
                }
            }
        }
        for (int i = 0; i < image.width; ++i){
            for (int j = 0; j < image.height; ++j){
                //for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k){
                    image2(j,image.width-i-1,k)=image(i,j,k);
                }
            }
        }
        save(image2);
    }

void invert(string filename){
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k)=255-image(i, j, k);
            }
        }
    }
    save(image);
}


int main()
{

    while (true)
    {
        cout << "\nWelcome to our program **PhotoKoshk**\n";

        string choice;
        cout << "Choose one of these filters:\nA)grayScaling\nB)darken\nC)lighten\nD)black and white\nE)Flipped\nF)Merge two pictures\nG)Crop\nH)Get edges\nI)Resizing Image\nJ)Blur Image\nk)frame image\nl)Rotate Image\nm)Invert Image\nn)";
        getline(cin, choice);
        cout << "\n";
        choice[0] = tolower(choice[0]);
        string validChoice = "abcdefghijk";
        while (!(validChoice.find(choice) < validChoice.length()) || (choice.length() != 1))
        {
            cout << "Please insert a valid char:\n";
            getline(cin, choice);
            choice[0] = tolower(choice[0]);
        }
        // ============================================ //
        string fileName;
        while (true)
        {
            cout << "Enter the image name you want to do:\n";
            cin >> fileName;
            Image test;
            try
            {
                test.loadNewImage(fileName);
                break;
            }
            catch (const std::exception &e)
            {
                cout << "Error: unvalid image name... Please write right image name\n";
            }
        }

        if (choice == "a")
        {
            grayScaling(fileName);
        }
        else if (choice == "b")
        {
            darken(fileName);
        }
        else if (choice == "c")
        {
            lighten(fileName);
        }
        else if (choice == "d")
        {
            blackandwhite(fileName);
        }
        else if (choice == "e")
        {
            flipped(fileName);
        }
        else if (choice == "f")
        {
            merge(fileName);
        }
        else if (choice == "g")
        {
            crop(fileName);
        }
        else if (choice == "h")
        {
            edges(fileName);
        }
        else if (choice == "i")
        {
            ResizingImages(fileName);
        }
        else if (choice == "j")
        {
            blur(fileName);
        }else if(choice == "k"){
            
            frame_filter(fileName);
        }else if(choice == "l"){
            rotate(fileName);
        }else if(choice =="m"){
            invert(fileName);
        }else if(choice =="n"){
            (fileName);
        }

        cout << "\nthank you for using our program\nA)Again\nB)Exit\n";
        string goOut;
        cin.ignore();
        getline(cin, goOut);
        cout << "\n";
        goOut[0] = tolower(goOut[0]);
        while (goOut != "a" && goOut != "b" || (goOut.length() != 1))
        {
            cout << "Please insert a valid char\nA)Again\nB)Exit\n";
            getline(cin, goOut);
            goOut[0] = tolower(goOut[0]);
        }
        if (goOut == "b")
        {
            break;
        }
    }
    cout << "Bye :)";
    return 0;
}
