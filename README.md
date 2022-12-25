# Final Project : Puzz Loop
![puzzloop](https://user-images.githubusercontent.com/26185179/209459587-73b2c736-1e73-48b2-acd9-e58e5109ddc2.PNG)
You may run program via downloading ```Debug/Project.exe``` only.


## Versions and Packages
- C++ 14 (or later)
- OpenGL (included in source file)
- FreeImage (included in source file)


## Installation
This installation guide is based on Visual Studio 2022.  
  
1. Open Properties on project (Alt+Enter).  
2. Set
    - configuration(C) : All configuration  
    - Platform(P) : Win32  
3. Go to ```Properties``` > ```C/C++``` > ```General``` > ```Additional include directories```, type "./include" manually.  
4. Go to ```Properties``` > ```Linker``` > ```General``` > ```Additional library directories```, type "./lib" manually.  
5. Go to ```Properties``` > ```Linker``` > ```Input``` > ```Additional dependencies```, add "glut32.lib".  
6. Go to ```Properties``` > ```Linker``` > ```Input``` > ```Additional dependencies```, add "FreeImage.lib". 
