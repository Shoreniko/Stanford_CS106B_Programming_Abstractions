/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include "hashmap.h"
#include "hashset.h"
using namespace std;

const double INTERVAL_MIN = 0;
const double INTERVAL_MAX = 1;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, 
						 double costFunction(Loc one, Loc two, Grid<double>& world), 
						 double heuristic(Loc start, Loc end, Grid<double>& world)){
	/* Initialization */ 
    HashMap<Loc, double> candidateDistances; 
	HashMap<Loc, Loc> parents;
	HashSet<Loc> yellow;
	TrailblazerPQueue<Loc> pQueue;
	Vector<Loc> shortestPath;
	/* Color startNode yellow */ 
	colorCell(world, start, YELLOW);
	yellow.add(start);
	/* Set startNode's candidate distance to 0 */ 
	candidateDistances[start] = 0;
	/* Enqueue startNode into the priority queue with priority h(startNode, endNode) */ 
	pQueue.enqueue(start, heuristic(start, end, world));
	/* While the queue is not empty */
	while(!pQueue.isEmpty()){
		/* Dequeue the lowest-cost node curr from the priority queue */ 
		Loc curr = pQueue.dequeueMin();
		/* Color curr green */
		colorCell(world, curr, GREEN);
		if(yellow.contains(curr)) yellow.remove(curr);
		/* If curr is the destination node endNode, you have found the shortest path from startNode
           to endNode and are done */
		if(curr == end) break;
		/* For each node v connected to curr by an edge of length L */ 
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				if(!(i == 0 && j == 0) && world.inBounds(curr.row + i, curr.col + j)){
					Loc v = makeLoc(curr.row + i, curr.col + j);
					/* If v is gray */
					if(!candidateDistances.containsKey(v)){
						/* Color v yellow */ 
						colorCell(world, v, YELLOW);
						yellow.add(v);
						/* Set v's candidate distance to be dist + L */
						double L = costFunction(curr, v, world);
						candidateDistances[v] = candidateDistances[curr] + L;
						/* Set v's parent to be curr */ 
						parents[v] = curr;
						/* Enqueue v into the priority queue with priority dist + L + h(v, endNode) */ 
						pQueue.enqueue(v, candidateDistances[v] + heuristic(v, end, world));
					} 
					/* Otherwise, if v is yellow and the candidate distance to v is greater than dist + L */ 
					else {
						double distL = candidateDistances[curr] + costFunction(curr, v, world);
						if(candidateDistances[v] > distL && yellow.contains(v)){
							/* Set v's candidate distance to be dist + L */
							candidateDistances[v] = distL;
							/* Set v's parent to be curr */
							parents[v] = curr;
							/* Update v's priority in the priority queue to dist + L + h(v, endNode) */ 
							pQueue.decreaseKey(v, distL + heuristic(v, end, world));
						}
					}
				}
			}
		}	
	}
	/* Convert the hash-map of parent locations to the vector of the shortest path */ 
	hashMapToVector(parents, shortestPath, end, start);
	shortestPath.add(end);
	/* Return the shortest path vector */
	return shortestPath;
}

/* This recursive function converts a hash-map into a vector */ 
void hashMapToVector(HashMap<Loc, Loc>& parents, Vector<Loc>& shortestPath, Loc loc, Loc start){
	if(loc == start){
		shortestPath.add(start);
	} else {
		hashMapToVector(parents, shortestPath, parents[loc], start);
		shortestPath.add(parents[loc]);
	}
}	

/* This function returns a set of edges that represent a maze (spanning tree)
   built based on the Kruskal's algorithm */ 
Set<Edge> createMaze(int numRows, int numCols) {
	/* Initialisation */ 
	TrailblazerPQueue<Edge> pQueue;
	Map<Loc, HashSet<Loc> > clusters;
	Map<Loc, Loc> origins;
	Set<Edge> spanningTree;
	/* Place each node into its own cluster */ 
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			Set<Loc> cluster;
			Loc loc = makeLoc(i, j);
			cluster.add(loc);
			origins[loc] = loc;
			clusters[loc].add(loc);
		}
	}
	/* Insert all edges in the graph into a priority queue */
	/* Add vertical edges to the priority queue */ 
	for(int i = 0; i < numRows - 1; i++){
		for(int j = 0; j < numCols; j++){
			Loc start = makeLoc(i, j);
			Loc end = makeLoc(i + 1, j);
			Edge e = makeEdge(start, end);
			double priority = randomReal(INTERVAL_MIN, INTERVAL_MAX);
			pQueue.enqueue(e, priority);
		}
	}
	/* Add horizontal edges to the priority queue */ 
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols - 1; j++){
			Loc start = makeLoc(i, j);
			Loc end = makeLoc(i, j + 1);
			Edge e = makeEdge(start, end);
			double priority = randomReal(INTERVAL_MIN, INTERVAL_MAX);
			pQueue.enqueue(e, priority);
		}
	}
	/* While there are two or more clusters remaining */ 
	int numOfClusters = numRows * numCols;
	while(numOfClusters >= 2){
		/* Dequeue an edge e from the priority queue */ 
		Edge e = pQueue.dequeueMin();
		/* If the endpoints of e are not in the same cluster */
		Loc startOrigin = findOrigin(origins, e.start);
		Loc endOrigin = findOrigin(origins, e.end);
		if(startOrigin != endOrigin){
			/* Merge the clusters containing the endpoints of e */
			origins[endOrigin] = startOrigin;
			numOfClusters--;
			/* Add e to the resulting spanning tree */
			spanningTree.add(e);
		}
	}
	/* Return the spanning tree formed this way */ 
	return spanningTree;
}

/* This recursive function finds the origin location that the current
   location is tied to with the help of the origins' map */ 
Loc findOrigin(Map<Loc, Loc>& origins, Loc loc){
	if(loc == origins[loc]) return loc;
	return findOrigin(origins, origins[loc]);
	return Loc();
}