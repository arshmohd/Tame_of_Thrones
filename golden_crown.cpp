#include "golden_crown.hpp"

/*
    Requires c++17: auto, extract
*/

// Access private totalAllies member.
int Game::get_totalAllies()
{
    return totalAllies;
}

// Access totalAllies and decide if enough allies were gained.
bool Game::check_totalAllies()
{
    if(totalAllies >= MINALLIES)
    {
        return true;
    }

    return false;
}

// Access vector of strings containing allies gained.
std::vector<std::string> Game::get_allies()
{
    return allies;
}

// Constructor to start this instance, decide alliances.
Game::Game(std::map<std::string, std::string> messages)
{
    // Decode the messages using the method.
    this->decoder(messages);

    std::string tmp;
    int emblemCtr = 0;              // Emblem character counter. Tracks no. of emblem characters in it message.

    // Iterate through the private constant southeros with kingdom names, passkeys and length of keys.
    for(auto i : southeros)
    {
        tmp = "";                   // Ensuring its reset.
        emblemCtr = 0;
        tmp = decrypted[i.first];   // Accessing decrypted messages after decoded messages.

        // Iterate character-wise through passkey string of current kingdom. 
        for(char c : i.second.first)
        {   
            // Binary search as the decrypted messages are sorted.
            if(!std::binary_search(tmp.begin(), tmp.end(), c))
            {
                break;              // Break out of current for loop instantly, save time as one character missing is enough to fail. 
            }

            else
            {
                removeC(tmp, c);    // Remove one instance of that character from the string.
                emblemCtr++;        // Increment for successful character.
            }
        }

        // Check if all the characters from the kingdom's passkey were found.
        if (emblemCtr == i.second.second)
        {
            allies.push_back(i.first);  // Add kingdom to list of allies.
            totalAllies++;              // Increment no. of Allies.
        } 
    }
}

// Destructor to reset ally counter, just making sure. And in case of future updates: Record keeping, resetting...
Game::~Game()
{
    totalAllies = 0;
}

// Novelty redundancy: To encode messages according to notes. Used For debugging.
void Game::encoder()
{
    for(auto i : southeros)
    {   
        for(char &c : decrypted[i.first])
        {
            c = (c - DECAP + i.second.second) % ALPH + DECAP;
        }
    }
}

// To decode messages according to notes.
void Game::decoder(std::map<std::string, std::string> encrypted)
{   
    // Clean up the keys of the input encrypted map. 
    mess_cleaner(encrypted);

    // Carry out decoding of given message and store in private decrypted.                                          
    std::string temp;

    // Refer constructor.
    for(auto i : southeros)
    {   
        temp = "";

        // Refer constructor.
        for(char c : encrypted[i.first])
        {   
            if(isalpha(c))                              // Only keeping alphabet characters.
            {
                c = toupper(c);                         // Capitalising character, ease of process.
                int tmp = 0;                            // Holds x of (x % 26), to ensure cyclic nature of alphabet shifting.
                tmp = (c - DECAP - i.second.second);    // De-ASCII-late the character then shift according to length of passkey. 
                c = modulo(tmp, ALPH) + DECAP;          // custom unsigned Modulo function to remove negative results, then re-ASCII-late.
                temp.push_back(c);                      // Push into temporary string, because strings can't remove specific characters willy-nilly.
                sort(temp.begin(), temp.end());         // Sorting everytime a new character is added. Ease of constructor's process. 
            }
        }

        encrypted[i.first] = temp;                      // Setting the message string to decoded, sorted string.
    }

    // Assigning the decrypted map to private member.
    decrypted = encrypted;
}

// Overload << to output a <string, string> map.
std::ostream& operator << (std::ostream& output, std::map<std::string, std::string> message)
{
    for(auto const &entry : message)
    {
        std::cout << entry.first << " :: " << entry.second
            << std::endl;
    }

    return output;
}

// Overload << to outpute a 1-D vector.
std::ostream& operator << (std::ostream& output, std::vector<std::string> vecs)
{
    for(auto const &entry : vecs)
    {
        std::cout << entry << " ";
    }

    return output;
}

// Function to clean up input map's key for processing.
void mess_cleaner(std::map<std::string, std::string> &mess)
{
    // Iterate through the map using iterator
    for(auto &i : mess) 
    {  
        // To capitalize/homogenize the input keys
        auto node = mess.extract(i.first);      // Extract the key into node, allowing manipulation.
        auto tmp = node.key();                  
        std::transform(tmp.begin(), tmp.end(),  // Transform the key string to all caps.
            tmp.begin(), ::toupper);
        node.key() = tmp;                       // Assigning all caps string to the node as key.
        mess.insert(std::move(node));           // Insert the node back to the referenced map.
    }
}

// Removes the given character, from given string, ONCE.
void removeC(std::string &legacy, char c)
{
    bool removed = false;
    std::string temp = "";

    if(legacy.empty())
    {
        return;
    }

    for(char old : legacy)
    {
        if((old != c) || removed)
        {
            temp.push_back(old);
        }

        else
        {
            removed = true;
        }
    }

    legacy = temp;
}

// Convert given input text file into a map. Used in the main function.
std::map<std::string, std::string> file2map(std::ifstream& inFile)
{
    std::map<std::string, std::string> messages;
    std::string key;
    std::string value;
    std::string reader;

    while(std::getline (inFile, reader))   // Read through input file.
    {   
        // Turn the file into a map, Emblem: <encrypted message>
        std::istringstream mappingIt(reader);
        mappingIt >> key >> value;
        messages[key] = value;
    }

    return messages;
}

// For an unsigned modulo function.
unsigned modulo(int value, unsigned m)
{
    int mod = value % (int)m;

    if (mod < 0)    // If resultant remainder is negative, add the divisor.
    {
        mod += m;
    }

    return mod;
}