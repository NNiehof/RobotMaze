# RobotMaze
Line maze resolution for an Arduino-based robot.

![Robot](https://github.com/NNiehof/RobotMaze/blob/master/robot.jpg)

### Project structure
The Arduino compiler includes all source code in the `libraries` directory, regardless of what is indicated in header files.

For this reason, source and header files for use on Arduino are in `./src/libraries/<subfolder>`.  
Build files and source code for testing and debugging in pure C++ are in `./src/<subfolder>`.

### Working notes
A capacity test with three 16 x 16 matrices runs, but this is approaching
the maximum capacity of SRAM. Experiments with larger arrays made the Arduino unresponsive. Next things to look into:
* Check how much data is necessary for implementing an A* based maze solving algorithm.
* Change data type from `int` to `byte`.
* Put data in Flash or EEPROM instead of SRAM where possible (abandon dynamic arrays).