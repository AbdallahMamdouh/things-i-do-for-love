#include <iostream>
using namespace std;
template <class T>
double determinant( T **matrix, int n) {
    int det = 0;
    T** submatrix=new T*[n-1];
    for(int i=0;i<n;i++){
        submatrix[i]=new T[n-1];
    }
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
        }
    }
    return det;
}
class matrix{
public:
    int**data;
    int size;
    void operator=(matrix right){
        size=right.size;
        data=new int*[size];
        for(int i=0;i<size;i++){
            data[i]=new int[size];
        }
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                data[i][j]=right.data[i][j];
            }
        }
    }
    matrix() {}
    matrix(int **x,int s){
        data=x;
        size=s;
    }
    double det(){
        return determinant(data,size);
    }

};
double f(matrix m,int *y,int c,int size){
    for(int i=0;i<size;i++){
        m.data[i][c]=y[i];
    }
    return determinant(m.data,size);
}
int main() {
    int n;
    cout<<"enter the number of linear equations to solve\n";
    cin>>n;
    int **x=new int*[n];
    for(int i=0;i<n;i++){
        x[i]=new int[n];
    }
    int *y=new int[n];
    cout<<"enter the coefficients as x0+...+xn=y\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>x[i][j];
        }
        cin>>y[i];
    }
    matrix m(x,n);
    double delta=m.det();
    double *deltax=new double[n];
    matrix temp;
    double *ans=new double[n];
    for(int i=0;i<n;i++){
        temp=m;
        deltax[i]=f(temp,y,i,n);
        ans[i] = deltax[i] / delta;
        cout<<"x"<<i<<" = "<<ans[i]<<'\n';
    }
return 0;
}
