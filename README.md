# Cub3D Project

<p align="center">
  <img src="https://github.com/Degef/Cub3D/assets/103037326/3b14ec2a-c8d2-4b4c-a07f-7a4b7f757125" alt="recording1" />
</p>

## Overview

Welcome to the Cub3D project! This project was successfully completed by me and Alexander as part of our coursework at 42 Abu Dhabi. Cub3D is an exciting venture into the world of 3D graphics, built upon the fascinating ray casting technique. In this project, we convert a 2D array map into a mesmerizing 3D world.

## Graphics Library

For window graphic management in this project, we utilized the MLX library, which is a basic graphic library. MLX provided us with the essential tools and functions to create and render the 3D environment, manage user input, and handle graphical elements effectively.

## Key Features

### Ray Casting Magic

Our project harnesses the power of ray casting to transform a 2D map into a 3D wonderland. By skillfully manipulating rays, we bring depth and dimension to what was once a flat surface. This technique allows us to create the illusion of 3D environments in real-time.

...

### Textured Walls

We take our project a step further by adding textures to the walls. Each cardinal direction (north, south, east, and west) is adorned with its distinct texture, enhancing the immersive experience. The variation in textures adds realism and depth to our virtual world.

### Player Controls

Players can explore the 3D environment with intuitive controls. Use the WASD keys to move forward, backward, left, and right. To change your viewpoint, employ the arrow keys for rotation. These controls provide a smooth and engaging user experience, making exploration a breeze.

### MiniMap

To keep players oriented in our 3D world, we've implemented a minimap. This handy feature displays the player's current position on the map and provides a visual representation of all the rays being cast. It's a helpful tool for navigating the environment and understanding the ray-casting process.

### Error Handling

We've taken care to ensure robust error handling. Our project can gracefully handle various error scenarios that might arise from an invalid map. Whether it's an unclosed border or missing elements, we've got it covered. Users can expect a stable and reliable experience.

## Getting Started

To get started with Cub3D, follow these steps:
Note: This will work in a Mac or Linux environment only. Also use mlx_linux if you are trying this in linux environment. you can do this by changing the "mlx" in the Makefile to "mlx_linux". 
1. Clone this repository to your local machine.
2. Compile the project by writing "make all" at the root of the project.
3. Run the executable with a valid map as argument (./cub3D maps/cub.cub).
4. Explore the captivating 3D world we've created using the controls mentioned above.
- Note: This will work in Mac and Linux environments only. 

## Demo

![recording](https://github.com/Degef/Cub3D/assets/103037326/7419fcad-f2e9-4e52-b8c0-89155fce2a5d)

<!-- [![Demo Video](https://img.youtube.com/vi/qmxmi8o191A/0.jpg)](https://www.youtube.com/watch?v=qmxmi8o191A?autoplay=1) -->
<!-- [![Demo Video](https://img.youtube.com/vi/8E_v4l38JKw/0.jpg)](https://www.youtube.com/watch?v=8E_v4l38JKw "Cub3D") -->

## Contributions and Feedback

We welcome contributions and feedback from the community. If you have ideas for improvements or want to report issues, please open an issue or submit a pull request. Your input is valuable and can help us make Cub3D even better!
