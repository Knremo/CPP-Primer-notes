cd .\build
del .\*.* -Force
cd ..
cmake.exe -S . -B build -G "MinGW Makefiles"
cd .\build
mingw32-make.exe
.\Text_Query.exe
cd ..