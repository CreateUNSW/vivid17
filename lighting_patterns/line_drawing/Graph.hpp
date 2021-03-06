#ifndef GRAPH_H
#define GRAPH_H

#include "my_vector.hpp"
#include "PriorityQ.hpp"
#include "config.h"

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
     * TODO change edges to an array of pointers
     */
    Graph(int edges[][MAX_EDGE_PER_CRYSTAL + 1], int nV) : _matrix() {
        vector<bool> *tmp = new vector<bool> (nV, false);
        _matrix.resize(nV, *tmp);
        delete tmp;
        _nV = nV;
        _nE = 0;
        
        for(int i=0;i<nV;i++) {
            int j=0;
            while(edges[i][j] != -1) {
                _matrix[i][edges[i][j]] = true;
                _matrix[edges[i][j]][i] = true;
                _nE++;
                j++;
            }
        }

    };

    /**
     * calculates the distance from the origin of all vertices
     * @param  origin origin index of the crystal
     * @return        an vector of size nV (use like a normal array)
     */
    int* calcDist (int origin) {
        vector <int> dist;
        vector <int> st;
        int* ret = new int[_nV];
        _dijsktra(origin, st, dist);
        for(int i=0;i<dist.size();i++) {
            ret[i] = dist[i];
        }
        return ret;
    };

    int* calcLine (int origin, int destin) {
        vector <int> dist;
        vector <int> st;
        int* ret = new int[_nV];
        _dijsktra(origin, st, dist);
        int j=1;
        ret[0] = origin;
        for(int i=st[destin];i!=-1&&j<st.size()&&i!=origin;i=st[i]) {
            ret[j] = i;
            j++;
        }
        ret[j] = destin;
        return ret;
    };


    bool hasEdge(int i, int j) {
        return _matrix[i][j];
    }

    int nV() {
        return _nV;
    }
    
    // void print() {
    //     for(int i=0;i<_nV;i++) {
    //         for(int j=0;i<_nV;j++)
    //             if(_matrix[i][j])
    //                 cout << 1;
    //             else    
    //                 cout << 0;
    //         cout << endl;
    //     }
    // }


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
        dist.resize(_nV, PriorityQ::MAX_VALUE);
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
