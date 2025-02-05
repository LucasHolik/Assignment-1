//Assignment 1/assignment_1.cpp
//This program calculates the energy of a photon emitted during an electron transition in an atom of atomic number Z, according to the Bohr model.
//Lucas Holik 11010219
//Created on 28/01/2025

//Include the necessary libraries.
#include <iostream>
#include <cmath>
#include <string>
#include <tuple>
#include <stdexcept>
#include <iomanip>

//Define the conversion factor from eV to J.
const double eV_to_J{1.602176634e-19};

double get_transition_energy(int n_i, int n_j, int Z, std::string unit)
{   //Calculates the photon energy for an electron transition due to the Bohr model.
    //n_i = initial electron quantum number n.
    //n_f = final electron quantum number n.
    //Z = atomic number of atom.
    //unit = "eV" or "J", specifies the units in which to return the transition energy.

    //Calculate transition energy in eV.
    double transition_energy{13.6 * pow(Z, 2) * (1/pow(n_j, 2) - 1/pow(n_i, 2))};
    //Convert from eV to J if specified.
    if (unit == "J")
    {
        transition_energy *= eV_to_J;
    }

    return transition_energy;
}


void check_cin()
{   //Checks if std::cin has failed (string / char entered) or if there are characters in the buffer (float entered).
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cin.clear(); //Clear the error.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore the input.
        throw std::invalid_argument("Invalid input, please enter what is asked."); //Throw an exception.
    }
}

int get_positive_integer(std::string message)
{   //Repeatedly tells the user 'message' until a positive integer is entered.
    int number;
    bool valid_input{false}; //Assume invalid input.
    //Loop until a valid input is entered.
    while(!valid_input)
    {
        try
        {
            std::cout<<message; //Display 'message'.
            std::cin>>number; //Get user input.
            check_cin(); //Check for valid numerical input.

            if(number > 0)
            {
                valid_input = true;
            }
            else
            {
                throw std::invalid_argument("Energy levels are positive integers.");
            }
        }
        catch(const std::invalid_argument &e) //Catch any exceptions thrown in get_positive_integer or check_cin.
        {   //Print out error message.
            std::cerr<<e.what()<<'\n';
        }
    }
    return number;
}

std::tuple<int,int> get_energy_levels()
{
    int n_i, n_j;
    bool valid_input{false}; //Assume invalid input.
    //Loop until a valid input is entered.
    while(!valid_input)
    {
        try
        {
            n_i = get_positive_integer("Please enter the initial energy level of the electron: ");

            if(n_i == 1)
            {
                throw std::invalid_argument("The initial energy level must be greater than or equal to 2.");
            }

            n_j = get_positive_integer("Please enter the final energy level of the electron: ");

            if(n_i > n_j)
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
            std::cerr<<e.what()<<'\n';
        }
        
    }
    std::tuple<int,int> energy_levels = std::make_tuple(n_i, n_j);
    return energy_levels;
}

std::string get_energy_unit()
{   
    std::string unit;
    bool valid_input{false};

    while(!valid_input)
    {
        std::cout<<"Would you like the energy to be displayed in joules or electron-volts? Type 'J' or 'eV': ";
        std::cin >> unit;

        if(unit == "J" || unit == "eV")
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
    std::cout<<"This programs calculates the energy of an emitted photon due to an electron transition between energy levels in an atom of atomic number Z."<<std::endl;
    std::cout<<"The electron's initial quantum number must be greater than its final quantum number. Quantum numbers must be positive integers, hence the minimum values for the inital and final quantum numbers are 2 and 1 respectively."<<std::endl;

    int n_i, n_j;

    std::tuple<int,int> energy_levels = get_energy_levels();
    std::tie(n_i, n_j) = energy_levels;

    std::string unit = get_energy_unit();

    double transition_energy = get_transition_energy(n_i, n_j, 1, unit);

    std::cout << std::scientific << std::setprecision(2);
    std::cout<<"The transition energy is: "<<transition_energy<<" "<<unit<<" to 3 significant figures"<<std::endl;

    return 0;
}