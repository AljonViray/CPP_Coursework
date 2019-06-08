// Commands.hpp
//
// Code made by Aljon Viray, ID: 86285526
// ICS 45C Winter 2019
// Project #3: Maps and Legends

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "HashMap.hpp"


// Main Commands Function
void handleCommands(const std::string& input1, const std::string& input2, const std::string& input3, const std::string& garbage, bool& debug, bool& running, HashMap& hashMap);

// User-facing Commands Functions
void create(const std::string& username, const std::string& password, HashMap& hashMap);
void login(const std::string& username, const std::string& password, HashMap& hashMap);
void remove(const std::string& username, HashMap& hashMap);
void clear(HashMap& hashMap);

// Debug Commands Functions
void toggleDebug(const std::string& command, bool& debug);


#endif // COMMANDS_HPP