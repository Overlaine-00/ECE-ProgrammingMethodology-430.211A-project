# Final Project : Puzz Loop
You may run program via downloading ```Debug/Project.exe``` only.


## Versions and Packages
- C++ 14 (or later)
- OpenGL (included in source file)
- FreeImage (included in source file)


## Installation
This installation guide is based on Visual Studio 2022.  
  
1. Open Properties on project (Alt+Enter).  
2. Set
    > configuration(C) : All configuration  
    > Platform(P) : Win32  

  __Include OpenGL Library__  

3. Go to ```Properties``` > ```C/C++``` > ```General``` > ```Additional include directories```, type "./include" manually.  
4. Go to ```Properties``` > ```Linker``` > ```General``` > ```Additional library directories```, type "./lib" manually.  
5. Go to ```Properties``` > ```Linker``` > ```Input``` > ```Additional dependencies```, add "glut32.lib".  

  __Include Freeimage Library__  

6. ...
