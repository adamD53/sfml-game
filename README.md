# ⚔️ SFML Top-Down RPG Engine

This repository hosts a 2D game engine core built with **SFML** and modern **C++**. The architecture emphasizes graphics optimization through **Batched Rendering** and clean, separated systems. The game is still not playable and is in the early phase of development.

### 🎯 Key Architectural Features

1.  **Optimized Tilemap Renderer (Batching):** The core feature is a custom tilemap rendering pipeline that drastically reduces draw calls.
      * **Multi-Layer Geometry:** The `World` class correctly utilizes separate `sf::VertexArray` buffers for each layer (batching all tiles per layer per tileset).
      * **TMX Parsing:** Map structures are loaded from **Tiled Map Editor (.tmx)** files using the efficient **TinyXML2** library.

### 📦 Dependencies

  * **SFML 3.0.2** (Graphics, Window, System)
  * **tinyxml2** (Single-file)

### Screenshots from the current state of the game

<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/7e86634c-55d0-44e1-9fa4-410225211204" />

-----

### 🔨 Building Instructions (Terminal CMake)

#### Requirements

  * C++ Compiler (GCC, Clang, MSVC) with support for **C++17/C++20**.
  * **CMake 3.10+**.

#### Step 1: Clone and Configure

```bash
git clone https://github.com/adamD53/sfml-game.git
cd sfml-game
mkdir build
cd build
```

#### Step 2: Generate Build Files

Generate the necessary build files.

```bash
cmake .. 
```
Add ```-G "Visual Studio 17 2022"``` to generate solution file.

#### Step 3: Compile the Project

Use the generic build command to compile the executable.

```bash
cmake --build . 
```
