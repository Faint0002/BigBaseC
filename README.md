# BigBaseC
 An improved BigBaseC with a more usable code base and classes. This was made in about 3 days, and has no apparent issues.
 I'm still working out some kinks so please keep that in mind.

# License:
- This project is licensed under the MIT License
- Please visit https://opensource.org/licenses/MIT for all terms and conditions related to this project.

# Issues
- This is detected you shoud not use it in GTA Online.
- You'll need to do some things yourself, such as adding more classes.

# Projects used
- BigBaseC (github.com/Poccaking/BigBaseC)
- MinHook (github.com/TsudaKageyu/minhook)
- Universal_GTAO_Booster (github.com/QuickNET-Tech/Universal_GTAO_Booster) (This was used for it's signature scanner and logger, thanks Quick for allowing me to use it)

# Info
- This base is STRICTLY for educational purposes and I am not affilated with any projects linked to this. Use at your own risk.
- This is primarly made in C, so try not to judge the code too much. It's been a very long time since I've used C

# Compiling
- On windows:
```bash
cd source
mkdir build
cd build
cmake ..
```
this will give you Visual Studio solution.

Note: cmake is required for this to work.

- On linux:
Install MinGW and cmake.
Debian:
```bash
sudo apt install gcc-mingw-w64 g++-mingw-w64 binutils-mingw-w64 cmake
```
  
Arch:
```bash
sudo pacman -S mingw-w64-gcc mingw-w64-binutils mingw-w64-headers cmake
```

Generate and build the project.
```
cd source
mkdir build && cd build
cmake .. -D CMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -D CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_SYSTEM_NAME=Windows -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release
make
```

# Contacts
Email - diorcheats.vali@gmail.com
Discord - Vali#0004
Reddit - diorvali
YouTube - Falling Star
