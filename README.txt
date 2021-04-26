# Ford-Fulkerson

This program solves the Maximun flow problem, using Ford - Fulkerson methods, using both BFS (Edmonds - Karp Algorithm) 
and a greedy approach to find the improving route.
In order to create your own flow function and solve the Maximum flow program you need to follow these instructions:
	1. Create a simple text file called 'input.txt' and place it in the Solution's directory.
	2. First line of the text file should be the number of Vertexes in the graph (n).
	3. Second line of the text file should be the number of Edges in the graph (m).
	4. Third line of the text file should be the source vertex number (S).
	5. Forth line of the text file should be the destenation vertex number (T).
	6. m (number of Edges) lines - each line represents an edge in the graph.
	   The data in each line should be the source vertex, destenation vertex, and the edge's capacity,
	   in this format - source destenation capacity (emphasis on spaces).
All the edge's capacity values must be positive.
If any input will be invalid the program will notify the user before exiting
The program will retrieves all the data from the given file and build the graph using a matrix.
Then it will run both algorithm to solve the Maximum Flow problem.
For each run the program will print the Maximum Flow that was found, the Minimun cut and the number of iterations.

Example input:
6
10
1
6
1 2 16
1 3 13
2 3 10
3 2 4
2 4 12
4 3 9
3 5 14
5 4 7
5 6 4
4 6 20

For this input the output will be:
BFS Method:
Max flow = 23
Min cut: S = 1, 2, 3, 5. T = 4, 6
Number of iterations = 3
Greedy Method:
Max flow = 23
Min Cut: S = 1, 2, 3, 5. T = 4, 6
Number of iterations = 4
