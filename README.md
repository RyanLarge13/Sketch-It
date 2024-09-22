# Sketch-It

## Build the application

1. Clone the repo

```
$ git clone https://github.com/RyanLArge13/Sketch-It
```

2. Install dependencies
   You must have gtkmm, openGL and nlohmann-json3 installed to build the program

   **These are commands for Debian based systems**

   **Learn how to install these libraries for your own system**

   [gtkmm >= 4.0](https://gtkmm.org/en/download.html)

   [jnlohmann](https://json.nlohmann.me/integration/package_managers/)

   [openGL](https://www.opengl.org/)

```
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install libgtkmm-4.0-dev
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
$ cd includes/ && wget https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
```

3. Run with CMake

```
$ cd build/
$ cmake ..
$ make
$ ./sketch-it
```
