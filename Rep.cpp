#include <bits/stdc++.h>

using namespace std;
#define PI 3.14159265358979323846


complex<double> computeWnk(int n, int k)
{
    return cos((2*PI*k/n)) - sin((2*PI*k/n))*1i;

}
void computeFFT(complex<double> *x, int N,int xSize)
{
    if (N<=2)
    {
        complex<double> temp=x[0];
        x[0]+=x[1];
        x[1]=temp-x[1];

    }
    else
    {
        complex<double> xEven[N/2];
        complex<double> xOdd[N/2];
        for(int i = 0 ; i< N/2; i++)
        {
            xEven[i]=x[2*i];
            xOdd[i]=x[(2*i)+1];
        }

        computeFFT(xEven,N/2,xSize);
        computeFFT(xOdd,N/2,xSize);
        complex<double> temp[N];

        for(int i = 0 ; i< N/2; i++)
        {
            temp[i]=xEven[i];
            temp[i+N/2]=xOdd[i]*computeWnk(xSize,i*(pow(2,log2(xSize)-log2(N))));


        }
        for (int i = 0; i< N; i++)
        {

            if(i < N/2)
            {
                x[i]=temp[i]+temp[i+N/2];
            }
            else
            {
                x[i]=temp[i-N/2]-temp[i];
            }
        }

    }


}

int main()
{
    cout<<"Enter The size of input: ";
    short N;
    while(true)
    {
        cin>>N;
        if (int(log2(N)) != log2(N) || N < 2)
        {
            cout<<"N must be a power of 2 re-enter N: \n";
        }
        else
        {
            cout<<"Enter your inputs: \n";
            complex<double> X[N];
            for ( int i=0 ; i<N; i++)
            {
                cin>>X[i].real()>>X[i].imag();

            }
            computeFFT(X,N,N);
            cout<<"(Outputs, Magnitude, Phase)\n";
            for ( int i=0 ; i<N; i++)
            {
                X[i].real() = truncf(X[i].real() * 100) / 100;
                X[i].imag() = truncf(X[i].imag() * 100) / 100;
                cout<<X[i]<<"\t\t"<<abs(X[i]) <<"\t\t"<<arg(X[i])<<endl;

            }

            break;
        }

    }
    return 0;
}
