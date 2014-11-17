#MESH OFFSET PROCESS FOR AXEL 2.3.1

#SOFTWARE: 
   This process is a plugin of axel (http://axel.inria.fr/). 
#What does it do?
   This plugin is for computing the offset of mesh in distance d. 
   The results is quite good. But of course, there are some works to make it better.
   If you are interested in this project, feel free to contact me to discuss. 
#How to build it? 
   At first, you have to build axel SDK: follow this tutorial: 
       http://axel.inria.fr/user_documentations/45.
  
  After that: 
       In Windows, you can use CMake 2.8 to create the project, use Visual Studio to build.   
       (Tested with Visual Studio 2008, windows 7 - for axel SDK, check out the tutorial.)
##Problem? 
* Problem 1:
   - OS: Windows 7.  
   - Content: unistd.h problem  
   - Solution: change unistd.h to io.h.
   
* Problem 2: 
   - OS: Windows 7
   - Content: CMake + Visual Studio 2010 when build VTK, fail from beginning. 
   - Solution: Check .Net Frameworks version.   
               If it's differences with version 4.0,Uninstall .Net,reinstall .Net Frameworks 4.0.
      
#Contact: 
   Email: peterpans2014@gmail.com
