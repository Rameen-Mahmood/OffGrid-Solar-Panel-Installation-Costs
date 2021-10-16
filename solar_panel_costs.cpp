//
//  main.cpp
//  Assignment #3
//
//  Created by Rameen Mahmood on 11/11/2019.
//  Copyright © 2019 ENGR-AD101. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include<cmath>
using namespace std;
#define column 24
#define row 12
double S[] = {4.89, 5.52, 6.21, 6.88, 7.20, 6.76, 6.33, 6.39, 6.35, 6.04, 5.13, 4.68};
double solar_cell_effeciency = 0.18;
double inverter_efficiency = 0.9;
void inputValues(double &spcost, double &dreq, double &picost, double &bcost);
double fillInInsolation(double arr[][column],int r);
double dailyInsolation(double *ptr,int s, int month);
double searchMin(double arr[], int size);
double searchMax(double arr[][column], int col, int rows);
int main()
{
    double ratio=0, cost=0,spcost=0, dreq=0, picost=0, bcost=0, insolDayMin=0, insolHourMax=0, area=0; //declaring and initializing variables
    int num_power_invterters=0, num_batteries=0;
    inputValues(spcost, dreq, picost, bcost); // calling the function to update variables with user entered values
    double insolation_matrix[row][column]; //declaring 2d array
    for (int j=0;j<row;j++)
    {
        for(int i=0;i<column;i++)
        {
            insolation_matrix[j][i]=0; // initliazing each element in 2d array to 0
        }
    }
    insolDayMin = fillInInsolation(insolation_matrix, row); //updating each value in the 2d array

    insolHourMax = searchMax(insolation_matrix,column, row); //getting the maximum insolation value
    area = (dreq)/(solar_cell_effeciency * insolDayMin* inverter_efficiency); //calculating the area
    ratio = solar_cell_effeciency/inverter_efficiency; // calculating the ratio
    num_power_invterters= ceil(((insolHourMax*area)/5) * ratio); //calculating the number of power inverters
    num_batteries=ceil(dreq/4.8); //calculating the number of batteries.
    cost = (area * spcost) + (num_power_invterters * picost) + (num_batteries*bcost); //calculating the total cost
    cout<<"The minimum insolation value is: "<<insolDayMin<<" kWh/m2"<<endl;
    cout<<"The maximum insolation value is: "<<insolHourMax<<" kWh/m2"<<endl;
    cout<<"The area is: "<<area<<" m2" <<endl;
    cout<<"The number of power inverters are: "<<num_power_invterters<<endl;
    cout<<"The number of batteries are: "<<num_batteries<<endl;
    cout<<"The total cost is: "<<cost<<endl;
    return 0;
}
void inputValues(double &spcost, double &dreq, double &picost, double &bcost) //variables are passed by reference to update them accordingly
{

        cout<<"Please enter the daily energy requirements: ";
        cin>>dreq;
        cout<<"Please enter the solar panel cost: ";
        cin>>spcost;
        cout<<"Please enter the power inverters cost: ";
        cin>>picost;
        cout<<"Please enter the battery cost: ";
        cin>>bcost;
        while (dreq<0)//validating each value (dreq,spcost,bcost,picost) to check if user inputs a negative value, if user does input a negative value, it will ask for the correct value until the user inputs a positive value
        {
            cout<<"Invalid daily requirements, enter again"<<endl;
            cin>>dreq;
        }
        while(spcost<0)
        {
            cout<<"Invalid solar panel cost, enter again"<<endl;
            cin>>spcost;
        }
        while (picost<0)
        {
            cout<<"Invalid power inverter cost, enter again"<<endl;
            cin>>picost;
        }
        while(bcost<0)
        {
            cout<<"Invalid battery cost, enter again"<<endl;
            cin>>bcost;
        }
}
double fillInInsolation(double a[][column], int size)
{
    double min=0;
    int month =0;
    double daily_insolation[row];
    for (int j=0;j<row;j++)
    {
        daily_insolation[j]=0; //initalizing each element in array daily_insolation to zero
    }
    for (int i =0; i < row; i++) //each row will be accessed through index i
    {
        double *ptr = &a[i][0]; //initializing the pointer as address of each row in the 2d array.
        daily_insolation[i] = dailyInsolation(ptr, row, month); //storing each month's daily insolation value in the daily_insolation array
        month++; //repeating for each month
    }

    min = searchMin(daily_insolation, row); //to find the minimum of all the 12 months.
    return min;
}
double dailyInsolation(double *ptr, int elements, int  month)
{
    double daily_insolation[row];
    for (int j=0;j<row;j++)
     {
         daily_insolation[j]=0; //initializing the elements of daily_insolation to 0
     }
    for (int i=0;i<elements;i++) //to fill each row of the matrix
    {
        ptr[6+i] = 2*S[month]*cos(0.2618*((6+i)-12)); //filling the matrix using the formula, from hour 6 to 17.
        daily_insolation[month] += ptr[6+i]; //adding each rows values and storing into the daily_insolation array for each month
    }
   return daily_insolation[month]; //returning the array daily_insolation value for each particular month
}
double searchMin(double arr[], int size) //calculating the minimum, comparing the values of each month
{
    double minimum = 100000;

    for (int j=0;j<size;j++)
    {
        if (arr[j]<minimum)
        {
            minimum=arr[j];
        }
    }
    return minimum;
}
double searchMax(double arr[][column], int col, int rows) //calculating the maximum daily insolation value
{
    double max = -10000000;
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<col;j++)
        {
            if (arr[i][j]>max)
            {
                max = arr[i][j];
            }
        }
    }
    return max;
}
