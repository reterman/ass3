#include<bits/stdc++.h>
using namespace std;

double CalculateV(double t, double v0, double k0, double alpha1, double beta1, double alpha2, double beta2)
{
    double result = v0*cos(sqrt(alpha1*alpha2)*t) - k0*((sqrt(alpha2)*beta1)/(beta2*sqrt(alpha1)))*sin(sqrt(alpha1*alpha2)*t) + alpha2/beta2;
    return result;
}

double CalculateK(double t, double v0, double k0, double alpha1, double beta1, double alpha2, double beta2)
{
    double result = v0*((sqrt(alpha1)*beta2)/(beta1*sqrt(alpha2)))*sin(sqrt(alpha1*alpha2)*t) + k0*cos(sqrt(alpha1*alpha2)*t) + alpha1/beta1;
    return result;
}

#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"

void creatCoordFile(double T, double detTime, double v0, double k0, double alpha1, double beta1, double alpha2, double beta2)
{
 ofstream coord1, coord2, coord3;
 coord1.open("C:\\gnuplot\\coord1.dat");
 coord2.open("C:\\gnuplot\\coord2.dat");
 coord3.open("C:\\gnuplot\\coord3.dat");

    double runTime = 0;
     while (runTime <= T)
    {
        double V = CalculateV(runTime, v0, k0, alpha1, beta1, alpha2, beta2);
        double K = CalculateK(runTime, v0, k0, alpha1, beta1, alpha2, beta2);
        coord1<<runTime <<" "<<V<<endl;
        coord2<<runTime <<" "<<K<<endl;
        coord3<<V <<" "<<K<<endl;
    runTime+=detTime;
    }
 coord1.close();
 coord2.close();
 coord3.close();
}



void creatGraphs(double T, double detTime, double v0, double k0, double alpha1, double beta1, double alpha2, double beta2 )
{
 creatCoordFile(T, detTime, v0, k0, alpha1, beta1, alpha2, beta2);

 FILE* pipe = _popen(GNUPLOT_NAME, "w");
 if (pipe!=NULL)
 {
    fprintf(pipe, "%s\n" ,"set terminal qt 0");
    fprintf(pipe, "%s\n", "plot 'C:\\gnuplot\\coord1.dat' title 'victims' with lines, 'C:\\gnuplot\\coord2.dat' title 'killers' with lines");
    fprintf(pipe, "%s\n" ,"set terminal qt 1");
    fprintf(pipe, "%s\n", "plot 'C:\\gnuplot\\coord3.dat' title 'relation' with lines");
    fflush(pipe);
    _pclose(pipe);
 } else cout << "ERROR!"<<endl;
}


int main() {
    double v0, k0, alpha1, beta1, alpha2, beta2;
    double T, N;
    cin>>v0>>k0>>alpha1>>beta1>>alpha2>>beta2>>T>>N;

    ostringstream V, K;
    v0=v0-alpha2/beta2;
    k0=k0-alpha1/beta1;
    
    double runTime = 0;
    double detTime = T/N;
    cout << "t:"<<endl;
    while (runTime <= T)
    {
    cout <<fixed<<setprecision(2)<<runTime<<" ";
    V <<fixed<<setprecision(2)<<CalculateV(runTime, v0, k0, alpha1, beta1, alpha2, beta2)<<" ";
    K <<fixed<<setprecision(2)<<CalculateK(runTime, v0, k0, alpha1, beta1, alpha2, beta2)<<" ";
    runTime+=detTime;
    }
    cout << endl;
    cout << "v:"<<endl;
    cout << V.str();
    cout << endl;
    cout << "k:"<<endl;
    cout << K.str();

    creatGraphs(T, detTime, v0, k0, alpha1, beta1, alpha2, beta2);

    


    return 0;
}
