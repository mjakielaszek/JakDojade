# JakDojade?
### The program navigates through the maps available in the mapa.zip folder where hashtags are roads and stars are cities. There can be also given direct connections between cities in the input (flights) along with their time cost. The returned value is the shortest possible path between desired cities.
### In the input:
- the dimensions of the map are given in 'WIDTH HEIGHT' manner,
- '#' is a part of the road,
- '*' is a symbol of a city - at least one letter of its name should be adjacent to it,
- then the number of flights is given. Each flight is given in 'START DESTINATION time-cost' manner.
#### In the program I implemented:
- a doubly linked list for storing direct connections between cities and their lengths,
- BFS algorithm to map the roads,
- Djikstra's algorithm to find connections between cities,
- queue for the BFS algorithm,
- structs to store city and road informations.

#### The program is written in object-oriented manner in C++.
