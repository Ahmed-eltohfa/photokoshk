// main app to add filters to images
#include <iostream>
#include <cmath>
#include "Image_Class.h"
#include <stdio.h>
using namespace std;

void saveImg(Image sora)
{
    string name;
point:
    cout << "enter the saving name with the RIGHT extention to save the image: ";
    cin >> name;
    try
    {
        sora.saveImage(name);
    }
    catch (const std::exception &e)
    {
        cout << "Error: invalid extention\n";
        goto point;
    }
}

void grayScaling(string filename, Image &sora)
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
    sora = image;
}

void darken(string filename, Image &sora)
{
    Image image(filename);
    int prcntg;
    cout << "Enter the percentage to the darkeness from 1 to 100: ";
    cin >> prcntg;

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) -= image(i, j, k) * prcntg / 100;
            }
        }
    }
    sora = image;
}

void lighten(string filename, Image &sora)
{
    Image image(filename);
    int prcntg;
    cout << "Enter the percentage to the darkeness from 1 to 100: ";
    cin >> prcntg;
    prcntg /= 20;
    while (prcntg--)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    if (image(i, j, k) + 20 < 255)
                    {
                        image(i, j, k) += 20;
                    }
                }
            }
        }
    }
    sora = image;
}

void blackandwhite(string filename, Image &sora)
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
    sora = image;
}

void flipped(string filename, Image &sora)
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
    sora = image2;
}

void merge(string fileName, Image &sora)
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
    sora = merged;
}

void crop(string filename, Image &sora)
{
    int x, y;
    cout << "Enter x and y input as the starting point:\n ";
    cin >> x >> y;

    int w, h;
    cout << "Enter w and h as the dimensions of the area to cut:\n ";
    cin >> w >> h;

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
    sora = image2;
}

void edges(string fileName, Image &sora)
{
    Image img;
    blackandwhite(fileName, img);

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
    sora = img;
}

void red(string fileName, Image &sora)
{
    Image img(fileName);
    grayScaling(fileName,img);
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            for (int k = 1; k < 3; ++k)
            {
                img(i,j,k) = 0;
            }
        }
    }
    sora = img;
}

int main()
{

    cout << "\nWelcome to our program **PhotoKoshk**\n";

    while (true)
    {
        // ================= Check on the fileName ================= //
        string fileName;
        Image currentImg;
        while (true)
        {
            cout << "Enter the image name you want to apply the filter on:\n";
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
        // ===================== choose upply which func ==================== //
        while (true)
        {
            // getting started and choosing filter //
            string choice;
            cout << "Choose one of these filters:\nA)grayScaling\nB)darken\nC)lighten\nD)black and white\nE)Flipped\nF)Merge two pictures\nG)Crop\nH)Get edges\n";
            cin.ignore();
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

            if (choice == "a")
            {
                grayScaling(fileName, currentImg);
            }
            else if (choice == "b")
            {
                darken(fileName, currentImg);
            }
            else if (choice == "c")
            {
                lighten(fileName, currentImg);
            }
            else if (choice == "d")
            {
                blackandwhite(fileName, currentImg);
            }
            else if (choice == "e")
            {
                flipped(fileName, currentImg);
            }
            else if (choice == "f")
            {
                merge(fileName, currentImg);
            }
            else if (choice == "g")
            {
                crop(fileName, currentImg);
            }
            else if (choice == "h")
            {
                edges(fileName, currentImg);
            }
            else if (choice == "i")
            {
                cout << choice;
            }
            else if (choice == "j")
            {
                cout << choice;
            }
            cout << "Choose an option\nA)Save image\nB)Add more filters\nC)Skip\n";
            string choice2;
            // cin.ignore();
            getline(cin, choice2);
            choice2[0] = tolower(choice2[0]);
            while (choice2 != "a" && choice2 != "b" && choice2 != "c" || (choice2.length() != 1))
            {
                cout << "Please insert a valid char\n";
                // cin.ignore();
                getline(cin, choice2);
                choice2[0] = tolower(choice2[0]);
            }
            if (choice2 == "a")
            {
                saveImg(currentImg);
                remove("temp.jpg");
                break;
            }
            else if (choice2 == "b")
            {
                currentImg.saveImage("temp.jpg");
                fileName = "temp.jpg";
                continue;
            }
            else
            {
                remove("temp.jpg");
                break;
            }
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
