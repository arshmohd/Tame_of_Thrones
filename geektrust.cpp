#include "golden_crown.hpp"

int main(int argc, char *argv[])
{   
    // Check if correct number of command-line arguments were passed.
    if (argc != 2)
    {
        std::cerr << "Usage: geektrust <input_file>\n";
        
        return 1;
    }

    std::string inputFile = argv[1];        // Assign command-line given input-file.
    std::ifstream inFile (inputFile);       // Open the file.
    
    // Check if opening the file worked.
    if(!inFile)
    {
        std::cerr << "Unable to open specified input file.";
        
        return 2;
    }

    // Convert given input text file into a map.
    std::map<std::string, std::string> messages = file2map(inFile);

    // Start the Game of Crowns. Make an object and pass a map messages (from inpute file)
    Game ofCrowns(messages);
    std::vector<std::string> allies = ofCrowns.get_allies();    // Access class method to get the list of allies.

    // Check if object gained enough allies.
    if(ofCrowns.check_totalAllies())
    {
        std::cout << "SPACE " << allies << "\n";
    }

    else
    {
        std::cout << "NONE\n";
    }
    
    // Le fin.
    return 0;
}