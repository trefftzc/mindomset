// CIS677 -- Fall 2023 
// Code to find the minimum dominating set in
// an undirected graph
// Brute Force: Check each and every one of the
// possible subsets of the Power Set to find
// the dominating sets and then choose
// the one with minimum cardinality
//
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

set < int > fromIntToSet(unsigned int encodedSet,int n)
{
  int mask = 1;
  set < int > result;
  for(int i = 0;i < n;i++) {
    if ((encodedSet & mask) != 0) {
      result.insert(i);
    }
    mask = mask * 2;
  }
  return result;
}
// Find if a set of vertices, encoded in encodedSet
// is a dominating set in the graph.
// If it is, return the size of the dominating set
// otherwise nVertices + 1

int calcMinDomSet(const unsigned int encodedSet,
		  map < int, set < int > > &graph,
		  const int n)
{
  int covered[n];
  for(int i = 0;i < n;i++) {
    covered[i] = 0;
  }
  set < int > candidateSet = fromIntToSet(encodedSet,n);
  // Check for every vertex if is in the candidate dominating set
  // or if it is directly connected to an element 
  // in the candidate dominating set
  for(int i = 0;i < n;i++) {
    if (candidateSet.find(i) != candidateSet.end()) {
      covered[i] = 1;
    }
    else {
      set < int > neighborsOfNodeI = graph[i];
      set < int > intersection;
      set_intersection(candidateSet.begin(),candidateSet.end(),
		       neighborsOfNodeI.begin(),neighborsOfNodeI.end(),
		       std::inserter(intersection,intersection.begin()));
      if (intersection.size() != 0) {
	covered[i] = 1;
      }
      else {
	covered[i] = 0;
      }
    }
  }
  for(int i = 0;i <n;i++) {
    // If one element in the graph is not covered, return n+1
    if (covered[i] == 0) {
      return n+1;
    }
  }
  return candidateSet.size();
}


int main(int argc,char *argv[])
{
  // Read the input file
  // The exepcted format is:
  // The first line contain two values:
  // n - the number of vertices
  // m - the number of edges
  // The following m lines will contain the m edges
  // Each edge will be specified with the 2 vertices

  int nVertices;
  int nEdges;

  cin >> nVertices;
  cin >> nEdges;

  map < int, set < int > > graph;
  for(int i = 0;i < nEdges;i++) {
    int vertex1,vertex2;
    cin >> vertex1;
    cin >> vertex2;
    if (graph.find(vertex1) == graph.end()) {
      set < int > neighborsOfVertex1;
      neighborsOfVertex1.insert(vertex2);
      graph[vertex1] = neighborsOfVertex1;
    }
    else {
      graph[vertex1].insert(vertex2);
    }
    if (graph.find(vertex2) == graph.end()) {
      set < int > neighborsOfVertex2;
      neighborsOfVertex2.insert(vertex1);
      graph[vertex2] = neighborsOfVertex2;

    }
    else {
      graph[vertex2].insert(vertex1);
    }
  }
  // Print the graph
  for(auto it = graph.cbegin(); it != graph.cend(); it++)
    {
      cout << "Neighbors of node " << it->first << ": ";
      set < int > thisSet = it->second;
      for(auto setElement = thisSet.cbegin();setElement != thisSet.cend();setElement++) {
	cout << *setElement << " ";
      }
      cout << endl;
    }
  // Calculate the number of elements in the Power Set 2^nVertices
  unsigned int nPowerSet = 1;
  for(int i = 0;i < nVertices;i++) {
    nPowerSet = nPowerSet * 2;
  }
  cout << "The number of elements in the Power Set is: " << nPowerSet << endl;
  vector < int > results(nPowerSet);
  int minSize = nVertices+1;
  int codeMinSize = -1;
  for(unsigned int encodedSet=1;encodedSet < nPowerSet;encodedSet++) {
    results[encodedSet] = calcMinDomSet(encodedSet,graph,nVertices);
    if (results[encodedSet] < minSize) {
      minSize = results[encodedSet];
      codeMinSize = encodedSet;
    }
  }
  cout << "The size of the Minimum Dominating Set is: " << minSize << endl;
  cout << "A set of vertices that is a minimum dominating set is: ";
  set < int > minDomSet = fromIntToSet(codeMinSize,nVertices);
  for(auto setElement = minDomSet.cbegin();setElement != minDomSet.cend();setElement++) {
	cout << *setElement << " ";
  }
  cout << endl;
  /*
  cout << "Array with results: " << endl;
  for(int i = 0;i < nPowerSet;i++) {
    cout << i << " " << results[i] << endl;
  }
  */



}
