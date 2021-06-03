#include <iostream>
#include <fstream>

using namespace std;

const int N = 4;

void print_realPrice_dif(double values[][N+1])
{
    double realPrices[N];
    for(int i = 0; i < N; i++){
        realPrices[i] = values[i][0]*0.129 + values[i][1]*1.461 + values[i][2]*85.07 + values[i][3]*0.132;
        cout<<values[i][N] - realPrices[i]<<" ";
    }
    cout << endl;
}

double *simpleGaus(double values[][N+1])
{
    static double fake_prices[N] = {0};
    double copy_of_values[N][N+1] = {0};
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N+1; j++)
        {
            copy_of_values[i][j] = values[i][j];
        }
    }

    for(int i = 0; i < N-1; i++)
    {
        if(copy_of_values[i][i] == 0)
        {
            for(int j = i; j < N; j++)
            {
                if(copy_of_values[j][i] != 0)
                {
                    for(int k = 0; k <= N; k++)
                    {
                        double swap = copy_of_values[j][k];
                        copy_of_values[j][k] = copy_of_values[i][k];
                        copy_of_values[i][k] = swap;
                    }
                }
            }
        }
        for(int j = i + 1; j < N; j++)
        {
            double koef = -(copy_of_values[j][i]/copy_of_values[i][i]);
            for(int k = i; k < N + 1; k++)
            {
                copy_of_values[j][k] += koef * copy_of_values[i][k];
            }
        }
    }
    
    for (int i = N-1; i >= 0; i--)
    {
        fake_prices[i] = copy_of_values[i][N]/copy_of_values[i][i];
        for (int j = N-1; j > i; j--)
        {
            fake_prices[i] -= (copy_of_values[i][j] * fake_prices[j])/copy_of_values[i][i];
        }
    }

    return fake_prices;
}

void print_OurToTheir_dif(double values[][N+1])
{
    double *fake_prices = simpleGaus(values);
    /*for(int i = 0; i < N; i++)
    {
        cout << fake_prices[i] << endl;
    }*/

    double real_prices[N] = {0.129, 1.461, 85.07, 0.132};

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            double dif = values[i][j]*fake_prices[j] - values[i][j]*real_prices[j];
            dif /= values[i][j]*real_prices[j] + dif;
            dif *= values[i][j];
            cout << dif << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    ifstream input_file(argv[1]);
    double values_fromfile[N][N+1];

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            input_file >> values_fromfile[i][j];
        }
    }
    for(int i = 0; i < N; i++)
    {
        input_file >> values_fromfile[i][N];
    }
    
    input_file.close();

    /*for(int i = 0; i < N; i++){
        for(int j = 0; j < N + 1; j++){
            cout << values_fromfile[i][j] << " ";
        }
        cout << endl;
    }*/

    print_realPrice_dif(values_fromfile);
    
    print_OurToTheir_dif(values_fromfile);

    return 0;
}
