# Warfront: My final project for CSCI 5229 Computer Graphics course


## Objective

I am creating a scene in which you can switch between a Airplane and a Tank. Your objective is to destroy
the Nazi Building. You can fire missiles while you are riding the tank and fire missiles as your are flying
the plane. If you are flying the plane and hit the building, you lose the game. While flying the plane, try 
firing directly at the building. Avoid head on collision as it will kill the player.

## How to play

The game begins in the flight mode. You can change from flight mode into plane mode. I have added a first person mode
that shall allow you tio navigate the scene.

Hit the mouse button to fire a missile while in plane or tank. Note, try not to hit the building while you are flying the 
plane.

In the flight mode, use the numpad. '8' and '2' shall increase and decrease the roll of the flight
'4' and '6' shall turn the flight left or right


## Goals

1. To make stuff look as authentic as possible

2. To add as much as detail as possible

3. To make things look real

4. To add some music if possible

5. To make it bright and colorful and to add to make the user feel

## Stretch Goals


## Key Bindings

| Key | Effect |
| ---- |---- |
| &uarr; | Move in forward in tank mode. Alternatively, move forward in first person mode |
| &darr; | Move in backwardin tank mode. Alternatively, move backward in first person mode |
| &larr; | Turn in left in flight/tank/first person mode |
| &rarr; | Turn in right in flight/tank/first person mode  |
| 8 | To increase roll in flight mode |
| 2 | To decrease roll in flight mode |
| 4 | To turn left in flight mode  |
| 6 | To turn right in flight mode |
| M | Toggle Mode between different views |
| A | Increase the Ambient intensity |
| Z | Decrease the Ambient intensity |
| S | Increase the specular intensity |
| X | Decrease in specular intensity |
| D | Increase the diffusion intensity |
| C | Decrease the diffusion intensity |
| E | Increase the emission |
| R | Decrease the emission |
| H | Increase the shine |
| J | Decrease the shine |
| L | Toggle for Light Mode on or off |
| O | Stop or move the light source |

## Platform information

#### Operating system           : Linux (Ubuntu)
#### Processor Architecture     : Intel X86/64

## Software Requirements

#### 1. GNU (Make), Compiler toolchain
#### 2. OpenGL graphics library

## Steps to install OpenGL and build this project

**The steps to install OpenGL on linux (ubuntu) are as follows**

1. run "sudo apt install freeglut3-dev"
2. run "sudo apt install binutils-gold g++ cmakelibglew-dev g++ mesa-common-dev build-essential libglew1.5-dev libglm-dev"
3. run "sudo apt install mesa-utils"

**The steps to build this project are as follows**

1. run "make"

**Command to clean the executable**
make clean

## Directory Structure

Here is the directory structure of my project folder




## How to build the project


## References

All the basic shapes have been made by Professor. 


