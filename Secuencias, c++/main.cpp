#include <iostream>
#include <vector>
using namespace std;
int p;

template <class T>
void print_vector(const vector<T>& vec){
    for(auto c: vec)
        cout<<c;
    cout<<'\n';
}

void Min_voraz(const vector<int>& A,const vector<int>& B){}

int Min_recursivo(vector<int> A, vector<int> B, int a, int b){
    A.erase(A.begin(), A.begin() + a);
    B.erase(B.begin(), B.begin() + b);
    int m = A.size();
    int n = B.size();
    if (m==1){
        int sumB=0;
        for(int i=0; i<n; i++)
            sumB = sumB+B[i];
        return A[0]/sumB;
    }
    if (n==1){
        int sumA=0;
        for(int i=0; i<m; i++)
            sumA = sumA+A[i];
        return sumA/B[0];
    }
    vector<int> posibles;
    for(int i=0; i<m-1; i++){
        int sumA=0;
        for(int j=0; j<=i; j++)
            sumA = sumA+A[j];
        posibles.push_back(sumA/B[0] + Min_recursivo(A,B,i,1));
    }
    for(int i=0; i<n-1; i++){
        int sumB=0;
        for(int j=0; j<=i; j++)
            sumB = sumB+B[j];
        posibles.push_back(A[0]/sumB + Min_recursivo(A,B,1,i));
    }
    return *min_element(posibles.begin(), posibles.end());
}

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

    Min_recursivo(A_blocks, B_blocks, 0, 0);

    return 0;
}