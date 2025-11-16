
/*The purpose of this program is to demostrate how an AVL tree works.
 *An AVT tree is a self balancing version of a BST (binary search tree)
 *After each insertion the tree automatically checks if its balance.
 *If any node in not balance the program performs a LL,RR,LR,or RL to
 *restore balance.
 */

#include <iostream> // used for printing outputs
#include <algorithm> // used fro max() functions
using namespace std; // so i dont have to use std:: everytime

// the structure
    struct AVLNode // all the nodes in the AVL tree
    {
       int key, height; // stores data the key and the hight of the node
        AVLNode *left, *right; // pointer to the left and right

     //the constructure
     AVLNode(int k): key(k), height(1), left(nullptr), right(nullptr){}

    };
/////////////

// helper fuction return the hight of the node or 0 if its null
    int h(AVLNode* n) {return n ? n->height : 0; }

// returns the balance factor = height left - height right
    int balance(AVLNode* n) {return n ? h(n->left) - h(n->right) : 0;}

// function use to fix ubalanced trees rigt rotation (LL case)
    AVLNode* rotateRight(AVLNode* y)
    {
    cout<<"Rotate right LL\n";
        AVLNode* x=y->left; // x= left child of y
        AVLNode* T2 = x->right; // T2 = temporary subtree x's right child
        x->right = y; // perform rotation, y becomes right child of x
        y-> left=T2; //move t2 to y's left
        y->height= max(h(y->left), h(y->right)) +1; // update y's height '
        x->height=max(h(x->left), h(x->right)) +1; // update x's heigh
        return x; // return the new root after rotation
    }

// function use to fix unbalanced trees left rotation (RR case)
    AVLNode* rotateLeft(AVLNode* x)
    {
        AVLNode* y=x->right; // y=right child of x
        AVLNode* T2 = y->left; //T2 is the temporary subtree of y's left child
        y->left = x; // perform rotation x becomes left child of y
        x->right= T2; //move T2 to x's right
        x->height = max(h(x->left), h(x->right)) +1; // update x height
        y->height =max(h(y->left), h(y->right)) +1; //update y height
        return y; // return the new root after rotatioin

    }
//////////////

// insertion function maintains balance automatically
    AVLNode* insertAVL(AVLNode* node, int key)
    {
        if (!node) return new AVLNode(key); // create a new node if tree/subtree is empty

        //standard BST inser logic
        if (key < node->key) // if smaller, go letf
            node->left = insertAVL(node->left, key);
        else if (key > node->key) // if large, get right
            node->right = insertAVL(node->right, key);
        else return node; // equal keys are ignored, no duplicates

        //update the node of the ancestor node
        node->height = 1+ max(h(node->left), h(node->right));
        int b = balance(node); // calculate the balance factor

       // 4 types of rotation to fix inbalance
        // LL case, the left tree is heavier and new key inserted to the left left
        if (b>1 && key < node->left->key) return rotateRight(node);

        //RR case right subtree heavier and new key inserte to the right right
        if (b<-1 && key > node->right->key) return rotateLeft(node);

        //LR case, left subtree is heavier nut new key inserted in left right position
        if (b >1 && key >node->left->key)
        {
            cout<<"Left Right LR;\n";
            node->left=rotateLeft(node->left); // first rotate left child
            return rotateRight(node); // now rotate current node
        }

        // RL case right subtree is heavier, but new key inserteed in right left position
        if (b<-1 && key < node->right->key)
        {
            cout<<"Right left \n";
            node->right=rotateRight(node->right); // forst rotate right child
            return rotateLeft(node); // then rotate the current node
        }
        return node; // return unchanged node if alance
    }

/////////////

// tree traversal print tree in sorted
    void inorder(AVLNode* r)
    {
        if (!r) return;
        inorder(r->left);
        cout<<r->key<<" ";
        inorder(r->right);
    }

    void preorder(AVLNode* r)
    {
        if (!r) return;
        cout<<r->key<<" ";
        preorder(r->left);
        preorder(r->right);
    }

// the main program
    int main()
    {
        int vals[5] = {50,30,70,20,40};
        AVLNode* root = nullptr;
        for (int v : vals) root= insertAVL(root, v);

        cout<<"AVL inorder, sorted : "; inorder(root); cout<<"\n";
        cout<<"AVL preorder : "; preorder(root); cout<<"\n";
        cout<<"AVL height : " << h(root) << "\n";

    }
