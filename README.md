# BATTLE TANK

Battle Tank is an Unreal Engine 4, Open World, Head-to-Head Combat game with simple AI, terrain and advanced control systems based on https://www.udemy.com/course/unrealcourse by Ben Tristem


## GAME DESIGN DOCUMENT (GDD)

1. CONCEPT
* Open World Head-to-Head Combat Game
* Terrain provides tactical advantage
* Flow and Feel are the main Focus

2. RULES
*	Free mobility up to the mountains which enclose the field
*	Limited Health and Ammo
*	Hits deduct Health
*	Blasts burn Ammo
*	Last man standing wins

3. REQUIREMENTS
*	SFX: Barrel movement, Engine, Gun fire, Explosions, , Turret movement
*	Static Mesh: Simple Tank comprising tracks, Barrel, Body and Turret 
*	Textures: Field, Mountains, Metal
*	Music: Background loop

4. ITERATIVE CYCLE
* World -> Tank -> Controls -> Player 2 -> UI ->

5. AIMING ARCHITECTURE
* Tank AI Controller using AimAt(Player) & Tank Player Controller using AimAt(Crosshair) -> Tank Delegates To -> Tank Aiming Component -> Blueprint Event Handles Rotations
