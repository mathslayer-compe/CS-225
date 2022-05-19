/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
int AVLTree<K, V>::getTreeHeight(Node* root) const {
  if(root == NULL){
    return -1;
  } else {
    return (1 + std::max(heightOrNeg1(root->right), heightOrNeg1(root->left)));
  }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)

    // your code here

    Node* stick_middle = t->right; // new root of the tree
    t->right = stick_middle->left; // move stick middle left child
    t->height = getTreeHeight(t);
    stick_middle->left = t;
    t = stick_middle;              // change old root with the new root
    t->height = getTreeHeight(t);
    

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    
    // your code here

    Node* stick_middle = t->left;  // new root of the tree
    t->left = stick_middle->right; // move stick middle left child
    t->height = getTreeHeight(t);
    stick_middle->right = t;  
    t = stick_middle;              // change old root with the new root
    t->height = getTreeHeight(t);
    
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (balance == -2) {
    
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);

        if (l_balance == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }

    } 
    
    if (balance == 2) {

        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);

        if (r_balance == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }

    subtree->height = getTreeHeight(subtree);

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
      subtree = new Node(key, value);
    } else if (key < subtree->key) {
      insert(subtree->left, key, value);
    } else {
      insert(subtree->right, key, value);
    }

    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {

        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here

            Node* curr_iop = subtree->left;
            while (curr_iop->right != NULL){
              curr_iop = curr_iop->right;
            }

            swap(curr_iop, subtree);
            remove(subtree->left, key);

        } else {

            /* one-child remove */
            // your code here

            if (subtree->left == NULL && subtree->right != NULL) {
                Node* curr_right = subtree->right;
                delete subtree;
                subtree = curr_right;
            } else {
                Node* curr_left = subtree->left;
                delete subtree;
                subtree = curr_left;
            }

        }
        // your code here
        rebalance(subtree);
    }

}