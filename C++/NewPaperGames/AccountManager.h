//
// Created by Arron on 21/01/2020.
//

#ifndef NEWPAPERGAMES_ACCOUNTMANAGER_H
#define NEWPAPERGAMES_ACCOUNTMANAGER_H

bool createAccount(std::string username);
void createFile();
void editScore(int scoreType, std::string currentUser);
void displayAccount(std::string user);
bool accountExists(std::string userInput);

#endif //NEWPAPERGAMES_ACCOUNTMANAGER_H
