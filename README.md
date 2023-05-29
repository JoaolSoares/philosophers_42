# philosophers_42
<p align="center">
    <img src="https://game.42sp.org.br/static/assets/achievements/philosopherse.png">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/tokei/lines/github/JoaolSoares/philosophers_42?color=critical">
    <img src="https://img.shields.io/badge/Language-C%20-orange.svg" alt="Language">
    <img src="https://img.shields.io/badge/Grade-100%2F100-brightgreen.svg" alt="Grade">
    <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

# Philosophers
This project is about using threads and mutexes to solve the [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

<p align="center">
  <img src="https://2.bp.blogspot.com/-CdsTdRiQpKk/WdcnTQpYQqI/AAAAAAAABkw/hBu33DBKg10fxei211VL-C4mIK-e8x5tgCLcBGAs/s1600/Dining-Philosophers-Problem.png">
</p>

## Introduction
The project consists of simulating the behavior of philosophers at a dinner table. Each philosopher has a fork on his left and right. To eat, a philosopher needs both forks. To avoid deadlock, a philosopher must always pick up the fork on his right first, then the fork on his left. When he finishes eating, he puts down both forks so that the other philosophers can eat. The simulation stops when a philosopher dies.

## How to use
- Clone the repository
- Run `make` to compile the project
- Run `./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]` to execute the program
