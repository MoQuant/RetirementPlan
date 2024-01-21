#include <stdio.h>
#include <math.h>

void Print(double x)
{
    printf("%f\n", x);
}


double Time(double fv, double r, double x)
{
    double A = (fv*r)/x+1;
    double B = 1 + r;
    return log(A)/log(B);
}

double PV(double x, double r, double t)
{
    return (x/r)*(1 - pow(1 + r, -t));
}

double dPV(double x, double r, double t)
{
    double A = (x*t)/(r*pow(1 + r, t + 1));
    double B = (x/pow(r, 2))*(1 - pow(1 + r, -t));
    return A - B;
}

double Rate(double pv, double x, double t)
{
    double r0 = 0.1, r1 = 0.99;
    int go = 0;
    double error = 0.0001;
    while(go < 1){
        r1 = r0 - (PV(x, r0, t) - pv)/dPV(x, r0, t);
        if(fabs(r1 - r0) < error){
            break;
        }
        r0 = r1;
    }
    return r1;
}

int main()
{
    double deposit = 1000;
    double goal = 300000;
    double interest = 0.07;

    double withdraw = 5000;
    double time_window = 7;

    double periods = 12;
    double rate = interest / periods;
    double time =  time_window * periods;

    double CT = Time(goal, rate, deposit);

    printf("It will take you %f years to have %f\n", CT/periods, goal);

    double R = Rate(goal, withdraw, time);
    R = R * periods;

    printf("You will need to earn an interest rate of %f yearly to withdraw %f for %f years\n", R, withdraw, time_window);

    return 0;
}