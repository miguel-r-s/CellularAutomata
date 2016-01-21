# Cellular Automata

## First steps

I decided to build a piece of software that allowed me to study the properties of Cellular Automata in a visual way. The first step was to build something that just prints the evolution of the Automaton to the terminal, according to specific rules.

![](https://github.com/miguelrodriguesdossantos/CellularAutomata/blob/master/example_gifs/visual_demo.gif?raw=true)

This is the output for the Rule Corresponding to the famous [*Game Of Life*](https://en.wikipedia.org/wiki/Conway's_Game_of_Life) (rule 23/3). I can specify a different rule from the terminal, a different size and a different probability of occupation of a given cell in the first generation.

Let's look at the rule called *Stains* (rule 2345/45678), with a probability of occupation of 0.1, and a board with 15x25 cells.

% GIF here (2345/45678)

Notice it stopped at a point in time. The reasone why it stopped is it recognised the current state of the Automaton had already occurred before (let's say the Automaton is *stable* when this happens*). 

The interface allows us to run until stability in a fairly intuitive way:

```C++
	while(!B.isStable()){
		B.setNext();
		std::cout << B;
	}
```

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
