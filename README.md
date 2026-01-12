# Game a la Kono – Console Board Game

## Overview
This project is a **console-based board game** in C++, inspired by a simplified strategy game similar to “Kono.”  
The game is designed for **two players**, with one controlled by a human and the other by the computer. Players move their pieces (pawns) on a **4x4 grid** and aim to capture the opponent's pieces or block their moves.  
Each player has **4 pawns**, represented on the board as `B` (computer) and `C` (human).  

---

![KONO](kono.gif)


## Key Features
- **Two-player gameplay:** Human vs. computer.
- **Board display:** A clear 4x4 grid shown in the console with Unicode borders.
- **Pawn movement:**  
  - Move to adjacent empty spaces.  
  - Capture opponent’s pawns by jumping over them.  
- **Time-based moves:** Each player has a limited amount of time per turn.  
- **Computer AI:**  
  - Checks for possible captures first.  
  - Otherwise, selects a random valid move.  
- **Win conditions:** Game ends when a player has 1 or fewer pawns, cannot make a move, or runs out of time.

---

## Implementation Summary
- **Data Structures:**  
  - `struct Gracz` stores player names, pawn counts, time remaining, and the board as a 2D array.  
- **Board Setup:**  
  - Player 1 pawns on the first row, player 2 pawns on the last row.  
  - Empty spaces represented by `0`.  
- **Board Display Function:**  
  - Prints the board with column letters (`A–D`) and row numbers (`1–4`).  
  - Uses Unicode box characters for a clear grid.  
- **Movement and Capture Logic:**  
  - `ruch_gracza()` handles human input with validation.  
  - `ruch_komp()` handles computer moves, prioritizing captures.  
  - `sprawdz_bicie()` implements the jump-over capture rules.  
- **Utility Functions:**  
  - `licz_pionki()` counts pawns for win condition checks.  
  - `czy_mozliwy_ruch()` checks if a player can move.  
  - `podanie_czasu()` sets the move time limit.  
- **Game Loop:**  
  - Alternates between human and computer moves.  
  - Updates the board, checks captures, validates moves, and decrements time.  
  - Ends when a player cannot move, runs out of time, or loses most pawns.

---

