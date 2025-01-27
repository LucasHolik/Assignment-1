//Assignment 1/assignment_1.cpp


#include <iostream>
#include <cmath>

//Want to find the electron transition energy for the outer electron in an atom with atomic number Z.

//Create a function returning the energy in eV.
float transition_energy(int n1, int n2, int Z) {
    float energy{13.6 * pow(Z, 2) * (1/pow(n1, 2) - 1/pow(n2, 2))};
    return energy;
}



int main() 
{
std::cout<<"This programs calculates the energy of the transition of an electron in an atom with atomic number Z." << std::endl;
int n1, n2, Z;
std::cout<<"Please enter the initial energy level of the electron: ";
std::cin >> n1;
std::cout << "Please enter the final energy level of the electron: ";
std::cin >> n2;
std::cout << "Please enter the atomic number of the atom: ";
std::cin >> Z;

float energy = transition_energy(n1, n2, Z);

std::cout << "The energy of the transition is: " << energy << " eV" << std::endl;

std::cout<<"Would you like to calculate another transition energy? (y/n): ";
char response;
std::cin>>response;

if(response == 'y') 
    main();
}