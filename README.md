# Philosophers

**Philosophers** is a C program that simulates the classic dining philosophers problem using threads and mutexes to manage concurrent eating, thinking, and sleeping.

## File Structure

```
Philosophers-main/
├── Makefile               # Build rules for the philo executable
├── main.c                 # Entry point: argument parsing and initialization
├── philo.h                # Declarations: structs, constants, and function prototypes
├── created_table.c        # Setup of philosopher data structures and mutexes
├── threads_start.c        # Thread creation and routine starter
├── simulation.c           # Philosopher routines (eat, sleep, think) and timing
├── cleanup.c              # Resource cleanup and mutex destruction
└── utils.c                # Utility functions (time management, printing, error handling)
```

## Compilation

From the project root directory (`Philosophers-main`), run:

```bash
make
```

This will compile all source files and produce the executable **`philo`**.

Common Make targets:

```bash
make clean   # remove object files
make fclean  # remove object files and the philo executable
make re      # recompile from scratch (fclean + make)
```

## Usage

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
```

* **`number_of_philosophers`**: total philosophers (and forks)
* **`time_to_die`** (in ms): max time a philosopher can go without eating
* **`time_to_eat`** (in ms): time it takes to eat
* **`time_to_sleep`** (in ms): time to sleep
* **`number_of_times_each_must_eat`** (optional): how many times each philosopher must eat before the simulation ends

**Example:**

```bash
./philo 5 800 200 200 7
```

This starts 5 philosophers who will die if they don’t eat within 800 ms, each eating for 200 ms and sleeping for 200 ms; the simulation ends after each has eaten 7 times.

## Author

* **Alparslan Aslan** ([alparslanaslan504@gmail.com](mailto:alparslanaslan504@gmail.com))

## License

No explicit license provided. Use, modify, and distribute at your own risk.
