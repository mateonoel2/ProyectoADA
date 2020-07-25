#include <iostream>
#include <vector>
using namespace std;
int p,m,n;

vector<pair<int,int> > matching_voraz;

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
    float weight = 0;
    bool divided = false, combined = false;
    conectar(A[0], B[0]);
    int ACurrent = 0, BCurrent = 0;
    int ACWeigth = A[0], BCWeight = B[0];

    for(int i = 2; i < m+n; i++){
        if(BCurrent < n-1 && ACurrent < m-1){
            if(ACWeigth < BCWeight){
                if(ACurrent < m -2){
                    if(divided  || ACWeigth + A[ACurrent+1] >= BCWeight) {
                        weight += float(ACWeigth) / float(BCWeight);
                        ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                        i++;
                    }else{
                        combined = true; divided = false;
                        ACurrent++;
                        conectar(A[ACurrent], B[BCurrent]);
                        ACWeigth+=A[ACurrent];
                    }
                }
                else{
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                    i++;
                }
            }
            else{
                if(ACurrent < m-2){
                    if(combined || BCurrent >= n-2){
                        weight += float(ACWeigth) / float(BCWeight);
                        ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                        i++;
                    }
                    else{
                        BCurrent++;
                        BCWeight+= B[BCurrent];
                        conectar(A[ACurrent], B[BCurrent]);
                        divided =true, combined= false;
                    }
                }
                else{
                    weight += float(ACWeigth) / float(BCWeight);
                    ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                    i++;
                }
            }
        }
        else if (BCurrent >= n-1){
            ACurrent++;
            ACWeigth += A[ACurrent];
            conectar(A[ACurrent], B[BCurrent]);
        }
        else{
            BCurrent++;
            BCWeight += B[BCurrent];
            conectar(A[ACurrent], B[BCurrent]);
            if(BCurrent == n-1) break;
        }
    }
    weight += float(ACWeigth) / float(BCWeight);

    return weight;
}

float Min_recursivo(vector<int> A, vector<int> B, int a, int b){
    if (a==m-1){
        int sumB=0;
        for(int i=b; i<n; i++)
            sumB = sumB+B[i];
        return float(A[a])/float(sumB);
    }
    if (b==n-1){
        int sumA=0;
        for(int i=a; i<m; i++)
            sumA = sumA+A[i];
        return float(sumA)/float(B[b]);
    }
    vector<float> posibles;
    for(int i=a; i<=m-2; i++){
        int sumA=0;
        for(int j=a; j<=i; j++)
            sumA = sumA+A[j];
        posibles.push_back(float(sumA)/float(B[b]) + Min_recursivo(A,B,i+1,b+1));
    }
    for(int i=b; i<=n-2; i++){
        int sumB=0;
        for(int j=b; j<=i; j++)
            sumB = sumB+B[j];
        posibles.push_back(float(A[a])/float(sumB) + Min_recursivo(A,B,a+1,i+1));
    }
    return *min_element(posibles.begin(), posibles.end());
}

float Min_memoizado(vector<int> A, vector<int> B, int a, int b, float **M){
    if(bool(M[a][b]))
        return M[a][b];

    if (a==m-1){
        int sumB=0;
        for(int i=b; i<n; i++)
            sumB = sumB+B[i];
        M[a][b] = float(A[a])/float(sumB);
        return M[a][b];
    }
    if (b==n-1){
        int sumA=0;
        for(int i=a; i<m; i++)
            sumA = sumA+A[i];
        M[a][b] = float(sumA)/float(B[b]);
        return M[a][b];
    }
    vector<float> posibles;
    for(int i=a; i<=m-2; i++){
        int sumA=0;
        for(int j=a; j<=i; j++)
            sumA = sumA+A[j];
        posibles.push_back(float(sumA)/float(B[b]) + Min_memoizado(A,B,i+1,b+1, M));
    }
    for(int i=b; i<=n-2; i++){
        int sumB=0;
        for(int j=b; j<=i; j++)
            sumB = sumB+B[j];
        posibles.push_back(float(A[a])/float(sumB) + Min_memoizado(A,B,a+1,i+1, M));
    }
    M[a][b] = *min_element(posibles.begin(), posibles.end());
    return M[a][b];
}

