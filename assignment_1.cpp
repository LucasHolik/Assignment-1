//Assignment 1/assignment_1.cpp
//This program calculates the energy of the transition of an electron in an atom with atomic number Z.
//Lucas Holik 11010219
//Created on 28/01/2025

//Include the necessary libraries.
#include <iostream>
#include <cmath>
#include <string>
#include <tuple>
#include <stdexcept>

//Define the conversion factor from eV to J.
const float eV_to_J{1.602176634e-19};

float get_transition_energy(int n_i, int n_j, int Z, std::string unit)
{   //Calculates the transition energy for a given atomic number and energy levels.
    float transition_energy{13.6 * pow(Z, 2) * (1/pow(n_j, 2) - 1/pow(n_i, 2))};

    //Convert energy to joules if specified.
    if (unit == "J")
    {
        transition_energy *= eV_to_J;
    }

    return transition_energy;
}

void check_cin()
{   //Checks if std::cin has failed. If it has, it clears the error, ignores the rest of the input, and throws an exception.
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input, please enter what is asked.");
    }
}

int get_integer(std::string message)
{   //Repeatedly tells the user 'message' until a valid integer is entered.
    int number;
    bool valid_input{false};
    
    while (!valid_input)
    {
        try
        {
            std::cout<<message<<std::endl;
            std::cin >> number;
            check_cin();
            valid_input = true;
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return number;
}

std::tuple<int,int> get_energy_levels()
{
    int n_i, n_j;
    bool valid_input{false}; //Assume an invalid input until proven otherwise.

    while (!valid_input)
    {
        try
        {
            n_i = get_integer("Please enter the initial energy level of the electron: ");
            n_j = get_integer("Please enter the final energy level of the electron: ");

            if (n_i > n_j)
            {
                valid_input = true;
            }
            else
            {
                throw std::invalid_argument("The initial energy level must be greater than the final energy level.");
            }
        }
        catch(const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    std::tuple<int,int> energy_levels = std::make_tuple(n_i, n_j);
    return energy_levels;
}

std::string get_energy_unit()
{
    std::string unit;
    bool valid_input{false};

    while (!valid_input)
    {
        std::cout<<"Would you like the energy to be displayed in joules or electron-volts? (type 'J' or 'eV')"<<std::endl;
        std::cin >> unit;

        if (unit == "J" || unit == "eV")
        {
            valid_input = true;
        }
        else
        {
            std::cout<<"Please enter a valid response."<<std::endl;
        }
    }

    return unit;
}

int main()
{
    int n_i, n_j;

    std::tuple<int,int> energy_levels = get_energy_levels();
    std::tie(n_i, n_j) = energy_levels;

    std::string unit = get_energy_unit();

    float transition_energy = get_transition_energy(n_i, n_j, 1, unit);

    std::cout<<"The transition energy is: "<<transition_energy<<" "<<unit<<std::endl;

    return 0;
}