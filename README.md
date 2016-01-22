# Cellular Automata

## First steps

I decided to build a piece of software that allowed me to study the properties of Cellular Automata in a visual way. The first step was to build something that just prints the evolution of the Automaton to the terminal, according to specific rules.

![](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/example_gifs/visual_demo.gif?raw=true)

This is the output for the Rule Corresponding to the famous [*Game Of Life*](https://en.wikipedia.org/wiki/Conway's_Game_of_Life) (rule 23/3). I can specify a different rule from the terminal, a different size and a different probability of occupation of a given cell in the first generation.

Let's look at the rule called *Stains* (rule 2345/45678), with a probability of occupation of 0.1, and a board with 15x25 cells.

![](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/example_gifs/visual_demo_stains.gif?raw=true)

Notice it stopped at a point in time. The reasone why it stopped is it recognised the current state of the Automaton had already occurred before (let's say the Automaton is *stable* when this happens). 

The interface allows us to run until stability in a fairly intuitive way:

```C++
	while(!B.isStable()){
		B.setNext();
		std::cout << B;
	}
```

## Simulations

It is interesting to see how many steps until stability we need. The question here is: for a given probability of occupation and a given rule, how many steps does the automaton need until it reaches a state that it had already been in before? My initial guess would be a Gaussian distribution around a peak that was centered around some value that increased with the size of the board. I was.. uh... wrong. 

Let's see the results for several rules.

### Distribution of \#steps until stability:

Parameters:
* p = 0.6
* size = 10x10
* number of experiments = 1E4

#### Coral (45678/3)
![Coral (45678/3)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/Coral.png?raw=true)

#### Diamoeba (5678/35678)
![Diamoeba (5678/35678)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/Diamoeba.png?raw=true)

#### LongLife (5/345)
![LongLife (5/345)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/LongLife.png?raw=true)

#### Mazectric (1234/3)
![Mazectric (1234/3)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/Mazectric.png?raw=true)

#### VoteFourSlashFive (35678/4678)
![VoteFourSlashFive (35678/4678)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/VoteFourSlashFive.png?raw=true)

The data was acquired using `2D_stability.cpp`, and the histograms were made using the script `GNU_steps_to_stability` in the directory `gnuplot_scripts/`. All of the histograms have the same bin width, which is not ideal, but is good enough to give us an idea of how each rule behaves in terms of number of steps til stability. 

We can now choose to focus on one of the rules and run the experiment with a higher number of tests. I chose rule LongLife (5/345) because it's not clear what the distribution looks like in the previous case.

Here is the result for 100x as many experiments. This took about 15 minutes to compute in my machine (with an Intel Core i7 2.4GHz).

#### LongLife (5/345)
![LongLife (5/345)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/2D_stability/graphs/LongLife_1E6.png?raw=true)

### Variation of \#steps until stability with the initial probability of occupation

The only intuition I had for the results was that the number of steps til stability should drop to zero when the probability was too close to 0 or 1. I decided to run a simulation to see how the average \#steps to stability changes with the initial probability of occupation.

The results were obtained using the source file `sts_occupation.cpp` with the following parameters:

* 0 <= p <= 1
* size = 8x8
* number of experiments = 1E6

The idea is to run a number of simulations for each probability of occupation (0 <= p <= 1) and calculate the average number of steps to stability.

These are some of the most interesting results: 

#### Assimilation (45678/345)
![Assimilation (4567/345)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/sts_vs_occupation/graphs/Assimilation.png?raw=true)

#### ConwaysLife (23/3)
![ConwaysLife (23/3)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/sts_vs_occupation/graphs/ConwaysLife.png?raw=true)

#### Maze (12345/3)
![Maze (12345/3)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/sts_vs_occupation/graphs/Maze.png?raw=true)

#### Stains (235678/3678)
![Śtains (235678/3678)](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/sts_vs_occupation/graphs/Stains.png?raw=true)

<!---
We will also look at the *stability period*, which is defined as the number of iterations the Automaton takes to return to the first repeated state. We'll look into it in more detail later.

## Studying *stability*.

### How does the number of steps until stability vary with initial occupation status?

Let's say we start with an automaton in which each cell may be either alive (with a probablility `p`) or dead (with a probability `1-p`). For any automaton of decent size, there is a huge number of different configurations for these conditions. Will all of them take approximately the same time to reach a stable state? 

#### Experiement 1 (p = 0.6, verticalSize = 10, horizontalSize = 10)

Using `gnuplot`, I plotted the absolute frequency with which each result occurred. Almost all rules result in poisson distributions. Let's take a look at some of the prettiest results:

* Conways Life (23/3)

[![](./2D/ConwaysLife.png)](./2D/ConwaysLife.png)

* Coral (45678/3)

[![](./2D/Coral.png)](./2D/Coral.png)

* Maze (12345/3)

[![](./2D/Maze.png)](./2D/Maze.png)

### How does the number of steps until stability vary with the size of the board? 

#### Conways Game Of Life

#### Amoeba

###  

-->