float Min_dinamico(vector<int> A, vector<int> B){
    float Ma[m][n];

    for(int b=0; b<n; b++){
        int sumB=0;
        for(int i=b; i<n; i++)
            sumB = sumB+B[i];
        Ma[m-1][b] = float(A[m-1])/float(sumB);
    }

    for(int a=0; a<m; a++){
        int sumA=0;
        for(int i=a; i<m; i++)
            sumA = sumA + A[i];
        Ma[a][n-1] = float(sumA)/float(B[n-1]);
    }

    for(int a=m-2; a>=0; a--){
        for(int b=n-2; b>=0; b--){
            vector<float> posibles;
            for(int i=a; i<=m-2; i++){
                int sumA=0;
                for(int j=a; j<=i; j++)
                    sumA = sumA + A[j];
                posibles.push_back(float(sumA)/float(B[b]) + Ma[i+1][b+1]);
            }
            for(int i=b; i<=n-2; i++) {
                int sumB = 0;
                for (int j = b; j <= i; j++)
                    sumB = sumB + B[j];
                posibles.push_back(float(A[a])/float(sumB) + Ma[a+1][i+1]);
            }
            Ma[a][b] = *min_element(posibles.begin(), posibles.end());
        }
    }

    return Ma[0][0];
}

float promedio_dinamico(vector<int> A, vector<int> B){
    float Ma[m][n];
    int suma[m][m];
    int sumb[n][n];

    for(int i=0; i<m; i++)
        for (int j=0; j<m; j++)
            suma[i][j]=0;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            sumb[i][j]=0;

    for(int b=0; b<n; b++){
        int sumB=0;
        for(int i=b; i<n; i++)
            sumB = sumB+B[i];
        sumb[b][n-1] = sumB;
        Ma[m-1][b] = float(A[m-1])/float(sumB);
    }

    for(int a=0; a<m; a++){
        int sumA=0;
        for(int i=a; i<m; i++)
            sumA = sumA + A[i];
        suma[a][m-1] = sumA;
        Ma[a][n-1] = float(sumA)/float(B[n-1]);
    }

    for(int a=m-2; a>=0; a--){
        for(int b=n-2; b>=0; b--){
            vector<float> posibles;
            for(int i=a; i<=m-2; i++){
                int sumA=0;
                if(suma[a][i])
                    sumA = suma[a][i];
                else{
                    for(int j=a; j<=i; j++)
                        sumA = sumA + A[j];
                    suma[a][i] = sumA;
                }
                posibles.push_back(float(sumA)/float(B[b]) + Ma[i+1][b+1]);
            }
            for(int i=b; i<=n-2; i++) {
                int sumB = 0;
                if (sumb[b][i])
                    sumB = sumb[b][i];
                else {
                for (int j = b; j <= i; j++)
                    sumB = sumB + B[j];
                sumb[b][i] = sumB;
                }
                posibles.push_back(float(A[a])/float(sumB) + Ma[a+1][i+1]);
            }
            Ma[a][b] = *min_element(posibles.begin(), posibles.end());
        }
    }

    return Ma[0][0];
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

    m = A_blocks.size();
    n = B_blocks.size();

    cout<<"Vector A: ";
    print_vector(A_blocks);
    cout<<"Vector B: ";
    print_vector(B_blocks);


    cout<<"Min_Matching_Voraz: "<<Min_voraz(A_blocks, B_blocks);


    float **M;
    M = new float *[m];
    for(int i = 0; i < m; i++)
        M[i] = new float[n];

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            M[i][j] = 0;

    cout<<"\nMin_Matching_Memoizado: "<<Min_memoizado(A_blocks,B_blocks, 0, 0, M);

    cout<<"\nMin_Matching_Dinámico: "<<Min_dinamico(A_blocks,B_blocks);

    cout<<"\nMin_Matching_Dinámico_Optimizado: "<<promedio_dinamico(A_blocks,B_blocks);

    cout<<"\nMin_Matching_Recursivo: "<<Min_recursivo(A_blocks, B_blocks, 0, 0);
    return 0;
}