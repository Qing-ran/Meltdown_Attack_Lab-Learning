# Meltdown_Attack_Lab-Learning

Continue To Update…

Share the process of the Meltdown_Attack_Lab 

Welcome to exchange and discuss！！

## Experimental environment

- CPU : Intel 6700
- OS : Ubuntu 16.04



## Task 1: Reading from Cache versus from Memory

### About CacheTime.c

- purpose ： To show the difference between reading data from the cache and reading data from memory.

- Steps：

  - Type the following in the terminal to compile

  ```c
  $ gcc -march=native -o CacheTime CacheTime.c
  ```

  - Run the compiled file

  ```c
  $ ./CacheTime
  ```

We can see the consequence

```c
Access time for array[0*4096]: 466 CPU cycles
Access time for array[1*4096]: 502 CPU cycles
Access time for array[2*4096]: 524 CPU cycles
Access time for array[3*4096]: 276 CPU cycles
Access time for array[4*4096]: 522 CPU cycles
Access time for array[5*4096]: 502 CPU cycles
Access time for array[6*4096]: 640 CPU cycles
Access time for array[7*4096]: 252 CPU cycles
Access time for array[8*4096]: 502 CPU cycles
Access time for array[9*4096]: 516 CPU cycles
```

## Task 2: Using Cache as a Side Channel

Use the side channel to extract a secret value used by the victim function.

**Method ： FLUSH + RELOAD** 

Steps：

- FLUSH the entire array from the cache memory to make sure the array is not cached.
- Invoke the victim function, which accesses one of the array elements based on the value of the secret. This action causes the corresponding array element to be cached.
- Invoke the victim function, which accesses one of the array elements based on the value of the secret. This action causes the corresponding array element to be cached.

![image-20230401102338499](C:\Users\Lan\AppData\Roaming\Typora\typora-user-images\image-20230401102338499.png "Diagram depicting the Side Channel Attack")

<p align="center">Diagram depicting the Side Channel Attack</p>

### About FLUSH + RELOADc
- Compile & Run

```c
$ gcc -march=native -o FlushReload FlushReload.c
$ sudo ./FlushReload
```

- Consequence

```c
array[94*4096 + 1024] is cache.
The Secret = 94
```

- **Notice** :  It should be noted that the technique is not 100 percent accurate, and you may not be able to observe the expected output all the time.

I have tried 20 times and just 10 times show me the secret correctly.



