#include <iostream>
#include <vector>
using namespace std;
int p;

vector<pair<int,int>> matching_voraz;

template <class T>
void print_vector(const vector<T>& vec){
    for(auto c: vec)
        cout<<c;
    cout<<'\n';
}

void conectar(int A, int B){
    auto* paircito = new pair<int, int>(A, B);
    matching_voraz.push_back(*paircito);
    delete paircito;
}

void ResetConection(int &ACurrent, int &BCurrent, int &BCWeight, int&ACWeigth, vector<int> A, vector<int> B, bool &divided, bool &combined, float &weight){
    ACurrent++;
    BCurrent++;
    conectar(A[ACurrent], B[BCurrent]);
    ACWeigth = A[ACurrent];
    BCWeight = B[BCurrent];
    divided = false; combined = false;
}

float Min_voraz(const vector<int>& A,const vector<int>& B){
    int sizeA = A.size(), sizeB = B.size();
    float weight = 0;
    bool divided = false, combined = false;
    conectar(A[0], B[0]);
    int ACurrent = 0, BCurrent = 0;
    int ACWeigth = A[0], BCWeight = B[0];

   for(int i = 0; i < sizeA; i++){
        //Comprobamos que no estemos en el último elemento
        if(BCurrent < sizeB-1 && ACurrent < sizeA-1){
            if (!i)i++;
            //Si el peso de A es menor que el de B, evaluamos si conviene o no meter otro A.
            if(ACWeigth < BCWeight){
                if(ACurrent < sizeA -2){
                if(divided  || ACWeigth + A[ACurrent+1] >= BCWeight) { //Para evitar que una conexión sea agrupada y dividida a la vez.
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                }else{ //Acá si combiene agregar más As.
                    combined = 1; divided = 0;
                    ACurrent++;
                    conectar(A[ACurrent], B[BCurrent]);
                    ACWeigth+=A[ACurrent];
                }
                }
                else{
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                }
            }
            else{
                //Si el peso ed A es mayor al de B, analizamos si se puede agregar más Bs.
                if(ACurrent < sizeA-2){
                if(combined || BCurrent >= sizeB-2){
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                }
                else{
                    BCurrent++;
                    i--;
                    BCWeight+= B[BCurrent];
                    conectar(A[ACurrent], B[BCurrent]);
                    divided =1, combined=0;
                }
                }
                else{
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                }
            }
        }
        //Cuando A sea el último elemento, se conecta a todos los B restantes.
        else if (BCurrent >= sizeB-1){
            if(!i)i++;
            ACurrent++;
            ACWeigth += A[ACurrent];
            conectar(A[ACurrent], B[BCurrent]);
        }
        //Cuando B sea el último elemento, se conecta a todos los A restantes.
        else{
            BCurrent++;
            i--;
            BCWeight += B[BCurrent];
            conectar(A[ACurrent], B[BCurrent]);
            if(BCurrent == sizeB-1)break;
        }
    }
    weight += float(ACWeigth) / float(BCWeight);

    for(auto c : Matching){
        cout << c.first << "," << c.second << endl;
    }
    return weight;
}
float Min_recursivo(vector<int> A, vector<int> B, int a, int b){
    A.erase(A.begin(), A.begin() + a);
    B.erase(B.begin(), B.begin() + b);
    int m = A.size();
    int n = B.size();
    if (m==1){
        int sumB=0;
        for(int i=0; i<n; i++)
            sumB = sumB+B[i];
        return float(A[0])/float(sumB);
    }
    if (n==1){
        int sumA=0;
        for(int i=0; i<m; i++)
            sumA = sumA+A[i];
        return float(sumA)/float(B[0]);
    }
    vector<float> posibles;
    for(int i=0; i<m-2; i++){
        int sumA=0;
        for(int j=0; j<=i; j++)
            sumA = sumA+A[j];
        posibles.push_back(float(sumA)/float(B[0]) + Min_recursivo(A,B,i,1));
    }
    for(int i=0; i<n-2; i++){
        int sumB=0;
        for(int j=0; j<=i; j++)
            sumB = sumB+B[j];
        posibles.push_back(float(A[0])/float(sumB) + Min_recursivo(A,B,1,i));
    }
    return *min_element(posibles.begin(), posibles.end());
}

float Min_memoizado(vector<int> A, vector<int> B, int a, int b, float **M){
    if(bool(M[a][b]))
        return M[a][b];
    A.erase(A.begin(), A.begin() + a);
    B.erase(B.begin(), B.begin() + b);
    int m = A.size();
    int n = B.size();
    if (m==1){
        int sumB=0;
        for(int i=0; i<n; i++)
            sumB = sumB+B[i];
        return float(A[0])/float(sumB);
    }
    if (n==1){
        int sumA=0;
        for(int i=0; i<m; i++)
            sumA = sumA+A[i];
        return float(sumA)/float(B[0]);
    }
    vector<float> posibles;
    for(int i=0; i<m-2; i++){
        int sumA=0;
        for(int j=0; j<=i; j++)
            sumA = sumA+A[j];
        posibles.push_back(float(sumA)/float(B[0]) + Min_recursivo(A,B,i,1));
    }
    for(int i=0; i<n-2; i++){
        int sumB=0;
        for(int j=0; j<=i; j++)
            sumB = sumB+B[j];
        posibles.push_back(float(A[0])/float(sumB) + Min_recursivo(A,B,1,i));
    }
    M[a][b] = *min_element(posibles.begin(), posibles.end());
    return M[a][b];
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

    A_blocks = getBlocks(A);
    B_blocks = getBlocks(B);

    cout<<"Vector A: ";
    print_vector(A_blocks);
    cout<<"Vector B: ";
    print_vector(B_blocks);


    cout<<"Min_Matching_Voraz: "<<Min_voraz(A_blocks, B_blocks);

    cout<<"\nMin_Matching_Recursivo: "<<Min_recursivo(A_blocks, B_blocks, 0, 0);

    int m = A_blocks.size();
    int n = B_blocks.size();
    float **M;
    M = new float *[m];
    for(int i = 0; i < m; i++)
        M[i] = new float[n];

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            M[i][j] = 0;
        }
    }
    cout<<"\nMin_Matching_Memoizado: "<<Min_memoizado(A_blocks,B_blocks, 0, 0, M);

    return 0;
}
