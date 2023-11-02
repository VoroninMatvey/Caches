# Implementation of LFU cache and ideal cache
## Information about project:
In this project, the LFU cache was implemented - a cache from which the page that is called the least number of times is thrown away. An “ideal” cache was also implemented, it is based on the idea that we know in advance all the pages that have arrived.
## Building the project:
```
git clone git@github.com:VoroninMatvey/Caches.git
cd /Caches
cmake -S ./ -B build
cd build/
make
```
Use the lfu cache executable file:
```
./lfu
```
Use the perfect cache executable file:
```
./perfect
```
The program takes as input: 
1) capacity of cache
2) number of page
3) page1  page2  page3 ...
## Building the test:
```
cd cache_tests/
cmake -S ./ -B build
cd build/
make
```
Use the test generation executable file:
```
./tests
```
The program takes as input:
1) capacity of cache
2) number of page
3) minimum value of incoming page
4) maximum value of incoming page
5) amount of generated tests

In directory cache_data are generated tests and answers
