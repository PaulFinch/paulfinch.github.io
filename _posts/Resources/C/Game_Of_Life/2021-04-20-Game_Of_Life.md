---
layout: post
title:  "Game Of Life"
date:   2021-04-20 10:00:00 +0200
image:  program.jpg
tags:   programming c
---
## Description ##
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.
[Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

Written for Linux Environment.

## Code ##
### The Engine
```C
{% include_relative files/GameOfLife.c %}
```

### The Universe
```
{% include_relative files/Universe.txt %}
```