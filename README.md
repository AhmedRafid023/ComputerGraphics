# 🎨 Computer Graphics Project - C++ & OpenGL

This project implements various **computer graphics algorithms** using **C++ and OpenGL**. The focus is on fundamental rendering techniques, line drawing, ball bouncing projection, and ray tracing.

## 🚀 Implemented Algorithms

### 📏 Bresenham's Line Drawing Algorithm
Bresenham's algorithm is an efficient way to draw lines on a raster display. It uses integer calculations to determine the closest pixel for a smooth and accurate line without floating-point operations.

### ✂️ Cyrus-Beck Line Clipping Algorithm
A parametric line-clipping algorithm used in computer graphics for convex polygon clipping. It determines the visible portion of a line segment that lies inside a convex polygonal region.

### 🔭 Projection
Projection transforms 3D objects onto a 2D screen. This project implements:
- **Orthographic Projection**: Preserves parallel lines without perspective distortion.
- **Perspective Projection**: Mimics the way the human eye perceives depth.

### 🔄 Projection with Rotation
Extends the projection technique by adding **rotational transformations**, allowing objects to be viewed from different angles before projecting them onto a 2D plane.

### 🏞️ Slope-Independent Line Drawing
Unlike traditional algorithms, this technique avoids division operations, making it efficient for real-time applications where precision and speed are crucial.

### ✈️ Visible Plane Detection
Determines which parts of a 3D object should be visible in a scene, helping to remove hidden surfaces and improve rendering performance.

### 🖼️ Bitmap Image Rendering
Uses bitmap images as textures in OpenGL to display graphical elements with pixel-perfect accuracy.

### ☀️ Ray Tracing
A powerful rendering technique that simulates realistic lighting by tracing rays from the camera to light sources. It accounts for:
- Reflection
- Refraction
- Shadows
- Light absorption

### 🏀 Ball Bouncing Simulation
This simulation demonstrates realistic **bouncing ball physics** using OpenGL. The ball follows a natural bouncing motion with gravity applied. The motion includes:
- Gravity-affected movement
- Collision detection with the ground
- Shape deformation upon impact
- Dynamic motion adjustments

## 🛠️ Tech Stack
- **C++** ⚡
- **OpenGL** 🎨
- **GLUT** (OpenGL Utility Toolkit)

## 📦 Installation
Clone the repository:
```sh
git clone https://github.com/AhmedRafid023/ComputerGraphics.git
cd computer-graphics
```

Compile and run:
```sh
g++ main.cpp -o graphics -lGL -lGLU -lglut
./graphics
```

## 🤝 Contributing
Contributions are welcome! Feel free to fork the project and submit a PR.

## 📜 License
MIT License © 2025 Ahmed Rafid

