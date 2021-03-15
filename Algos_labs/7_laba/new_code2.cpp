#include<fstream>
#include<iostream>
#include <vector>
using namespace std;
struct node
{
    int v; 
    int left ;
    int right;
    int height;
    int balance;
};
int max(int a, int b){
    return a>b ? a : b;
}
void find_h(vector <node> & MyVector, int k){
    if (MyVector[k].left != -1) 
        find_h(MyVector, MyVector[k].left); 
        
    if (MyVector[k].right != -1) {
       find_h(MyVector, MyVector[k].right);
    }
    if (MyVector.at(k).left == -1 && MyVector.at(k).right == -1){
           MyVector.at(k).height = 1;
           return;
       }
    if (MyVector.at(k).left != -1 && MyVector.at(k).right == -1){
           MyVector.at(k).height = MyVector[MyVector[k].left].height+1;
           return;
       }
    if (MyVector.at(k).left == -1 && MyVector.at(k).right != -1){
           MyVector.at(k).height = MyVector[MyVector[k].right].height +1;
           return;
       }
    if (MyVector.at(k).left != -1 && MyVector.at(k).right != -1){
           MyVector.at(k).height = max (MyVector[MyVector[k].left].height, MyVector[MyVector[k].right].height )+1;
           return;
       }
  
}

    void small_left_turn (vector <node> & MyVector){
     int root_right = MyVector[0].right;
     int root_left = MyVector[0].left;
     int b_right = MyVector[MyVector[0].right].right;
     int b_left = MyVector[MyVector[0].right].left;
     int x_left =MyVector[MyVector[0].right].right ;//MyVector[MyVector[0].left].left;
     int x_right = MyVector[MyVector[0].right].left;//MyVector[MyVector[0].left].right;
     int save_a =MyVector[0].v;
     int save_x = MyVector[root_left].v;

     MyVector[0].v = MyVector[root_right].v;
     MyVector[root_right].v = MyVector[b_right].v;
     MyVector[root_left].v = save_a;
     MyVector [x_left].v =save_x;
     MyVector [x_right].v = MyVector[b_left].v;
     MyVector[root_right].right = MyVector[b_right].right;
     MyVector[root_right].left = MyVector[b_right].left;  
     MyVector[root_left].left = x_left;
     MyVector[root_left].right = x_right;     
}
    void big_left_turn(vector <node>& a){
     int root_right = a[0].right;
     int root_left = a[0].left;
     int b_right = a[a[0].right].right;
     int b_left = a[a[0].right].left;
     int c_left = a[b_left].left;
     int c_right = a[b_left].right;
     int w_left =c_left ;//MyVector[MyVector[0].left].left;
     int w_right = c_right;//MyVector[MyVector[0].left].right;
     int save_a =a[0].v;
     int save_w = a[root_left].v;
     int save_c =a[b_left].v;
     
     a[0].v = save_c;
     a[b_left].v = a[c_right].v;
     a[root_left].v =save_a;
     a[w_right].v = a[c_left].v;
     a[w_left].v = save_w;
     a[root_left].left = w_left;
     a[root_left].right = w_right;
     a[b_left].left = -1;
     a[b_left].right = -1;
     //cout << a[0].v << " " << a[b_left].v << "  " << a[w_left].v << " " << a[w_right].v << " " <<  a[c_right].v << " \n"; 
     
    }
int main() {
    ifstream fin("rotationin.txt");
    ofstream fout("rotationout.txt");
    int n, left, right, value;
     fin >> n;
    vector<node> MyVector;
    for (int i = 0; i < n; i++) {
        node e;
        fin >> value >> left >> right;
        MyVector.push_back(e);
        MyVector.at(i).v = value;
        MyVector.at(i).left = left-1;
        MyVector.at(i).right = right-1;
    }
        find_h(MyVector, 0);
     for ( int i = 0; i <n; i++){
         if (MyVector[i].left == -1 && MyVector[i].right != -1)  {
             MyVector[i].balance = MyVector[MyVector[i].right].height;
         } 
         else if (MyVector[i].left != -1 && MyVector[i].right == -1 ){ 
             MyVector[i].balance = -MyVector[MyVector[i].left].height;
         } 
         else if (MyVector[i].left != -1 && MyVector[i].right != -1  ){
             MyVector[i].balance = MyVector[MyVector[i].right].height - MyVector[MyVector[i].left].height;
         }
         else if (MyVector[i].left == -1 && MyVector[i].right == -1  ){
             MyVector[i].balance = 0;
         } 
     }
    if (MyVector[MyVector[0].right].balance ==-1){
        big_left_turn(MyVector);
    }
    else 
    small_left_turn(MyVector);
    vector<int> stack;
    fout << n <<" \n";
    for (int i = 0; i<n; i++){
        if (i< left+1 && i<right+1)
         fout << MyVector[i].v << " " << MyVector[i].left+1 << " " << MyVector[i].right+1 << "\n";
        else 
            stack.push_back(i);
    }
    for (int i = 0; i < stack.size(); i++)
    {
        fout << MyVector[stack[i]].v << " " << MyVector[stack[i]].left+1 << " " << MyVector[stack[i]].right+1<< "\n" ;
    }
    fin.close();
    fout.close();
    return 0;
}