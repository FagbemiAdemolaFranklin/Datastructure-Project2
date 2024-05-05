#include <iostream>
#include <string>

#ifndef Game_h
#define Game_h

using namespace std;

class Game{
    bool game_state;
    char game_array[9]={'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    int nop=0, location_on_game_array=0, starter=1, array_size = (sizeof(game_array)/sizeof(char)) - 1, difficulty_number, difficulty_number_2; // nop means number of plays
    char human='O', computer='X', inputed_character='\0', human2='X', computer2='O', current_computer='\0';
    unsigned long stats, victories=0, defeats=0, ties=0, computer_victories=0, human_victories=0, human_victories_2=0,  computer_defeats=0, human_defeats=0, human_defeats_2=0 , computer_ties=0, human_ties=0, human_ties_2=0;
    unsigned long computer_victories_2=0, computer_defeats_2=0, computer_ties_2=0;
    string exit_confirmation, difficulty="Elementary",User, Human1, Human2, computer_difficulty_1,computer_difficulty_2;

    public:
        Game(){
            
        };
        Game(char );
        char checkTable();
        void showTable();
        void showTable2();
        void showTable3();
        void countTable();
        void countPlays();
        void playGame();
        void gameMenu();
        void clearArray();
        int checkRandomNumber();
        void playElementary();
        void playElementaryWinner();
        void playGreedy();
        void playGreedyWinner();
        void playMedium();
        void playMediumWinner();
        void playAdvanced();
        void playAdvancedWinner();
        void playHumanVsHuman();
        void playComputerVsComputer();
        void playComputerOne();
        void playComputerTwo();
        void execute_option(int);
        void execute_option_one(),execute_option_two();
        void execute_option_three(),execute_option_four();
        void execute_option_five(struct PlayerStats playerss[], int);
        void restart_game();
        Game startNewGame();
        int retrievePreviousGame(string user);
        int readAndWriteStats(string, string, string);
        int readAndWriteStats2(string, string, string);
        int loadStats(string, string, string);
        int loadStats2(string, string, string);
        void showStats();
        void showStats2();
        void showStats3();
        void resetStats();
        void writeStats(string);
        void checkAndComputeStats();
        void checkAndComputeStats2();
        void checkAndComputeStats3();
        void showMultipleTables(char [][9], int);
        void writeGameArrayToFile(const char*);
        void readAndPrintGameArrays(const string &, const string &, const string & );
        void removeUserFromFile(const string& , const string&, const string& );
        void saveArrays(string);
        void showArrays();
        int saveGame();
        int saveGame2();
        int showTopPlayers(string, string);
        void setComputer1();
        void setComputer2();
        void exit();
        

};

#endif

