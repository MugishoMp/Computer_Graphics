# Grass Simulation Project

This project simulates a field of grass using Worley noise and shader techniques. It creates a dynamic and visually appealing grass field that responds to Worley noise patterns.

## How to Run

To run this project, follow these steps:

1. **Install Dependencies:** Make sure you have the following dependencies installed on your system:

   - [SDL2](https://www.libsdl.org/): SDL2 is a cross-platform development library designed for 2D and 3D applications. It provides features for window creation, input handling, and more.

   On Linux (Debian-based systems such as Ubuntu), you can use the package manager to install SDL2:

   ```bash
   sudo apt-get install libsdl2-dev
   ```

   Other packages that you might potentially want to need
   
   ```bash
   sudo apt-get install freeglut3-dev
   sudo apt-get install mesa-common-dev
   sudo apt-get install libglu1-mesa-dev
   ```

2. **Header Files (GLAD and GLM):** The header files for GLAD and GLM are already included in the project. You don't need to install them separately. These headers are included to simplify the setup process on Linux machines.

3. **Build the Project:** Build the project using the provided build scripts or commands. Building typically involves compiling your code and generating executable files or assets. 

   ```bash
   make
   ```

4. **Run:** Execute the project to see the grass simulation in action. Running the project should launch the application and display the grass simulation on your screen. You may need can drag the simulation to move it around

   ```bash
   ./a.out
   ```

Ensure that you have SDL2 correctly installed on your Linux system using the provided installation command. The header files for GLAD and GLM are already included in the project, simplifying the setup process for Linux users.

## Project Overview

Here is a detailed overview of the steps involved in creating this grass simulation:

1. **Worley Noise Generation:**
   - In this step, Worley noise is generated. Worley noise is a type of noise function used to decide where and at what point each grass blade moves within the field.
   - **Formula:** Worley noise is calculated using a formula that generates pseudo-random patterns in space. It assigns values to points in space based on their proximity to other points. The result is a pattern that resembles cellular or Voronoi patterns.
   - **Use:** The Worley noise values are used to determine the movement and behavior of individual grass blades. Each point in the Worley noise pattern corresponds to a specific grass blade, and the noise values control attributes like color, position, and sway.

2. **Mesh Creation:**
   - Two distinct mesh models are created: one representing a single grass blade and another representing the entire grass field.
   - **Use:** Meshes define the geometry and structure of objects in the 3D scene. The grass blade mesh defines the shape of an individual blade, while the field mesh represents the overall layout of the grass. These meshes serve as the visual representation of the grass in the simulation.

3. **Shader Usage:**
   - Separate shaders are implemented for each mesh to control their appearance and behavior.
   - **Use:** Shaders are programs that run on the GPU and determine how objects are rendered. For this project, shaders are essential for achieving realistic grass rendering. They control aspects such as color, lighting, and movement. By using separate shaders for each mesh, you can fine-tune the visual effects to create a natural and dynamic grass field.

4. **Instancing:**
   - Instancing is a technique used to efficiently generate multiple instances of an object with slight variations.
   - **Use:** Instancing is applied to populate the grass field with numerous blades of grass. Each instance is created with different proportions and initial rotations. This diversity adds realism to the grass field, mimicking the natural variations found in real grass.

5. **Worley Noise in Shaders:**
   - Worley noise is applied within the shaders to influence both color and movement.
   - **Use:** In the fragment shader, Worley noise is used to gradually change the color of the grass, creating a visually dynamic effect. In the vertex shader, it controls the movement of the grass blades. The Rodriguez rotation formula is applied to rotate the grass blades based on the Worley noise values. This rotation occurs around the sway yaw and sway pitch, simulating the swaying motion of grass in the wind.

6. **Color Adjustment:**
   - The fragment shader is utilized to adjust the colors, ensuring that the grass appears green and natural.
   - **Use:** The fragment shader is responsible for fine-tuning the color of the grass. It ensures that the grass blades have a vibrant and natural green color, enhancing the overall visual appeal of the simulation.

7. **Increasing Blade Instances:**
   - To enhance the realism of the simulation, the number of instanced grass blades is increased.
   - **Use:** Increasing the number of instances results in a denser grass field, making it more visually appealing and lifelike.

8. **Completion:**
   - At this stage, the grass simulation is complete and ready to run. Users can interact with the simulation to observe the realistic grass movement and colors.

## Formulas

In this section, we provide further details on the key formulas used in the project:

- **Worley Noise Formula:** Worley noise is generated using a formula that calculates the distance between points in space. The formula assigns values to each point based on its proximity to other points, creating a distinctive pattern resembling cells or Voronoi patterns.

- **Rodriguez Rotation Formula:** The Rodriguez rotation formula is applied to rotate grass blades based on the Worley noise values. It performs rotations around the sway yaw and sway pitch, simulating the swaying motion of grass in response to the noise.

This project combines Worley noise, shaders, and instancing techniques to create an engaging and visually captivating grass field. The incorporation of these elements results in a dynamic and immersive experience for users.

Feel free to customize and further improve upon this project for your specific needs or experiments.

## License

This project is licensed under the [MIT License](LICENSE).