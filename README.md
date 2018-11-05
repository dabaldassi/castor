# Castor

This is a game engine using the actor pattern.

It uses the library SANDAL2 to handle graphics.

## Compiling

You need SANDAL2 ( and SDL2 ) to compile it.

```
>cd castor

>git submodule init src/SANDAL2

>git submodule update src/SANDAL2

>mkdir build

>cd build

>cmake ..

>make
```