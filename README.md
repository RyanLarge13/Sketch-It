# Sketch-It

## Table of contents

- [Build the app](#build-the-application)
- [Contributions](#contributing)
- [Licensing](#licensing)

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
```

nlomann-json is included as a .hpp file under src/lib for the application. Optionally you can use the link above to
install it locally and add it to CMake. Check it out form the link above

```
$ cd includes/ && wget https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
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

## Licensing

This projects is licensed under the GNU 4.0 license. See the licensing here [GNU 4.0](LICENSE)
