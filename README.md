# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Algorithm and tuning

The goal of this project is to control the steering angle of a simulated car so it will follow the road. It is also possible to control the throttle, which  found very useful.

### Controlling the steering angle

For controlling the car basic PID controller is used. The input the the PID was the distance of the car from the center of the line.

This type of controller has three basic terms:
* Proportional (P) - proportional to the current value - directly reacts to changes in control value (if used alone overshoots and leads to oscillations)
* Derivative (D) - proportional to error between current and previous value - tries to estimate future trend (used to dampen or remove the oscillation)
* Integral (I) - proportional to sum of errors - prevents residual error

 The biggest challenge of the project was to tune the PID parameters to get the smooth and safe trajectory. I've started to estimate the biggest P parameter when the car is still behaving in a stable way (with I and D set to 0). I found out that this value is around 0.5. Next step was to find a D parameter that will compensate for the oscillations in the system. During tests with different values I realized that the car was not turning enough when approaching the corners, which leads to overshooting. To tackle this problem I did two things: increase the P value and introduce the heuristic to control the throttle (described later).

 After multiple tests I found out that parameters P = 0.13 I = 0.0003 and D = 1.4, yield a good results. The car is still oscillating a bit, but it is not driving off the road.

 ### Controlling the throttle

 During the PID tuning I realized that it's hard to follow the road when driving with the full speed. That's why I introduced the heuristic that limits the throttle depending on the current control value. The ranges that I used are based on experiments, and could potentially be improved. Another improvement might be to use the PID controller instead of the heuristics.

 Used throttle values:
 | CTE        | throttle           |
| ------------- |:-------------:|
 | < 0.5 | 0.25|
 |0.5< CTE <0.8 | 0.15|
 |0.8<CTE<2 | 0.1|
 |>2 (if speed <20)|0.05|
 |>2 (if speed >20)|-0.05|
