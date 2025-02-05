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
        {   //Get first energy level.
            n_i = get_positive_integer("Please enter the initial energy level of the electron: ");
            //n_i must be 2 or more.
            if(n_i == 1)
            {
                throw std::invalid_argument("The initial energy level must be greater than or equal to 2.");
            }
            //Get second energy level
            n_j = get_positive_integer("Please enter the final energy level of the electron: ");
            // Check that energy levels are valid.
            if(n_i > n_j)
            {
                valid_input = true;
            }
            else
            {
                throw std::invalid_argument("The initial energy level must be greater than the final energy level.");
            }
        }
        //Catch any exceptions.
        catch(const std::invalid_argument &e)
        {
            std::cerr<<e.what()<<'\n';
        }
        
    }
    //Pack n_i and n_j into a tuple and return.
    std::tuple<int,int> energy_levels = std::make_tuple(n_i, n_j);
    return energy_levels;
}

std::string get_energy_unit()
{   //
    std::string unit;
    bool valid_input{false};

    while(!valid_input)
    {   //Gets the user to input 
        std::cout<<"Would you like the energy to be displayed in joules or electron-volts? Type 'J' or 'eV': ";
        std::cin >> unit;
        //Cover all cases, upper and lower case.
        if(unit == "J" || unit == "j" || unit == "eV" || unit == "ev" || unit == "Ev" || unit == "EV")
        {
            valid_input = true;
        }
        else
        {
            std::cout<<"Please enter a valid response."<<std::endl;
        }
    }
    //Redefine unit in such that get_transition_energy can use it.
    if(unit == "j" || unit == "J")
    {
        unit = "J";
    }
    else
    {
        unit = "eV";
    }

    return unit;
}

int main()
{   
    //Gives the user some information about the program and electron transitions.
    std::cout<<"This programs calculates the energy of an emitted photon due to an electron transition between energy levels in an atom of atomic number Z."<<std::endl;
    std::cout<<"The electron's initial quantum number (n) must be greater than its final quantum number. Quantum numbers n must be positive integers, hence the minimum values for the inital and final quantum numbers are 2 and 1 respectively."<<std::endl;

    int n_i, n_j;
    //Get the energy levels.
    std::tuple<int,int> energy_levels = get_energy_levels();
    //Unpack the tuple_energy_levels.
    std::tie(n_i, n_j) = energy_levels;
    //Get the atomic numnber.
    int Z{get_positive_integer("Please enter the atomic number of the atom: ")}; //Get atomic number.
    //Get the unit.
    std::string unit = get_energy_unit();
    //Calculate the transition energy.
    double transition_energy = get_transition_energy(n_i, n_j, Z, unit);
    //Set the precision to 3 significant figures since the equation contains 13.6 which is to 3 significant figures.
    std::cout << std::scientific << std::setprecision(2);
    //Display the transition energy.
    std::cout<<"The transition energy is: "<<transition_energy<<" "<<unit<<" to 3 significant figures"<<std::endl;

    return 0;
}