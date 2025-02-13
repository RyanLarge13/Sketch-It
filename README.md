# Sketch-It

## Table of contents

- [Build the app](#build-the-application)
- [Contributions](#contributing)
- [Licensing](#licensing)

## Build the application

1. Clone the repo

```
$ git clone https://github.com/RyanLarge13/Sketch-It
```

2. Install dependencies
   You must have gtkmm, openGL and nlohmann-json3 installed to build the program

   **These are commands for Debian based systems**

   **Learn how to install these libraries for your own system**

   [gtkmm >= 4.0](https://gtkmm.org/en/download.html)

   [nlohmann-json3](https://json.nlohmann.me/integration/package_managers/)

   [openGL](https://www.opengl.org/)

```
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install libgtkmm-4.0-dev
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

nlomann-json is included as a .hpp file under src/lib for the application. Optionally you can use the link above to
install it locally and add it to CMake. Check it out form the link above

```
$ cd includes/ && wget https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
```

### Installing OpenGL on Ubuntu

```
glxinfo | grep "OpenGL"
```

If glxinfo is not installed, install it with

```
sudo apt update
sudo apt install mesa-utils
```

Install the missing libraries

```
sudo apt update
sudo apt install libgl1-mesa-dev
```

Install additional deps

```
sudo apt install libglu1-mesa-dev freeglut3-dev
```

3. Run with CMake

```
$ cd build/
$ cmake ..
$ make
$ ./sketch-it
```

## Contributing

**Clone the repository**

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature/my-feature`).
5. Open a Pull Request.

Please make sure to install clang-format on your machine if you are contributing
to help keep your pull requests and this code base consistent and maintainable

```
bash

$ sudo apt update
$ sudo apt upgrade
$ sudo apt install clang-format
```

## Licensing

This projects is licensed under the GNU 4.0 license. See the licensing here [GNU 4.0](LICENSE)
