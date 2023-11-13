🍽️ The Philosophers' Feast: Concurrency Explored!

🌟 Overview

Welcome to the Philosophers' Feast, an intriguing journey into the world of threads, mutexes, and dining philosophers! Inspired by the classic problem in concurrency, this project simulates philosophers thinking, eating, and sleeping, demonstrating critical concepts in multi-threaded programming.

📚 Table of Contents

Introduction
Key Concepts
Philosophers in Action
Conclusion

📖 Introduction

In this project, we simulate a scenario where a group of philosophers must share forks to eat their meals. 
It's a classic problem that illustrates the challenges in concurrent programming, such as avoiding deadlocks and ensuring thread safety.

🧠 Key Concepts

Threads: Think of them as philosophers, each acting independently.
Mutex (Mutual Exclusion): Essential to prevent conflicts over shared resources (like forks!).
Deadlocks and Race Conditions: Key challenges to overcome when multiple threads interact.
Thread Safety and Atomic Operations: Crucial for maintaining the integrity of shared data.

🍝 Philosophers in Action

The simulation involves philosophers (t_philo) who alternate between thinking, eating, and sleeping,
all while managing shared resources (forks) and keeping track of their state.

Eating: Acquiring two forks and updating their eating status.
Thinking and Sleeping: Philosophers ponder and rest, simulating non-critical sections.

🎉 Conclusion

This project is more than just coding; it's about understanding the complexities of concurrent processes and finding creative solutions to real-world problems in computing.
It's a fun and educational journey into the world of multi-threading!

