Lir Mimrod 315029124
Idan Rosenberg 315006882

bonus additions:
- color mode selection via menu 

- our own interpretation for novice ghost movement:
  when a ghost reaches an intersection, it decides randomally which direction to go
  based on available paths, but will not go backwards (in opposite direction), unless reaches dead end

- for smarter ghosts we used our own implementation of the A* algorithm, which finds approximately the shortest
  path to reach pacman
  - GOOD: 1/10 chance to sample a new path to pacman every turn 
  - BEST: 1/5 chance to sample a new path to pacman every turn 

- Ascii art
