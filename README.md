## Nearest neighbours package
### Table of contents

1. [Introduction](#intro)
2. [Algorithms included](#algo)
3. [Compile and test the configuration](#make)
   1. [Requirements](#req)
   2. [Compile](#comp)
4. [Run](#run)
   1. [Options format](#opt)
   2. [Input file format](#file)
5. [Summary of run-time complexities](#complx)


### 1. Introduction <a name="intro"></a>
In this repository we include some of the most popular algorithms to solve the 'all *m*-th nearest neighbours problem' (all-*m*-nn in short). Given a set of *n* points in a *d* dimensional space, the problem requires to find the m-th nearest neighbours for each point. We include algorithms that work both in euclidean and non-euclidean spaces. This last case is particularly suitable for the entropy estimation using the *k*NN method.
The notation we use is the following:
- *d* number of dimensions
- *n* number of input points
- *m* size of the neighborhood

### 2. Algorithms included <a name="algo"></a>
We include different algorithms to solve the all-*m*-nn problem with different properties and runtime complexities (see [Summary of run-time complexities](#complx)):
- *trivial/*
  contains trivial solutions to the problem
  - `trivial/1-mnn` performs a sorting process and works just for *d=1*
  - `trivial/d-mnn` performs $O(n^2)$ comparison and works for generic values of *d*
  - `trivial/periodic-d-mnn` performs $O(n^2)$ comparison and works in spaces with periodic boundary conditions.
- *kdtree/*
   contains solutions which construct a K-D tree
   - `kdtree/d-mnn` is the basic algorithm which works in euclidean spaces.
   - `kdtree/periodic-d-mnn` works in spaces with periodic boundary conditions.
 - *vptree/*
    contains solutions which construct a VP tree
    - `vptree/d-mnn` works in euclidean spaces.
    - `vptree/periodic-d-mnn` works in spaces with periodic boundary conditions.


### 3. Compile and test the configuration <a name="make"></a>

### 3.1 Requirements <a name="req"></a>
- gcc
- make
### 3.2 Compile <a name="comp"></a>
To build all the executables run:
```
./make
```
If you are using *bash* you can test that everything works by simply running:
```
./runTest
```

### 4. Run<a name="run"></a>
The syntax to run every executables is:
```
<executable> <yourInputFile> [-out <outputMode>] [-in <inputMode>] [-entropy] [-sort] 
```

### 4.1 Options format <a name="opt"></a>
`<outputMode>` is one of the following:
 - `verbose`: the program prints the neighbours in a human-readable format.
 - `flat`: the program prints the neighbours in a non-human-readable format. It's useful just to compare 2 implementations and to save output space.
 - `silent`: the program doesn't print the neighbours.
 - `time`: the program prints just the time taken to compute the m-neighbours for each point.

 `<inputMode>` is one of the following:
 - `verbose`: the program prints the points read from the input file.
 - `silent`: the program doesn't print the points read from the input file.


 With the option `-sort` the neighbours are sorted by increasing distances for each point.
 With the option `-entropy` the program prints the entropy in the specified space with periodic conditions. If `-entropy` is specified in a executable that doesn't support this kind of spaces, an exception will be raised.


Note that by specifying `-out time`, it is just considered the time taken to compute the neighborhood for each point and it is not considered the time to eventually sort the neighbours and calculate the entropy.

By default the both the `<outputMode>` and the `<inputMode>` are set to verbose. The neighbours are sorted and the entropy is not calculated.


**Example 1**: 
```
vptree/d-mnn test/basic-tests/input1.txt -in silent -out verbose -sort
```
Runs the VP tree algorithm with the input file *test/basic-tests/input1.txt*. It doesn't print the read points, but it prints the neighbours sorted by distance. 

**Example 2**: 
```
trivial/periodic-d-mnn test/basic-tests/input2.txt -in silent -out silent -entropy
```
Runs the Naive algorithm (the one which works in spaces with periodic boundaries conditions) with the input file *test/basic-tests/input2.txt*. It doesn't print neither the read points and their neighbours. It just prints the calculated entropy.

### 4.2 Input file format <a name="file"></a>


`<yourInputFile>` should have the following basic syntax
```
n=<nValue> d=<dValue> m=<mValue>
[L <l1> <l2> ... <ld>]
[U <u1> <u2> ... <ud>]
<p1_1> <p1_2> ... <p1_d>
<p2_1> <p2_2> ... <p2_d>
...
<pn_1> <pn_2> ... <pn_d>
```
- The first line is mandatory and defines parameters *n*,*d*, and *m*.
- The second and the third line are optional and should be used to specify the periodic boundary conditions if you use a *periodic-d-mnn* program. If you use a program for basic euclidean spaces, those lines are ignored if present. *li* is the lower bound for the *i*-th coordinate and *ui* is the upper bound for the *i*-th coordinate.
- The following lines are used to specify the points. *pi_j* is the *j*-th coordinate of the *i*-th point.

Some examples could be found in the `test/basic-tests` directory.



### 5. Summary of run-time complexities <a name="complx"></a>
The run-time complexities are summarized in the table below.

| **Algorithm**          | **Expected Time**       | **Worst Case**          | Constraints |
|------------------------|-------------------------|-------------------------|-------------|
| trivial/1-mnn          | $\Theta(n \log n + nm)$ | $\Theta(n \log n + nm)$ | *d=1*       |
| trivial/d-mnn          | $\Theta(dn^2)$          | $\Theta(dn^2)$          |             |
| trivial/periodic-d-mnn | $\Theta(dn^2)$          | $\Theta(dn^2)$          |             |
| vptree/d-mnn           | $O(dn \log n)$          | $O(dn^2 \log m)$        |             |
| vptree/periodic-d-mnn  | $O(dn \log n)$          | $O(dn^2 \log m)$        |             |
| kdtree/d-mnn           | $O(dn \log n)$          | $O(dn^2 \log m)$        |             |
| kdtree/periodic-d-mnn  | $O(n3^d \log(n3^d))$    | Not calculated          |             |

Note that with options `-sort` or `-entropy`, it is taken an additional time of $\Theta(n m (d + \log m))$.
