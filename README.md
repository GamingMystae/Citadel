# Citadel

**Citadel** is a **3D first-person shooter project** created during the **second year of college** in **Unreal Engine 5.4** using **C++**.

The project focuses on core FPS gameplay systems such as player shooting, enemy AI, damage and shield mechanics, behavior trees, HUD flow, and win/lose game states.

---

## Overview

In **Citadel**, the player controls a first-person combat character and must survive enemy encounters by shooting AI-controlled opponents while managing health and shield energy.

The game combines several important FPS systems, including:

- first-person combat
- hitscan weapon firing
- enemy AI using Behavior Trees and Blackboards
- shield activation
- damage and health management
- HUD and end-game screen flow
- kill-all-enemies win condition

This project was created as a second-year Unreal Engine 5.4 assignment and helped me practice how multiple FPS gameplay systems connect together inside a small but complete combat prototype.

---

## Gameplay Features

- **First-person shooter gameplay**
  - player-controlled combat character
  - shooting with a weapon attached to the character mesh
  - first-person aiming through player view direction

- **Gun and combat system**
  - hitscan-based firing using line trace
  - muzzle flash Niagara effects
  - muzzle sound and bullet impact sound
  - bullet impact Niagara effects
  - point damage applied to hit actors

- **Shield system**
  - player can activate and deactivate a shield
  - shield has its own energy value
  - shield is visually represented through a mesh component

- **Health and damage**
  - player and enemies use health values
  - health percentage can be queried for UI
  - shield percentage can also be queried for UI feedback

- **Enemy AI**
  - AI-controlled enemies use a custom AI controller
  - Behavior Tree driven logic
  - Blackboard-based location tracking
  - line-of-sight awareness
  - shooting task for enemy attacks

- **Win / lose game flow**
  - player loses when destroyed
  - player wins when all enemy AI pawns are dead
  - HUD is replaced with win/lose screens
  - level restarts automatically after a delay

---

## Technical Focus

This project helped me practice the following Unreal Engine systems:

- first-person shooter gameplay structure
- C++ character and weapon programming
- line trace combat systems
- point damage events
- Niagara VFX integration
- Behavior Tree and Blackboard AI
- AI line-of-sight checks
- custom BT tasks and BT services
- HUD and end-game UI flow
- GameMode-based victory and defeat handling

---

## Tech Stack

- **Engine:** Unreal Engine 5.4
- **Language:** C++
- **Framework/Modules:** Unreal Engine Gameplay Framework, AIController, Behavior Tree, Blackboard, Niagara, Enhanced combat systems
- **Project Type:** College assignment
- **Genre:** 3D First-Person Shooter

---

## Main Classes

### `ARaven`
Handles:
- player combat character logic
- health and shield values
- shooting input
- shield activation
- gun spawning and attachment
- damage reception

### `AGun`
Handles:
- weapon mesh setup
- muzzle flash spawning
- muzzle sound playback
- hitscan line trace shooting
- bullet hit effects and sounds
- applying point damage to targets

### `AAINemesisController`
Handles:
- AI controller logic
- running the assigned Behavior Tree
- storing start location in Blackboard
- checking whether the controlled enemy is dead

### `UBTTask_Shoot`
Custom Behavior Tree task that makes the AI character fire its weapon.

### `UBTService_PlayerLocation`
Behavior Tree service that continuously updates the player's location inside the Blackboard.

### `UBTService_PlayerLocationIfSeen`
Behavior Tree service that updates the player location only when the AI has line of sight to the player, otherwise clearing the Blackboard value.

### `AKillEmAllGameModeBase`
Handles:
- enemy elimination progression
- checking if all enemies are dead
- ending the game when the player dies
- triggering win/lose state for all controllers

### `ARavenPlayerController`
Handles:
- HUD creation
- win/lose screen display
- restart level flow after end game

---

## AI System

One of the main technical focuses of this project is the enemy AI setup.

The AI uses:

- **Behavior Trees**
- **Blackboard values**
- **custom BT services**
- **custom BT tasks**
- **line-of-sight checks**

This allowed me to practice how FPS enemy behaviour can be structured through Unreal Engine’s AI framework rather than only hardcoded logic.

---

## What I Learned

Through **Citadel**, I improved my understanding of how to build a small FPS combat loop in Unreal Engine 5.4 using C++.

This project helped me practice:

- building first-person combat systems
- creating reusable weapon logic
- using line traces for shooting
- applying damage with Unreal’s damage system
- connecting AI behaviour to combat logic
- using Behavior Trees and Blackboards
- handling victory and defeat states through GameMode and PlayerController

It was an important project for learning how first-person combat, UI flow, and AI systems work together inside a complete gameplay prototype.

---

## Project Purpose

This project was created as a **second-year college FPS assignment**.

Its purpose was to help me develop a more advanced Unreal Engine gameplay prototype by combining first-person combat, AI-driven enemies, health and shield systems, and structured game flow.

---

## Future Improvements

Possible future improvements for this project include:

- enemy variety and combat styles
- ammo and reload systems
- more advanced shield logic
- player health/shield UI polish
- cover system or smarter enemy navigation
- improved level design and encounter structure
- sound and visual polish
- weapon switching or multiple gun types

---

## Status

**Completed as a second-year college FPS project**

---

## Author

**George Bolias**  
Game Programmer / Unreal Engine Developer

- Portfolio: [https://www.georgebolias.com/](https://www.georgebolias.com/)
- LinkedIn: [https://www.linkedin.com/in/georgebolias/](https://www.linkedin.com/in/georgebolias/)
- GitHub: [https://github.com/GamingMystae](https://github.com/GamingMystae)
