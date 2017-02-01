#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "PriorityQ.hpp"
using namespace std;

/**
 * Unweighted and non directed graph
 */
class Graph {
    int _nV, _nE;
    vector < vector <bool> > _matrix;
    
public:
    /**
     * edges is the matrix storing edge configurations each row contains the indices of the vertices that are adjascent to that index
     * nV number of vertices (also number of rows in edges)
     * it is assumed that each row ends with -1
     *
     * technicaly edges is a nV x something matrix
     */
    Graph(int **edges, int nV) {
        _nV = nV;
        _nE = 0;
        
        // initializes the vector matrix
        _matrix.resize(nV);
        for (
            vector< vector<bool>>::iterator it = _matrix.begin();
            it != _matrix.end();
            it++
        ) {
            it->resize(nV,false);
        }
        
        for(int i=0;i<nV;i++) {
            int j=0;
            while(edges[i][j] != -1) {
                _matrix[i][edges[i][j]] = true;
                _matrix[edges[i][j]][i] = true;
                _nE++;
            }
        }
        
    };
    
    /**
     * calculates the distance from the origin of all vertices
     * @param  origin origin index of the crystal
     * @return        an vector of size nV (use like a normal array)
     */
    vector<int> calcDist (int origin) {
        vector <int> ret;
        vector <int> st;
        
        _dijsktra(origin, st, ret);
        
        return ret;
    };
    
    bool hasEdge(int i, int j) {
        return this->_matrix[i][j];
    }
    
    
private:
    /**
     * an implementation of dijsktra's algo
     * @param origin  the origin index
     * @param befores returned array of indices
     * @param dist    returned array of distances from the before index
     *
     * assumed that befores and dist is resized to nV already
     */
    void _dijsktra(int origin, vector<int> &befores, vector<int> &dist) {
        PriorityQ pq;
        dist.resize(_nV, PriorityQ::INFINITE);
        befores.resize(_nV, -1);
        for(int i=0; i<_nV; i++) {
            pq.insert(i,dist[i]);
        }
        dist[origin] = 0;
        pq.change(origin, 0);
        while(!pq.isEmpty()) {
            int vertex = pq.delMin();
            for(int i=0;i<_nV;i++) {
                if(hasEdge(i,vertex)) {
                    if(dist[vertex] + 1 < dist[i]) {
                        dist[i] = dist[vertex] + 1;
                        befores[i] = vertex;
                        pq.change(i,dist[i]);
                    }
                }
            }
        }
    };
    
};

#endif