/* Your code here! */
#include "dsets.h"
#include <vector>
void DisjointSets::addelements(int num){
    if(set.empty()){
        set.assign(num,-1);
    }
    else{
        for(int i=0; i<num; i++){
            set.push_back(-1);
        }
    }
}
int DisjointSets::find(int elem){
    int result=0;
    if(set[elem]<0){
        result=elem;
    }
    else{
        result=find(set[elem]);
        set[elem]=result;
    }
    return result;
}
void DisjointSets::setunion(int a, int b){
    a=find(a);
    b=find(b);
    int newSize=set[a]+set[b];
    if(set[a]<set[b]){
        set[b]=a;
        set[a]=newSize;
    }
    else{
        set[a]=b;
        set[b]=newSize;
    }

}
int DisjointSets::size(int elem){
    return abs(set[find(elem)]);
}