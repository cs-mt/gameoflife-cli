# gameoflife-cli
C++ implementation of Conway's Game of Life using ncurses library.

## TODO

:ballot_box_with_check: - Create the base game | 2023-03-06

:ballot_box_with_check: - Add Draw Option | 2023-03-06

:ballot_box_with_check: - Save Map to a file | 2023-03-06

:ballot_box_with_check: - Load Map from file | 2023-03-06

:black_square_button: Randomize Map

:black_square_button: - Add common patterns

:black_square_button: - Show statistics

## COMPILING

```
git clone https://github.com/cs-mt/gameoflife-cli.git
cd gameoflife-cli/src
clang++ -lncurses -pthread *.cpp -o gameoflife-cli
./gameoflife-cli
```

## SHORTCUTS

* D enters draw mode
* WASD moves the cursor
* E exits draw mode

## HOW TO SAVE/LOAD MAP 

* Enter draw mode with D
* Press G for saving
* Press L for loading 
* Enter file name.
* Maps are stored under Maps/ folder.

