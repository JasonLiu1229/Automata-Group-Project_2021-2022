#ifndef AUTOMATA_RE_H
#define AUTOMATA_RE_H

#include "ENFA.h"
#include <vector>

using namespace std;
class RE {
private:
    string regex;
    char eps;
public:

    // Constructor

    /**
     * @brief Construct a new RE object
     * 
     * @param regex The regex string
     * @param eps The character for the epsilon
     */
    RE(const string &regex, char eps);

    /**
     * @brief Construct a new RE object from a reference RE object
     * 
     * @param refRE The reference object
     */
    RE(RE* refRE);

    /**
     * @brief Construct a new RE object
     * @details The regex and epsilon characters are initialized as empty
     */
    RE();

    // Getters and setters

    /**
     * @brief Get the Regex string
     * 
     * @return const string& The regex string
     */
    const string &getRegex() const;

    /**
     * @brief Set the Regex string
     * 
     * @param regex The new regex string
     */
    void setRegex(const string &regex);

    /**
     * @brief Get the Eps character
     * 
     * @return char The epsilon character
     */
    char getEps() const;

    /**
     * @brief Set the Eps character
     * 
     * @param eps The new epsilon character
     */
    void setEps(char eps);

    set<char> getAlphabet() const;

    void setAlphabet(set<char> &newAlphabet);

    // Basic automatons

    /**
     * @brief Create an enfa for epsilon language {eps}
     * 
     * @param beginName Name of the begin state
     * @param endName Name of the end state
     * @return ENFA The epsilon enfa
     */
    ENFA* createEpsilon(string beginName , string endName);

    /**
     * @brief Create an enfa for the empty language {}
     * 
     * @param beginName Name of the begin state
     * @param endName Name of the end state
     * @return ENFA The empty enfa
     */
    ENFA* createEmpty(string beginName , string endName);

    /**
     * @brief Create an enfa for the language {a}
     * 
     * @param beginName Name of the begin state
     * @param endName Name of the end state
     * @param a The character
     * @return ENFA The enfa for the language {a}
     */
    ENFA* createSingleChar(string beginName , string endName , char a);

    // Induction automatons

    /**
     * @brief Create an enfa for the plus operation (R + S)
     * 
     * @param beginName Name of the begin state
     * @param endName Name of the end state
     * @param ref The vector of the enfa's to plus
     * @return ENFA The enfa for the operation R + S
     */
    ENFA* createPlus(vector<ENFA*> &ref , int &count);

    /**
     * @brief Create an enfa for the concatenation operation (R.S)
     * 
     * @param R The first enfa
     * @param S The second enfa
     * @return ENFA The enfa for the operation R.S
     */
    ENFA* createConcatenation(ENFA &R , ENFA &S);

    /**
     * @brief Create an enfa for the concatenation of a series of ENFA's
     * 
     * @param ref The vector of the enfa's
     * @return ENFA* A pointer to the concatenated ENFA
     */
    ENFA* createConcatenation(vector<ENFA*> ref);
    
    /**
     * @brief Create an enfa for the star operation (R*)
     * 
     * @param beginName Name of the begin state
     * @param endName Name of the end state
     * @param R The base enfa
     * @return ENFA The enfa for the operation R*
     */
    ENFA* createStar(string beginName , string endName , ENFA &R);

    // Convert function

    /**
     * @brief Splits the regex string into substrings
     * 
     * @param reg The REGEX
     * @return vector<string> A vector of substrings
     */
    vector<ENFA*> splitRegex(string &reg , int &count , vector<int>&index);

    /**
     * @brief Creates an ENFA from a regex
     * 
     * @param reg The RE string
     * @param count The current name count
     * @return ENFA* A pointer to the created ENFA
     */
    ENFA* toENFA(string &reg , int &count);

    /**
     * @brief Constructs an enfa from the regex
     * 
     * @return ENFA The enfa of the regex
     */
    ENFA toENFA();

    // Destructor
    virtual ~RE();
};


#endif //AUTOMATA_RE_H
