#include <iostream>
#include <vector>
using namespace std;
int p;

void Min_voraz(const vector<int>& A,const vector<int>& B){}

vector<int> getBlocks(const vector<bool>& vec){
    vector<int> blocks;
    for(int i = 0; i<p; i++){
        int newBlock = 0;
        if(vec[i]){
            while(vec[i]){
                newBlock++;
                i++;
            }
            blocks.push_back(newBlock);
        }
    }
    return blocks;
}

template <class T>
void print_vector(const vector<T>& vec){
    for(auto c: vec)
        cout<<c;
    cout<<'\n';
}

int main() {
    vector<bool> A, B;
    vector<int> A_blocks, B_blocks;
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

    print_vector(A_blocks);
    print_vector(B_blocks);

    Min_voraz(A_blocks, B_blocks);

    return 0;
}