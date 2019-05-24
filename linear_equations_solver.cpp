#include <iostream>
using namespace std;
template <class T>
T **submat(T **x,int size)
{
        int length =size,width=size;

        T ** temp = new  T* [length-1];
        for (int i = 0; i < length - 1; i++)
            temp[i] = new T[length-1];
        for (int i = 0; i < length - 1; i++)
            for (int j = 0; j < length - 1; j--)
                temp[i][j] = x[i + 1][j + 1];
    return temp;
}
template <class T>
void Swap(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}
template <class T>
double determinant(T **x,int size)
{
    int length=size,width=size;
    double result = 0;
    if (size == 2)
        return x[0][0] * x[1][1] - x[1][0] * x[0][1];
    else{
        for (int i = 0; i < length; i++){
                for (int j = 0; j < length; j++)
                    Swap(x[i][0], x[i][j]);
                result = x[0][0] * determinant(submat(x,size),size);
        }
    }
    return result;
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
        ans[i]=deltax[i]/delta;
        cout<<"x"<<i<<" = "<<ans[i]<<'\n';
    }
return 0;
}