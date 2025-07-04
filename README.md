# 🎲 42-cub3d

This project is inspired by the classic **Wolfenstein 3D**, which is considered the first-ever first-person shooter (FPS) game.</br>
It uses raycasting to project a 3D perspective onto a 2D screen, creating an immersive view inside a maze-like environment.

## 📝 Description
The program takes a map file as input, which defines the layout of walls, player's starting position, textures, and colors. It then renders a 3D scene where the player can explore using keyboard and mouse controls.

**Features**
* **Map parsing**: loads the map layout and configuration from a `.cub` file
* **Raycasting engine**: projects a 3D world from a 2D map using raycasting
* **Collision detection**: prevents player from walking through walls or closed doors
* **Minimap**: 2D top-down view of the map with player orientation
* **User interaction**:
  * Move around the map: `W`, `A`, `S`, `D` keys
  * Rotate player's view: `←` / `→` keys or drag with the left mouse button
  * Open and close doors: `SPACE` key
* **Animated sprites**:
  * 🧟 Enemy: avoid colliding with sprites wandering around, otherwise you will lose
  * 🏅 Medal: find the medal to win the game!

## 🔅 Raycasting
At the core of this project lies the **raycasting algorithm**, which - combined with the **DDA algorithm** - simulates a 3D environment based on a 2D map layout.</br>
It works by casting rays from the player’s point of view — one ray for each vertical stripe of the screen — and detecting where each ray hits a wall in the map. Based on the distance to that wall, a vertical slice of the wall is rendered, creating the illusion of depth.

1. For each vertical stripe on the screen:
    * Calculate the direction of the ray using the player’s direction and the camera plane
    * Determine the step direction and calculate delta and initial side distances
      - `delta_dist` represents how far the ray has to travel in the world to move from one x-side or y-side of a grid square to the next. It is constant for each ray and is based on the direction of the ray
      - `side_dist` represents the distance from the player's current position to the first x-side or y-side the ray will hit. It depends on the ray's direction and player's current position within the grid
      </br>
    ```c
    delta_dist[x] = fabs(1 / ray_dir[x]);
    
    if (ray_dir[x] < 0)
    {
        step[x] = -1;
        side_dist[x] = (pos[x] - map[x]) * delta_dist[x];
    }
    else
    {
        step[x] = 1;
        side_dist[x] = (map[x] + 1.0 - pos[x]) * delta_dist[x];
    }
    ```
    The same logic applies to the y-side.</br>

2. The **DDA algorithm** is used to traverse the 2D grid map and determine the first point at which each ray intersects a wall. It incrementally steps through the grid cells by comparing distances to the next x-side and y-side, and accumulates distance until a wall is hit:

    ```c
    while (hit == 0)
    {
        if (side_dist[x] < side_dist[y])
        {
            side_dist[x] += delta_dist[x];
            map[x] += step[x];
            side = 0; // vertical wall
        }
        else
        {
            side_dist[y] += delta_dist[y];
            map[y] += step[y];
            side = 1; // horizontal wall
        }
        if (map[map[y]][map[x]] == WALL)
            hit = 1;
    }
    ```
</br>

3. Calculate the perpendicular distance from the player to the wall, which will be used to scale the height of the wall slice on screen
4. Choose the appropriate texture based on the wall's direction and compute the exact texture coordinate to display
5. Draw the vertical line, sampling the texture pixel by pixel

For a more detailed explanation, check out this [tutorial](https://lodev.org/cgtutor/raycasting.html).

## 🕹️ Testing

* Compile the project (try the bonus version for a more playful experience)
  ```sh
  make
  ```
* Run the program providing the path of the selected map as argument
  ```sh
  ./cub3D maps/valid/42.cub
  ```
  > You can explore other map files in the `maps/` directory or create your own following the required format.
