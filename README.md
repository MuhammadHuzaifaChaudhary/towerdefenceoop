# Castle Conflict - Tower Defense Game
### OOP Semester Project | SFML 3.0.2 | C++

## About the Game
Castle Conflict is a tower defense game built in C++ using SFML 3.0.2.
Defend your kingdom by placing towers on the map to stop waves of enemies
from reaching the exit. Earn gold by defeating enemies and spend it on
powerful towers. Survive all 5 waves to win!

### Features
- 5 progressive waves with increasing difficulty
- 5 unique tower types (Cannon, Archer, Wizard, Electric, Bow)
- 6 enemy types including Healer and Bomb enemies
- Main Menu, Leaderboard, Settings, Instructions screens
- Background music and sound effects
- Customizable map backgrounds and path textures
- Leaderboard with top 5 high scores saved to file

---

## How to Install SFML and Run the Game

### Step 1 - Download SFML
Search "SFML download" on Google and download version 3.0.2.
Extract it to your Desktop or any folder you prefer.

### Step 2 - Create Project in Visual Studio
Open Visual Studio and create an empty C++ project.
Build it once to generate the exe file.
Then right click on your project name and go to Properties
(or click Project at the top and select Properties at the bottom).

### Step 3 - Set Configuration
At the top of Properties window select:
- Configuration: Debug
- Platform: Active x64

Then in the General tab find C++ Language Standard and select ISO C++20.

### Step 4 - Add Include Directory
Go to C/C++ > General > Additional Include Directories.
Click the small arrow and choose Edit.
Click the small folder icon at the top.
Navigate to your SFML folder and select the include folder.
Click OK.

### Step 5 - Add Library Directory
Go to Linker > General > Additional Library Directories.
Same procedure as above but select the lib folder from your SFML folder.
Click OK.

### Step 6 - Add Linker Dependencies
Go to Linker > Input > Additional Dependencies.
Add these lines:

```
sfml-graphics.lib
sfml-window.lib
sfml-system.lib
sfml-audio.lib
sfml-network.lib
```

### Step 7 - Copy DLL Files
Right click on your project name in Visual Studio and click
"Open Folder in File Explorer".
You will see an x64 folder. Copy these DLL files and paste them
both inside the x64 folder and outside it:

```
sfml-window-d-3.dll
sfml-system-d-3.dll
sfml-network-d-3.dll
sfml-graphics-d-3.dll
sfml-audio-d-3.dll
```

### Step 8 - Add Project Files
In the same location outside the x64 folder paste:
- All .cpp files
- All .h files
- assets folder

### Step 9 - Build and Run
Click Build Solution and then Run.
Enjoy the game!

---

## Controls
- Mouse Left Click - Place tower on map
- Keys 1 to 5 - Select tower type
- Exit Button (top right of UI panel) - Return to main menu

## Known Issues
- Volume range is 0 to 300
- Compiler shows warnings for internal linkage constants (harmless)

## Built With
- C++ (ISO C++20)
- SFML 3.0.2
- Visual Studio 2022
