#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <unistd.h>
#include <utility>
#include <cmath>
#include <climits>

using namespace std;
vector<pair<int,int>> din_Match;
vector<pair<int,char>> din_MatchSize;
vector<vector<pair<int,int>>> din_MatrizMatch;
vector<vector<pair<int,char>>> din_MatrizMatchSize;
int q;
int MB_voraz[10][240]={0};
int Answer[10][240]={0};
int MA_voraz[10][240]={0};
ifstream* imagen;
string fullData = "";
vector <int> Parsed;


//LECTURA DE IMÁGENES
vector<int> decode(int numero){
    vector<int> resultado;
    int potencia;
    for(int i = 7; i>= 0; i--){
        potencia = pow(2, i);
        if(numero < potencia)
            resultado.push_back(0);
        else{
            resultado.push_back(1);
            numero -= potencia;
        }
    }
    return resultado;
}
void decodeMain(vector <int> main, string matrix){
    int counter = 0;

    for(auto c : main){
        auto temp = decode(c);
        for(auto d: temp){
            if(matrix == "A")
                MA_voraz[0][counter] = d;
            else if(matrix == "B")
                MB_voraz[0][counter] = d;
            counter++;
        }
    }

}
int encode(vector <int> numero){
    int counter = 7;
    int resultado = 0;

    for(auto c : numero){
        resultado += c*pow(2, counter);
        counter--;
    }
    return resultado;
}
void readImage(const string imageName, string matrix){
    bool ready = false, readySize = false;
    int readyCounter = 0;
    imagen = new ifstream(imageName);
    string data, temp2;

    while(!imagen->eof()){
        *imagen >> data;
        int* temp;
        if(ready){
            fullData += data;
            temp = new int(stoi(data));
            Parsed.push_back(*temp);
            delete temp;

        }
        else if(data == "255"){
            ready = true;
        }else if(data[0] == 'P'){
            readySize = true;
        }

    }

}
void writeImage(const string imageName, int matrix[10][240]){
    ofstream output (imageName);
    vector<int> temporal;
    output << "P3" << endl;
    output << 10 << " " << 10 << endl;
    output << "255" << endl;
    int counter = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 240; j++){
            for(int k = 0; k < 8; k++){
                temporal.push_back(matrix[i][j]);
                j++;
            }
            output << encode(temporal);
            counter++;
            if(counter == 3){
                output << endl;
                counter = 0;
            }else{
                output << " ";
            }
            temporal.clear();
            j--;
        }
    }
}
vector<int> getBlocks(const vector<bool>& vec){
    vector<int> blocks;
    for(int i = 0; q < i; i++){
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

//ESCRITURA DE IMÁGENES
void Transformation(int Matrix_a[10][240], int Matrix_B[10][240], int combs, char source, int i, vector<pair<int,int>> matching, int &indexA, int &indexB, int iteratorMatching) {
    //vector de grupos de 1
    vector<string> bits;
    bits.clear();
    int indice_temp = 0;
    int isOne = false;
    int *A = new int[combs];
    if (source == 'x') {
        for (int k = 0; k < 240; k++) {
            Answer[i][k] = Matrix_a[i][k];
        }
    }
    else if (combs == 0){
        if (source == 'b'){
            for (int l = 0; l < 240; l++){
                if(Matrix_a[i][l] == 0){
                    Answer[i][l] = 0;
                }else{
                    if (isOne){
                        Answer[i][l] = 0;
                        isOne = false;
                    }else{
                        Answer[i][l] = 1;
                        isOne = true;
                    }

                }
            }
        }else{
            //Cuando A está vacío y B tiene varios
            for (int f = 0; f < 240; f++){
                if(Matrix_B[i][f] == 0){
                    Answer[i][f] = 0;
                }else{
                    if (isOne){
                        Answer[i][f] = 0;
                        isOne = false;
                    }else{
                        Answer[i][f] = 1;
                        isOne = true;
                    }

                }
            }
        }
    }
    else{

        if(source == 'a'){

            int pesoA = matching[iteratorMatching].first;
            vector <int> b;
            b.clear();
            b.reserve(combs);
            for(int q = 0; q < combs; q++){
                b.push_back(matching[iteratorMatching+q].second);
            }

            if(b.size() >= pesoA){
                for(auto c : b){
                    bits.push_back("1");
                }
            }else{
                int suma = 0;
                for(auto c : b){
                    suma += c;
                }
                for(auto c : b){
                    auto result = round( c*pesoA/suma);
                    string respuesta;
                    for(int d = 0; d < result; d++){
                        respuesta+= "1";
                    }
                    bits.push_back(respuesta);
                }
            }
        }
        else if (source == 'b'){
            int pesoB = matching[iteratorMatching].second;
            vector <int> a;
            a.clear();
            a.reserve(combs);
            for(int q = 0; q < combs; q++){
                a.push_back(matching[iteratorMatching+q].first);
            }

            if(a.size() >= pesoB){
                for(auto c : a){
                    bits.push_back("1");
                }
            }else{
                int suma = 0;
                for(int g = 0; g < combs; g++){
                    a.push_back( matching[iteratorMatching+g].first);
                    suma += matching[iteratorMatching+g].first;
                }

                for(auto c : a){
                    string resultado;
                    auto result = floor( c*pesoB/suma);
                    for(int d = 0; d < result; d++){
                        resultado += "1";
                        bits.push_back(resultado);
                    }
                }
            }
        }

        for(auto c : bits){
            //Iteramos matriz B
            while( indexB < 240 && Matrix_B[i][indexB] == 0){
                Answer[i][indexB] = 0;
                indexB++;
            }
            //indexB++;
            //indice_temp = indexB;
            for(auto e : c){
                if(indexB < 240){
                    Answer[i][indexB] = e-48;
                    indexB++;
                }
            }
        }

    }
}
void matchToBin( vector< vector <pair <int,int>>> Transform, vector< vector <pair <int,char>>> combSize, int Matrix_A[10][240], int Matrix_B[10][240]){
    int counterFila = 0;
    int counterColumnas = 0;

    for (int i = 0; i < 10; i++){
        int indexA = 0;
        int indexB = 0;
        int iteratorMatching = 0;
        for(auto c : combSize[i]){
            Transformation(Matrix_A, Matrix_B, c.first, c.second, i, Transform[i], indexA, indexB, iteratorMatching);
            iteratorMatching+=c.first;
        }
    }
}


//TRANNSFORMACIÓN VORAZ
int p,m,n;
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
pair<vector<pair<int,int>>, vector <pair<int,char>>> Min_voraz(const vector<int>& A,const vector<int>& B){
    vector <pair <int,char>> CombSize;
    char source;
    float weight = 0;
    bool divided = false, combined = false;
    if(!A.empty() && !B.empty()) {

        int paircounter = 1;
        conectar(A[0], B[0]);
        int ACurrent = 0, BCurrent = 0;
        int ACWeigth = A[0], BCWeight = B[0];
        bool last = false;

        for (int i = 2; i < m + n; i++) {
            if (BCurrent < n - 1 && ACurrent < m - 1) {
                if (ACWeigth < BCWeight) {
                    if (ACurrent < m - 2) {
                        if (divided || ACWeigth + A[ACurrent + 1] >= BCWeight) {
                            weight += float(ACWeigth) / float(BCWeight);
                            ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                            CombSize.push_back({paircounter, 'a'});
                            paircounter = 1;
                            i++;
                        } else {
                            combined = true;
                            divided = false;
                            ACurrent++;
                            conectar(A[ACurrent], B[BCurrent]);
                            paircounter++;
                            ACWeigth += A[ACurrent];
                        }
                    } else {
                        weight += float(ACWeigth) / float(BCWeight);
                        ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                        CombSize.push_back({paircounter,'b'});
                        paircounter = 1;
                        i++;
                    }
                } else {
                    if (ACurrent < m - 2) {
                        if (combined || BCurrent >= n - 2) {
                            weight += float(ACWeigth) / float(BCWeight);
                            ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                            CombSize.push_back({paircounter,'b'});
                            paircounter = 1;
                            i++;
                        } else {
                            BCurrent++;
                            BCWeight += B[BCurrent];
                            conectar(A[ACurrent], B[BCurrent]);
                            paircounter++;
                            divided = true, combined = false;
                        }
                    } else {
                        weight += float(ACWeigth) / float(BCWeight);
                        ResetConection(ACurrent, BCurrent, BCWeight, ACWeigth, A, B, divided, combined, weight);
                        CombSize.push_back({paircounter,'a'});
                        paircounter = 1;
                        i++;
                    }
                }
            } else if (BCurrent >= n - 1) {
                paircounter++;
                ACurrent++;
                ACWeigth += A[ACurrent];
                conectar(A[ACurrent], B[BCurrent]);
                source = 'b';
            } else {
                paircounter++;
                BCurrent++;
                BCWeight += B[BCurrent];
                conectar(A[ACurrent], B[BCurrent]);
                if (BCurrent == n - 1) break;
                source = 'a';
            }
        }

        CombSize.push_back({paircounter, source});
        weight += float(ACWeigth) / float(BCWeight);
    }
    else{
        if(A.empty() && B.empty()){
            conectar(0,0);
            CombSize.push_back({0, 'x'});
        }
        else if(A.empty()){
            for(int i = 0; i < B.size(); i++){
                conectar(0, B[i]);
            }
            CombSize.push_back({0, 'a'});
        }else if(B.empty()){
            for(int i = 0; i < A.size(); i++){
                conectar(A[i], 0);
            }
            CombSize.push_back({0, 'b'});
        }else{
            conectar(0,0);
            CombSize.push_back({0, 'a'});
        }
    }
    pair< vector<pair<int,int> >, vector<pair<int,char>>>* answer;
    auto temp = matching_voraz;

    answer->first = temp;
    answer->second = CombSize;
    return *answer;
}
vector<int> getBlocks(const vector<bool>& vec, int size){
    vector<int> blocks;
    for(int k = 0; k<vec.size(); k++){
        int newBlock = 0;
        if(vec[k]){
            while(vec[k]){
                newBlock++;
                k++;
            }
            blocks.push_back(newBlock);
        }
    }
    return blocks;
}
pair< vector<vector <pair<int,int>>>   , vector<vector <pair<int, char>> >>  Min_voraz_Matriz(int Matrix_A[10][240], int Matrix_B[10][240], int filas, int columnas){
    vector<bool> AB, BB;

    vector< vector<pair<int,int>> > filaMatching;
    vector< vector<pair<int,char>>> filaCombSize;

    vector<int> A_blocksM, B_blocksM;
    float peso =  0;
    for(int i = 0; i < filas; i++){
        for(int j=0; j<columnas; j++){
            if(Matrix_A[i][j] == 0) AB.push_back(false);
            else if(Matrix_A[i][j] == 1) AB.push_back(true);

            if(Matrix_B[i][j] ==0) BB.push_back(false);
            else if(Matrix_B[i][j] == 1) BB.push_back(true);
        }

        A_blocksM = getBlocks(AB,columnas);
        B_blocksM = getBlocks(BB, columnas);
        cout << "\n";
        m = A_blocksM.size();
        n = B_blocksM.size();
        matching_voraz.clear();

        auto temp = Min_voraz(A_blocksM, B_blocksM);

        filaMatching.push_back(temp.first);
        filaCombSize.push_back(temp.second);

        AB.clear();
        BB.clear();
        A_blocksM.clear();
        B_blocksM.clear();
    }

    pair< vector<vector <pair<int,int>>>   , vector<vector <pair<int, char>> >> answer;
    answer.first = filaMatching;
    answer.second = filaCombSize;
    return answer;
}

//tranformacion dinamica
vector<int> getBlocks(const vector<int>& vec){
    vector<int> blocks;
    for(int i = 0; i < q; i++){
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
float Min_dinamico(vector<int> A, vector<int> B){

    if (A.empty() and B.empty()){
        pair<int, char> casx = {0,'x'};
        din_MatchSize.push_back(casx);
        return 0;
    }
    if (A.empty()){
        pair<int, char> casa = {0,'a'};
        din_MatchSize.push_back(casa);
        return 0;
    }
    if (B.empty()){
        pair<int, char> casb = {0,'b'};
        din_MatchSize.push_back(casb);
        return 0;
    }

    int m = A.size();
    int n = B.size();
    float Ma[m][n];
    vector<pair<int,int>> totalMatch[m][n];
    vector<pair<int,char>> totalSizes[m][n];

    for(int b=0; b<n; b++){
        int sumB=0;
        vector<pair<int,int>> match;
        int mSize = 0;
        pair<int,int> join;
        pair<int,char> one;

        for(int i=b; i<n; i++) {
            sumB = sumB + B[i];
            join.first = A[m-1];
            join.second = B[i];
            match.push_back(join);
            mSize++;
        }
        Ma[m-1][b] = float(A[m-1])/float(sumB);
        vector<pair<int,char>> r;
        one.first = mSize;
        one.second = 'a';
        r.push_back(one);
        totalMatch[m-1][b] = match;
        totalSizes[m-1][b] = r;
    }

    for(int a=0; a<m; a++){
        int sumA=0;
        vector<pair<int,int>> match;
        int mSize = 0;
        pair<int,int> join;
        pair<int,char> one;

        for(int i=a; i<m; i++){
            sumA = sumA + A[i];
            join.first = A[i];
            join.second = B[n-1];
            match.push_back(join);
            mSize++;
        }

        Ma[a][n-1] = float(sumA)/float(B[n-1]);
        vector<pair<int,char>> r;
        one.first = mSize;
        one.second = 'b';
        r.push_back(one);
        totalMatch[a][n-1] = match;
        totalSizes[a][n-1] = r;
    }

    vector<float> posibles;
    vector<vector<pair<int,int>>> matches;
    vector<vector<pair<int,char>>> matchSize;

    for(int a=m-2; a>=0; a--){
        for(int b=n-2; b>=0; b--){
            posibles.clear();
            matches.clear();
            matchSize.clear();

            for(int i=a; i<=m-2; i++){
                int sumA=0;
                vector<pair<int,int>> match;
                pair<int,int> join;
                vector<pair<int,char>> si;
                pair<int,int> one;
                int mSize = 0;

                for(int j=a; j<=i; j++){
                    sumA = sumA + A[j];
                    join.first = A[j];
                    join.second = B[b];
                    match.push_back(join);
                    mSize++;
                }
                posibles.push_back(float(sumA)/float(B[b]) + Ma[i+1][b+1]);

                for(auto c : totalMatch[i+1][b+1])
                    match.push_back(c);

                matches.push_back(match);

                one.first= mSize;
                one.second = 'b';
                si.push_back(one);

                for(auto c : totalSizes[i+1][b+1])
                    si.push_back(c);

                matchSize.push_back(si);
            }

            for(int i=b; i<=n-2; i++) {
                int sumB = 0;
                vector<pair<int,int>> match;
                pair<int,int> join;
                vector<pair<int,char>> si;
                pair<int,int> one;
                int mSize = 0;

                for (int j = b; j <= i; j++){
                    sumB = sumB + B[j];
                    join.first = A[a];
                    join.second = B[j];
                    match.push_back(join);
                    mSize++;
                }

                posibles.push_back(float(A[a])/float(sumB) + Ma[a+1][i+1]);

                for(auto c : totalMatch[a+1][i+1])
                    match.push_back(c);

                matches.push_back(match);

                one.first = mSize;
                one.second = 'a';
                si.push_back(one);
                for(auto c : totalSizes[a+1][i+1])
                    si.push_back(c);

                matchSize.push_back(si);
            }

            float pos_min = INT_MAX;
            unsigned long index_min = 0;
            for(unsigned long i=0; i<posibles.size(); i++){
                if (posibles[i]<pos_min){
                    pos_min = posibles[i];
                    index_min = i;
                }
            }

            Ma[a][b] = pos_min;
            totalMatch[a][b] = matches[index_min];
            totalSizes[a][b] = matchSize[index_min];
        }
    }
    din_Match = totalMatch[0][0];
    cout<<"\n\n";
    for(auto c: din_Match){
        cout<<'{'<<c.first<<','<<c.second<<'}'<<" ";
    }
    cout<<"\n";

    din_MatchSize = totalSizes[0][0];
    for(auto c: din_MatchSize){
        cout<<'{'<<c.first<<','<<c.second<<'}'<<" ";
    }
    return Ma[0][0];
}
float Matching_dinamico(int A[10][240], int B[10][240]){
    float total = 0;

    for(int i=0; i<p; i++){
        vector<int> A_i;
        vector<int> B_i;

        for(int j=0; j<q; j++){
            A_i.push_back(A[i][j]);
            B_i.push_back(B[i][j]);
        }
        total = Min_dinamico(getBlocks(A_i),getBlocks(B_i)) + total;
        A_i.clear();
        B_i.clear();

        din_MatrizMatch.push_back(din_Match);
        din_MatrizMatchSize.push_back(din_MatchSize);
    }
    return total;
}
void animacion_din(int A[10][240], int B[10][240]){
    for(int i=0; i<p; i++){
        cout<<'\n';
        for (int j = 0; j < q; j++){
            cout<<A[i][j]<<" ";
        }
    }
    cout<<'\n';
    for(int i=0; i<p; i++){
        cout<<'\n';
        for (int j = 0; j < q; j++){
            cout<<B[i][j]<<" ";
        }
    }
    Matching_dinamico(A,B);
};


int main() {
    p = 10;
    q = 240;
    cout << "Debe de eliminar los comentarios para ejecutar alguna de las funcionalidades" << endl;
    //PROCEDIMIENTO CON MATRICES-VORAZ----------------------------------------------------------------------------------

    /*GENERA LOS 5 FRAMES COMO IMÁGENES
    matching_voraz.clear();

    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    auto answer = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer.first, answer.second, MA_voraz, MB_voraz);
    writeImage("match.ppm", Answer);
    matching_voraz.clear();

    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("match.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();


    auto answer2 = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer2.first, answer2.second, MA_voraz, MB_voraz);
    writeImage("match_prev.ppm", Answer);

    matching_voraz.clear();

    Parsed.clear();
    readImage("match.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    auto answer3 = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer3.first, answer3.second, MA_voraz, MB_voraz);
    writeImage("match_post.ppm", Answer);

     */


    //ANIMACIÓN VORAZ----------------------------------------------------------------------------------------------------
    /*
    sleep(1);
    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");
    Parsed.clear();
    readImage("match.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    writeImage("animacion.ppm", MA_voraz);

    sleep(1);

    auto answer2 = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer2.first, answer2.second, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

    matching_voraz.clear();
    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");
    Parsed.clear();
    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    auto answer = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer.first, answer.second, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

    sleep(1);
    matching_voraz.clear();
    sleep(1);
    matching_voraz.clear();
    Parsed.clear();
    readImage("match.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();
    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    auto answer3 = Min_voraz_Matriz(MA_voraz, MB_voraz, 10, 240);
    matchToBin(answer3.first, answer3.second, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

    sleep(1);

    readImage("testdosdos.ppm", "B");
    writeImage("animacion.ppm", MB_voraz);
     */

    //PROSECAMIENTO DINÁMMICO - GENERAR ARCHIVOS------------------------------------------------------------------------
/*
    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();


    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("match.ppm", Answer);

    din_Match.clear();
    din_MatchSize.clear();
    din_MatrizMatch.clear();
    din_MatrizMatchSize.clear();

    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("match.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("prev.ppm", Answer);

    din_Match.clear();
    din_MatchSize.clear();
    din_MatrizMatch.clear();
    din_MatrizMatchSize.clear();

    Parsed.clear();
    readImage("match.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("post.ppm", Answer);
*/

    //ANIMACIÓN DINAMICA-----------------------------------------------------------------------------------------------|
/*
    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    writeImage("animacion.ppm", MA_voraz);
    //sleep(1);
    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

    //sleep(1);

    din_Match.clear();
    din_MatchSize.clear();
    din_MatrizMatch.clear();
    din_MatrizMatchSize.clear();

    Parsed.clear();
    readImage("testdos.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("match.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

    //sleep(1);

    din_Match.clear();
    din_MatchSize.clear();
    din_MatrizMatch.clear();
    din_MatrizMatchSize.clear();

    Parsed.clear();
    readImage("match.ppm", "A");
    decodeMain(Parsed, "A");

    Parsed.clear();

    readImage("testdosdos.ppm", "B");
    decodeMain(Parsed, "B");
    Parsed.clear();

    animacion_din(MA_voraz, MB_voraz);
    matchToBin(din_MatrizMatch, din_MatrizMatchSize, MA_voraz, MB_voraz);
    writeImage("animacion.ppm", Answer);

 */
    return 0;
}