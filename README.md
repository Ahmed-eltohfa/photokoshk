##📸 photokoshk
photokoshk is a C++ application that applies various filters to images. It leverages the stb_image and stb_image_write libraries for image processing tasks, providing a simple interface to enhance and modify images with different effects.

#✨ Features
  Apply multiple image filters such as grayscale, sepia, inversion, and more
  
  Support for common image formats (e.g., JPEG, PNG)
  
  User-friendly console interface
  
  Lightweight and fast processing

#🛠️ Technologies Used
  C++
  
  stb_image.h
  
  stb_image_write.h

#🚀 Getting Started
  Prerequisites
  C++ compiler (e.g., g++, clang++)
  
  CMake (optional, for build automation)
  
  Installation
  Clone the repository:
    git clone https://github.com/Ahmed-eltohfa/photokoshk.git
    
  Navigate to the project directory:
    cd photokoshk
    
  Compile the application:
    g++ mainApp.cpp -o photokoshk
    
  Alternatively, use CMake for building:
    mkdir build
    cd build
    cmake ..
    make

#📷 Usage
  ![image](https://github.com/user-attachments/assets/42aed531-0274-4181-bf45-1f379b9a68fd)
  
  ![image](https://github.com/user-attachments/assets/84d78625-ab0c-43bb-8fba-03292cb277c6)
  
  ![image](https://github.com/user-attachments/assets/e66f93b7-6dec-4caa-b788-8e1e3065bb16)




Run the application:
  ./photokoshk
  

#🖼️ Sample Output
  Include screenshots or examples of filtered images here to showcase the application's capabilities.

#📁 Directory Structure
  photokoshk/
  ├── imgs/                  # Directory containing sample images
  ├── Image_Class.h          # Header file for image processing class
  ├── mainApp.cpp            # Main application source code
  ├── stb_image.h            # Image loading library
  ├── stb_image_write.h      # Image writing library
  ├── temp.jpg               # Temporary file for processed images
  └── README.md              # Project documentation
  
#🤝 Contributing
  Contributions are welcome! If you have suggestions for improvements or new features, feel free to fork the repository and submit a pull request.

#📄 License
  This project is licensed under the MIT License.
