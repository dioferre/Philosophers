# Philosophers

![Philosophers](https://images.theconversation.com/files/257265/original/file-20190205-86202-19tymqj.jpg?ixlib=rb-4.1.0&q=45&auto=format&w=926&fit=clip)

## 📝 Overview

The *Philosophers* project is part of the 42 curriculum and is based on the **Dining Philosophers Problem**, a classic synchronization problem in computer science. The goal is to manage multiple philosophers who alternate between **thinking**, **eating**, and **sleeping**, while ensuring that they do not encounter deadlocks or resource starvation.

## 🚀 Features

- Implemented using **threads and mutexes**.
- Ensures proper **synchronization** to avoid deadlocks.
- Supports **multiple philosophers** with customizable simulation parameters.
- Efficient resource sharing with **mutex locks**.
- Precise **time management** using `gettimeofday()`.

## 🛠️ Installation

To compile the project, simply run:

```bash
make
```

This will generate the `philo` executable.

## 📌 Usage

Run the program with the following parameters:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example:

```bash
./philo 5 800 200 200
```

This runs the simulation with:

- **5 philosophers**
- **800ms** before dying if they don’t eat
- **200ms** to eat
- **200ms** to sleep

## 🖥️ Output Example

```
0 1 is thinking
100 2 is eating
300 3 is sleeping
500 4 is eating
800 1 has died
```

## ⚠️ Handling Edge Cases

- Prevents deadlocks by **avoiding simultaneous fork grabbing**.
- Handles **single philosopher case** correctly.
- Properly cleans up **threads and mutexes** to prevent memory leaks.

## 🏛️ Project Structure

```
📂 philosophers
 ├── include
 │   ├── philosophers.h
 ├── src
 │   ├── init.c
 │   ├── monitor.c
 │   ├── parsing.c
 │   ├── routine.c
 │   ├── utils.c
 │   ├── utils2.c
 ├── Makefile
 ├── main.c
 ├── README.md
```

## 📚 Learning Outcomes

- **Multithreading** with `pthread`
- **Mutex synchronization**
- **Concurrency control**
- **Timing and precision in C**

## 📖 References

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [pthread Library Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Image used at the top](https://theconversation.com/3-philosophers-set-up-a-booth-on-a-street-corner-heres-what-people-asked-110866)

## 🎉 Acknowledgements

Special thanks to [Markos](https://github.com/MarkosComK) and [Edu](https://github.com/eduVVSC) for their help during this project.

---
⭐ If you found this project interesting, give it a **star** on GitHub! ⭐

