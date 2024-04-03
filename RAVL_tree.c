/* 
 *  RAVL (augmented with Rank AVL) tree implementation. 
 *  Author (starter code): Anya Tafliovich. 
 *  Based on materials developed by F. Estrada. 
*/  
  
#include "RAVL_tree.h"  
#include "math.h"  
  
/************************************************************************* 
 ** Suggested helper functions 
 *************************************************************************/  
  
/* Returns the height (number of nodes on the longest root-to-leaf path) of 
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.  Note: this 
 * should be an O(1) operation. 
 */  
  
int height(RAVL_Node* node){  
  if(node ==NULL){  
    return 0;  
  }  
  return node->height;  
}  
int size(RAVL_Node* node) { //my helper fcn.  
    if (node == NULL) return 0;  
    return node->size;  
}  
  
/* Returns the size (number of nodes) of the tree rooted at node 'node'. 
 * Returns 0 if 'node' is NULL.  Note: this should be an O(1) operation. 
 */  
  
  
/* Updates the height of the tree rooted at node 'node' based on the heights 
 * of its children. Note: this should be an O(1) operation. 
 */  
  
void updateHeight(RAVL_Node* node) {  
  int height_left=0;  
  int height_right=0;  
  if(node->left != NULL){  
    height_left = height(node->left);  
  }  
  if(node->right != NULL){  
    height_right = height(node->right);  
  }  
  
    node->height = (height_left>height_right ? height_left:height_right)+1;  
}  
  
  
/* Updates the size of the tree rooted at node 'node' based on the sizes 
 * of its children. Note: this should be an O(1) operation. 
 */  
void updateSize(RAVL_Node* node) {  
    int size_left = 0;   
    int size_right = 0;   
    if(node->left != NULL){  
        size_left = size(node->left);  
    }  
    if(node->right != NULL){  
        size_right = size(node->right);  
    }  
    node->size = size_left + size_right + 1;  
}  
  
  
/* Returns the bf factor (height of left subtree - height of right 
 * subtree) of node 'node'. Returns 0 if node is NULL.  Note: this should be 
 * an O(1) operation. 
 */  
  
int balanceFactor(RAVL_Node* node) {  
    if (node == NULL) {  
        return 0;  
    }  
    int height_left = 0;   
    int height_right = 0;  
    if(node->left != NULL){  
        height_left = height(node->left);  
    }  
    if(node->right != NULL){  
        height_right = height(node->right);  
    }  
    return height_left - height_right;  
}  
/* Returns the result of performing the corresponding rotation in the RAVL 
 * tree rooted at 'node'. 
 */  
RAVL_Node* rightRotation(RAVL_Node* node) {  
    RAVL_Node* leftChild = node->left;  
    RAVL_Node* leftRightChild = leftChild->right;  
    //rotation.  
    leftChild->right = node;  
    node->left = leftRightChild;  
  
    updateHeight(node);  
    updateHeight(leftChild);  
    updateSize(node);  
    updateSize(leftChild);  
  
    return leftChild; // update root.  
}  
RAVL_Node* leftRotation(RAVL_Node* node) {  
    RAVL_Node* rightChild = node->right;  
    RAVL_Node* rightLeftChild = rightChild->left;  
  
    rightChild->left = node;  
    node->right = rightLeftChild;  
  
    updateHeight(node);  
    updateHeight(rightChild);  
    updateSize(node);  
    updateSize(rightChild);  
  
    return rightChild;   
}  
RAVL_Node* rightLeftRotation(RAVL_Node* node) {  
    if (node == NULL){ return NULL;}  
    node->right = rightRotation(node->right);  
    return leftRotation(node);  
}  
RAVL_Node* leftRightRotation(RAVL_Node* node) {  
    if (node == NULL) {return NULL;}  
    node->left = leftRotation(node->left);  
    return rightRotation(node);  
}  
RAVL_Node* successor(RAVL_Node* node) {  
    RAVL_Node* current = node->right;  
    while (current != NULL && current->left != NULL) {  
        current = current->left;  
    }  
    return current;  
}  
/* Creates and returns an RAVL tree node with key 'key', value 'value', height 
 * and size of 1, and left and right subtrees NULL. 
 */  
