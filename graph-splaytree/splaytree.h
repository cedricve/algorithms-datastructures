#ifndef __SPLAYTREE
#define __SPLAYTREE
#include <cstdlib>
#include <iostream>
#include <queue>
#include "binsearchtree.h"
using namespace std;
using std::ostream;


template <class Sleutel,class Data>
class SplayTree : public BinSearchTree<Sleutel,Data> {
public:
	
	// check if position is left child from parent or not
	bool isLeftChild(BinNode<Sleutel,Data>*& position, BinNode<Sleutel,Data>*& parent){
		return (position == parent->left.k);
	};
	
	// splay operation
	void splay(BinTree<Sleutel,Data>*& position, BinNode<Sleutel,Data>*& parent, BinTree<Sleutel,Data>*& deBinTree){
		// Not @ root 
		while(parent!=0)
		{
			//Main 1: rotate root
			// 
			if(parent->parent==0)
			{
				// Symmetrie left child from root
				// Zig
				deBinTree->roteer(!isLeftChild(position->k,parent));
				parent = 0;
			}

			//Main 2: rotate intern
			else {
				
				BinNode<Sleutel,Data> * grandparentcpy = parent->parent->parent;
				BinTree<Sleutel,Data> * grootparent = 0;
				
				if(grandparentcpy==0)
					grootparent = deBinTree;
				else{	
					if(isLeftChild(parent->parent,grandparentcpy))
						grootparent = &(grandparentcpy->left);
					else
						grootparent = &(grandparentcpy->right);
				}
				
				// Symmetrie Parent left child from grandparent
				if(isLeftChild(parent,parent->parent))
				{
					//
					// Main 2A: if left child from parent
					// ZigZig
					//
					if(isLeftChild(position->k,parent)){	
						// if mag weg als deBinTree probleem opgelost
						grootparent->roteer(false);
						grootparent->roteer(false);
					}
					//
					// Main 2B: if right child from parent
					// ZigZag
					//
					else {
						parent->parent->left.roteer(true);	
						grootparent->roteer(false);
					}
				}
				
				
				// Symmetrie Parent right child from grandparent
				else {
					//
					// Main 2A: if left child from parent
					// ZigZag
					//
					if(isLeftChild(position->k,parent)){
						parent->parent->right.roteer(false);
						grootparent->roteer(true);
					}
					//
					// Main 2B: if right child from parent
					// ZigZig
					//
					else {
						grootparent->roteer(true);
						grootparent->roteer(true);
					}
				}
				
				// replace for while
				position = grootparent;	
				parent = grootparent->k->parent;

			}
		}
	};
	
	virtual void voegtoe(const Sleutel& sl,const Data& data){
	    BinTree<Sleutel,Data>* position;
	    BinNode<Sleutel,Data>* parent;
	    searchPosition(sl,position,parent);
	    if (position->k == 0){
	        position->k=new BinNode<Sleutel,Data>(sl,data);
	        position->k->parent=parent;
	    }
		BinTree<Sleutel,Data>* deBinTree = &(this->deBinTree);
		splay(position,parent,deBinTree);
	}
	
};

#endif


