//Assignment 1/assignment_1.cpp
//This program calculates the energy of the transition of an electron in an atom with atomic number Z.
//Lucas Holik 11010219
//Created on 27/01/2025

#include <iostream>
#include <cmath>
#include <string>
#include <tuple>
#include <stdexcept>

//Want to find the electron transition energy for the outer electron in an atom with atomic number Z.

void check_cin()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input. Please enter a valid integer.");
    }
}

//Create a function returning the energy in eV.
float transition_energy(int n_i, int n_j, int Z)
{
    float transitionEnergy{13.6 * pow(Z, 2) * (1/pow(n_j, 2) - 1/pow(n_i, 2))};
    return transitionEnergy;
}
//Transition is only positive if the initial energy level n_i > the final energy level n_j.
bool valid_energy_levels(int n_i, int n_j)
{
    if (n_i > n_j)
        return true;
    else 
        return false;
}

std::tuple<int,int,int,std::string> get_valid_inputs()
{   //This function gets valid inputs for energy level numbers and atomic number.
    //Define variables.
    int n_i, n_j, Z;
    bool valid_input{false};
    
    while (!valid_input)
    {
        try
        {
            /* code */
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout<<"Please enter the initial energy level of the electron: ";
        std::cin >> n_i;

        check_cin();

        std::cout << "Please enter the final energy level of the electron: ";
        std::cin >> n_j;
        
        check_cin();

        valid_input = valid_energy_levels(n_i, n_j);
        
        if (valid_input == true)
            std::cout<<"The initial energy level must be greater than the final energy level."<<std::endl;
    }
    valid_input = false;
    
    while (!valid_input)
    {
        std::cout << "Please enter the atomic number of the atom: ";
        std::cin >> Z;
        if (Z > 0)
            valid_input = true;
        else
            std::cout<<"The atomic number must be an integer greater than 0.";
    }

    valid_input = false;
    std::string response;
    while(!valid_input)
    {
        std::cout<<"Would you like the result in electron-volts (type 'eV') or in joules (type 'J')?";
        std::cin>>response;
        if (response == "eV" || response == "J")
            valid_input = true;
        else
            std::cout<<"Please enter a valid response.";
    }
        
}

int main() 
{
    std::string response;
    int n_i, n_j, Z;

    std::cout<<"This programs calculates the energy of the transition of an electron in an atom with atomic number Z."<<std::endl;
    
    float energy = transition_energy(n_i, n_j, Z);

    std::cout << "The energy of the transition is: " << energy << " eV" << std::endl;

    std::cout<<"Would you like to calculate another transition energy? (y/n): ";
    std::cin>>response;

    if(response == "y") 
        main();
}