/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: RamiroV
 *
 * Created on September 17, 2018, 3:07 PM
 */

#ifndef NODE_H
#define NODE_H

class Node_t {
    
public:
    
    /** The global xy coordinates of the node */
    double _x, _y;
    
    /** The total energy of the node (i.e. the sum of the energy of each
     *  associated box) */
    double energy;
    
    Node_t();
    Node_t(const Node_t& orig);
    virtual ~Node_t();
};

#endif /* NODE_H */