RAVL_Node* createNode(int key, void* value) {  
    RAVL_Node* node = (RAVL_Node *)malloc(sizeof(RAVL_Node));   
    if (node == NULL) {  
        return NULL;  
    }  
    node->key = key;  
    node->value = value;   
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1;   
    node->size = 1;   
    return node;  
}  
  
  
/************************************************************************* 
 ** Provided functions 
 *************************************************************************/  
  
void printTreeInorder_(RAVL_Node* node, int offset) {  
  if (node == NULL) return;  
  printTreeInorder_(node->right, offset + 1);  
  printf("%*s %d [%d / %d]\n", offset, "", node->key, node->height, node->size);  
  printTreeInorder_(node->left, offset + 1);  
}  
  
void printTreeInorder(RAVL_Node* node) {  
  printTreeInorder_(node, 0);  
}  
  
void deleteTree(RAVL_Node* node) {  
  if (node == NULL) return;  
  deleteTree(node->left);  
  deleteTree(node->right);  
  free(node);  
}  
  
/************************************************************************* 
 ** Required functions 
 ** Must run in O(log n) where n is the number of nodes in a tree rooted 
 **  at 'node'. 
 *************************************************************************/  
  
RAVL_Node* search(RAVL_Node* node, int key) {  
    if (node == NULL) {  
        return node;  
    }  
  
    if (key < node->key) {  
        return search(node->left, key);  
    } else if (key > node->key) {  
        return search(node->right, key);  
    } else {  
        return node;  
    }  
}  
//for code readability.  
RAVL_Node* fcn_Rotation(RAVL_Node* node){  
    int bf = balanceFactor(node);  
    if(bf > 1){  
        if(balanceFactor(node->left) < 0){  
            node = leftRightRotation(node);   
        }else{  
            node = rightRotation(node);  
        }  
    } else if(bf < -1){  
        if(balanceFactor(node->right) > 0){  
            node = rightLeftRotation(node);  
        }  
        else{  
            node = leftRotation(node);  
        }  
    }  
    return node;   
}  
  
RAVL_Node* insert(RAVL_Node* node, int key, void* value) {  
    if (node == NULL){  
     return createNode(key, value);  
    }  
    if (key < node->key) {  
        node->left = insert(node->left, key, value);  
    } else if (key > node->key) {  
        node->right = insert(node->right, key, value);  
    } else { // == key  
        return node;  
    }  
  
    updateHeight(node);  
    updateSize(node);  
    node = fcn_Rotation(node);  
  
      
  
    return node;  
}  
// RAVL_Node* minValueNode(RAVL_Node* node) {  
//     RAVL_Node* current = node;  
  
//     while (current->left != NULL) {  
//         current = current->left;  
//     }  
  
//     return current;  
// }  
RAVL_Node* delete(RAVL_Node* node, int key) {  
    if (node == NULL) {  
      return node;  
    }  
  
    if (key < node->key)  
        node->left = delete(node->left, key);  
    else if (key > node->key)  
        node->right = delete(node->right, key);  
    else {  
      RAVL_Node* temp;  
      if(node->left==NULL){  
        temp = node->right;  
        free(node);  
        return temp;  
      }  
      if(node->right==NULL){  
        temp=node->left;  
        free(node);  
        return temp;  
      }  
      temp=successor(node);  
  
      node->key=temp->key;  
  
      node->value = temp->value;  
      node->right=delete(node->right,temp->key);  
    }  
  
  
    updateHeight(node);  
    updateSize(node);  
    node = fcn_Rotation(node);  
  
    return node;  
}  
  
int rank(RAVL_Node* node, int key) {  
    int r = 0;   
    while (node != NULL) {  
        if (key < node->key) {  
            node = node->left;  
        } else if (key > node->key) {  
            r += (node->left != NULL ? node->left->size : 0) + 1;  
            node = node->right;  
        } else {  
            r += (node->left != NULL ? node->left->size : 0) + 1;  
            return r;   
        }  
    }  
      
    return -1;   
}  
  
  
RAVL_Node* findRank(RAVL_Node* node, int rank) {  
    if (node == NULL) {  
      return NULL;   
    }  
    int leftSize = size(node->left);  
  
    int currentNodeRank = leftSize + 1;  
  
    if (rank == currentNodeRank) {  
        return node;  
    }   
    else if (rank < currentNodeRank) {  
        return findRank(node->left, rank);  
    } else {  
         
        return findRank(node->right, rank - currentNodeRank);  
    }  
}  