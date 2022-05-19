/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
     if(first[curDim]<second[curDim]){
      return true;
    }
    else if(first[curDim]>second[curDim]){
      return false;
    }
    else{
      return (first<second);
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double curr=0;
    double pot=0;
    for(int i=0; i<Dim; i++){
      curr+=((target[i]-currentBest[i])*(target[i]-currentBest[i]));
      pot+=((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(pot!=curr){
      return pot<curr;
    }
    else{
      return potential<currentBest;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    if(newPoints.empty()){
      root=NULL;
      size=0;
      return;
    }
    vector<Point<Dim>> points=newPoints;
    int median=(points.size()-1)/2;
    quickSelect(median, 0, newPoints.size()-1, 0, points);
    root=new KDTreeNode(points[median]);
    size=1;
    root->right=constructor(median+1, newPoints.size()-1, 1%Dim, points);
    root->left=constructor(0,median-1, 1%Dim, points);
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructor(int first, int last, int curDim, vector<Point<Dim>> & newPoints)
{
    if(last<first){
        return NULL;
    }
    else{
        int median=(first+last)/2;
        quickSelect(median, first, last, curDim, newPoints);
        KDTreeNode* curr = new KDTreeNode(newPoints[median]);
        curr->left = constructor(first, median - 1, (curDim + 1) % Dim, newPoints);
        curr->right = constructor(median + 1, last, (curDim + 1) % Dim, newPoints);
        size+=1;
        return curr;
    }
}

template <int Dim>
void KDTree<Dim>::quickSelect(int k, int left, int right, int curDim, vector<Point<Dim>>& newPoints)
{
    if(left>=right){
        return;
    }
    int pivot=right;
    Point<Dim> pivot_data=newPoints[pivot];
    int start=left;
    for (int i=left; i<right; i++) {
        if(newPoints[i]<pivot_data && newPoints[i][curDim] == pivot_data[curDim]) {
            swap(newPoints[start], newPoints[i]);
            start+=1;
        } 
        if(newPoints[i][curDim]<pivot_data[curDim]) {
            swap(newPoints[start],newPoints[i]);
            start+=1;
        }
    }
    swap(newPoints[pivot],newPoints[start]);
    pivot=start;
    if(k>pivot){
      quickSelect(k,pivot+1,right, curDim, newPoints);
    }
    else if(k<pivot){
      quickSelect(k, left, pivot-1, curDim, newPoints);
    }
    else{
      return;
    }
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other)
{
    root=NULL;
    size=0;
    if(other.root){
        root=new KDTreeNode((other.root)->point);
        size=other.size;
        root->left=copy((other.root)->left);
        root->right=copy((other.root)->right);
    }
}



template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* cop) {
    if (!cop){
        return NULL;
    }
    KDTreeNode* curr=new KDTreeNode(cop->point);
    curr->right=copy(cop->right);
    curr->left=copy(cop->left);
    return curr;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
    if (*this != rhs) {
        if (root){
            del(root->left);
            del(root->right);
            delete root; 
            root = NULL;
        }
        size = 0;
        if (rhs.root) {
            root=new KDTreeNode((rhs.root)->point);
            size=rhs.size;
            root->left=copy((rhs.root)->left);
            root->right=copy((rhs.root)->right);
        }
    }
}

template <int Dim>
KDTree<Dim>::~KDTree() {
    if (root) {
        del(root->left);
        del(root->right);
        delete root; 
        root=NULL;
    }
    size=0;
}

template <int Dim>
void KDTree<Dim>::del(KDTreeNode* curr) {
    if (!curr) {
        return;
    }
    del(curr->left);
    del(curr->right);
    delete curr; 
    curr=NULL;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    Point<Dim> currentBest=root->point;
    nnsearch(query,root,currentBest,0);
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::nnsearch(const Point<Dim>& query, const KDTreeNode* subroot, Point<Dim>& currentBest, int curDim)const{
    bool change;
    
    if (subroot==NULL) {
        return;
    }

    if (query==subroot->point) {
        currentBest=subroot->point;
    }
    
    if (currentBest==root->point && subroot->leafCheck()) {
        currentBest=subroot->point;
    }

    bool dir=smallerDimVal(query, subroot->point, curDim);
   
    if (!dir) {
        nnsearch(query, subroot->right, currentBest,(curDim+1) % Dim);
        change=false;
        
    } 
    else if(dir){
        nnsearch(query, subroot->left, currentBest,(curDim+1) % Dim );
        change=true;
    }

    if (shouldReplace(query, currentBest, subroot->point)) {
        currentBest=subroot->point;
    }

    Point<Dim> split=query;
    split[curDim]=subroot->point[curDim];
    if (shouldReplace(query, currentBest, split)) {
        if (change==false) {
            nnsearch(query, subroot->left, currentBest, (curDim+1) % Dim);
        } 
        else if(change==true) {
            nnsearch(query, subroot->right, currentBest, (curDim+1) % Dim);
        }
        if(shouldReplace(query, currentBest, subroot->point)){
            currentBest = subroot->point;
        }
    }
}
