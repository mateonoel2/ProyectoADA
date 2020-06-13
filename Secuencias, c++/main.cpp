#include <iostream>
#include <vector>
using namespace std;
int p;

void Min_voraz(){}

vector<pair<int,int>> getBlocks(const vector<bool>& vec){
    vector<pair<int,int>> blocks;
    pair<int, int> block;
    bool ones=false;
    for(int i = 0; i<p; i++){
        if (!ones){
            if(vec[i]) {
                ones = true;
                block.first = i;
            }
        }
        else{
            if(!vec[i]){
                ones = false;
                block.second = i-1;
                blocks.push_back(block);
            }
            else if(vec[i] and i==p-1){
                block.second = i;
                blocks.push_back(block);
            }
        }
    }
    return blocks;
}

void print_vector(const vector<bool>& vec){
    for(auto c: vec)
        cout<<c;
    cout<<'\n';
}

int main() {
    vector<bool> A, B;
    vector<pair<int,int>> A_blocks, B_blocks;
    string a, b;

    cout << "Enter size for vector A and B:\n";
    cin >> p;

    cout << "Enter booleans without any spaces\n";
    cout << "Enter A vector:\n";
    cin >> a;
    cout << "Enter B vector:\n";
    cin >> b;
    for(int i=0; i<p; i++){
        if(a[i] == '0') A.push_back(false);
        else if(a[i] == '1') A.push_back(true);

        if(b[i] == '0') B.push_back(false);
        else if(b[i] == '1') B.push_back(true);
    }

    //print_vector(A);
    //print_vector(B);
    A_blocks = getBlocks(A);
    B_blocks = getBlocks(B);

    Min_voraz();

    return 0;
}