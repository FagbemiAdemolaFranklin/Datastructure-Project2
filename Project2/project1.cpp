#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;


int chosen_option;
char retrieve_decision;
int game_cheat_array_random_number, get_current_player=0;

struct PlayerStats {
    string name;
    int victories;
    int defeats;
    int ties;
};
PlayerStats players[50];

class Game{
    bool game_state;
    char game_array[9]={'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    int nop=0, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    char human='O', computer='X', inputed_character='\0';
    unsigned long stats, victories=0, defeats=0, ties=0, computer_victories=0, human_victories=0, computer_defeats=0, human_defeats=0, computer_ties=0, human_ties=0;
    string exit_confirmation, difficulty="Elementary",User;

    public:
        Game(){
            
        };
        Game(char );
        char checkTable();
        void showTable();
        void countTable();
        void countPlays();
        void playGame();
        void gameMenu();
        void clearArray();
        int checkRandomNumber();
        void playElementary();
        void playGreedy();
        void playGreedyWinner();
        void playMedium();
        void playMediumWinner();
        void execute_option(int);
        void execute_option_one(),execute_option_two();
        void execute_option_three(),execute_option_four();
        void execute_option_five(struct PlayerStats playerss[], int);
        void restart_game();
        Game startNewGame();
        int retrievePreviousGame(string user);
        int readAndWriteStats(string, string, string);
        int loadStats(string, string, string);
        void showStats();
        void resetStats();
        void writeStats(string);
        void checkAndComputeStats();
        void showMultipleTables(char [][9], int);
        void writeGameArrayToFile(const char*);
        void readAndPrintGameArrays(const string& );
        void removeUserFromFile(const string& , const string&, const string& );
        void saveArrays(string);
        void showArrays();
        int saveGame();
        int showTopPlayers(string, string);
        void exit();
        

};


void Game::execute_option(int a){ // a is just an argument for the function
    switch (a)
    {
    case 1:
        execute_option_one();
        break;
    case 2:
        execute_option_two();
        break;
    case 3:
        execute_option_three();
        break;
    case 4:
        execute_option_four();
        break;
    case 5:
        showTopPlayers("temporary_stats.txt", difficulty);
        break;
    case 6:
        exit();
        break;
    default:
        cout << "Choose a valid option." <<endl;
        gameMenu();
        break;
    }
}

int Game::showTopPlayers(string text3_param, string diff3){
    ifstream showStatsFile(text3_param);
    string current_line;
    if (!showStatsFile.is_open())
    {
        cout << "File not found" <<endl;
        return -1;
    }

    while(getline(showStatsFile,current_line)){

        string line_object = "", line_object_2 = "";
        // Check if the line contains "User:", "Difficulty:", and "Victories:" substrings
        size_t user_pos = current_line.find("User: ");
        size_t diff_pos = current_line.find("Difficulty: ");
        size_t vict_pos = current_line.find("Victories: ");

        if (user_pos != string::npos && diff_pos != string::npos && vict_pos != string::npos) {
            // Extract user, difficulty, and victories substrings
            line_object = current_line.substr(user_pos + 6, diff_pos - user_pos - 7);
            line_object_2 = current_line.substr(diff_pos + 12, vict_pos - diff_pos - 13);
        }
        if(line_object_2 == diff3){
            cout<< current_line.find("User: computer&");
            cout<< "foundcomp"<<endl;
            players[get_current_player] = {line_object, stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                            stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                            stoi(current_line.substr(current_line.find("Ties: ") +6))
                                        };
            
            get_current_player++;
        }            
    }
    showStatsFile.close();
    execute_option_five(players,10);
    return 0;
}


void Game::showStats(){
    cout <<right << "Difficulty: " <<difficulty<<endl;
    cout <<right << "Human_Victories: " <<human_victories<<endl;
    cout <<right << "Human_Defeats: " <<human_defeats<<endl;
    cout <<right << "Human_Ties: " <<human_ties<<endl;
    cout <<right << "Computer_Victories: " <<computer_victories<<endl;
    cout <<right << "Computer_Defeats: " <<computer_defeats<<endl;
    cout <<right << "Computer_Ties: " <<computer_ties<<endl;
}



int Game::loadStats(string text2_param, string user2, string diff2){  
    fstream retrieveFile(text2_param);
    string current_line = "";

    if (!retrieveFile.is_open()) {
        cout << "File not found" << endl;
        return -1;
    }

    while (getline(retrieveFile, current_line)) {
        string line_object = "", line_object_2 = "";
        // Check if the line contains "User:" and "Difficulty:" substrings
        size_t user_pos = current_line.find("User: ");
        size_t diff_pos = current_line.find("Difficulty: ");
        size_t vict_pos = current_line.find("Victories: ");

        if (user_pos != string::npos && diff_pos != string::npos) {
            // Extract user and difficulty substrings
            line_object = current_line.substr(user_pos + 6, diff_pos - user_pos - 7);
            line_object_2 = current_line.substr(diff_pos + 12, vict_pos-diff_pos-13);
            if ((line_object==user2) && (line_object_2==difficulty)) {
                cout << "Retrieving statistics" << endl;
                cout<<line_object<<endl;
                cout<<line_object_2<<endl;
                // Process the statistics
                // Here, you can add the logic to update the statistics variables
                // For example:
                int symbol_find;
                if (user2 == "computer&"+User) {
                    cout<<"here"<<endl;
                    symbol_find = current_line.find("Victories: ");
                    computer_victories = stoi(current_line.substr(symbol_find + 11));
                    symbol_find = current_line.find("Defeats: ");
                    computer_defeats = stoi(current_line.substr(symbol_find + 9));
                    symbol_find = current_line.find("Ties: ");
                    computer_ties = stoi(current_line.substr(symbol_find + 6));
                } else if (user2==User) {
                    symbol_find = current_line.find("Victories: ");
                    human_victories = stoi(current_line.substr(symbol_find + 11));
                    symbol_find = current_line.find("Defeats: ");
                    human_defeats = stoi(current_line.substr(symbol_find + 9));
                    symbol_find = current_line.find("Ties: ");
                    human_ties = stoi(current_line.substr(symbol_find + 6));
                }
                // End of processing statistics logic
                retrieveFile.close();
                return 0; // Exit function after processing statistics
            }
            
        }
        
    }

    cout << "No data found for this user" << endl;
    retrieveFile.close();
    resetStats();
    return 0;
}

Game Game::startNewGame(){
    Game *players  = new Game;
    players->playGame();
}

void Game::writeStats(string write_stats){
    ofstream write_stats_file(write_stats, ofstream::out | ofstream::trunc);
    if(! write_stats_file.is_open()){
        cout << "Error opening file"<<endl;
    }else{
        write_stats_file <<"User: " << User <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << victories<< " "<< "Defeats: "  <<defeats << " " <<ties << " "<< endl;
        cout<< "Stats saved!"<<endl;
        write_stats_file.close();
    }

}

int Game::readAndWriteStats(string text_param, string user, string diff) {
    fstream stats_file_read_and_write(text_param, ios::in | ios::out);
    string current_line = "";
    bool userExists = false; // Flag to track if the user exists in the file

    if (!stats_file_read_and_write.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    } else {
        // Loop through each line in the file
        while (getline(stats_file_read_and_write, current_line)) {
            string line_object = "", line_object_2 = "";
            // Check if the line contains "User:", "Difficulty:", and "Victories:" substrings
            size_t user_pos = current_line.find("User: ");
            size_t diff_pos = current_line.find("Difficulty: ");
            size_t vict_pos = current_line.find("Victories: ");

            if (user_pos != string::npos && diff_pos != string::npos && vict_pos != string::npos) {
                // Extract user, difficulty, and victories substrings
                line_object = current_line.substr(user_pos + 6, diff_pos - user_pos - 7);
                line_object_2 = current_line.substr(diff_pos + 12, vict_pos - diff_pos - 13);

                // Check if the current line corresponds to the specified user and difficulty
                if ((line_object == user) && (line_object_2 == diff)) {
                    cout<<line_object<<endl;
                    cout<<line_object_2<<endl;
                    // Update the line with new victories, defeats, and ties
                    if(user == "computer&"+User){
                        cout<<"True"<<endl;
                        int new_victories = stoi(current_line.substr(vict_pos + 11)) + computer_victories;
                        int new_defeats = stoi(current_line.substr(current_line.find("Defeats: ") + 9)) + computer_defeats;
                        int new_ties = stoi(current_line.substr(current_line.find("Ties: ") + 6)) + computer_ties;
                        size_t line_length = current_line.length()+3; // Adding 1 for the newline character
                        //+ 3//
                        // Seek to the position of the line to be modified
                        stats_file_read_and_write.seekp(stats_file_read_and_write.tellg() - static_cast<streamoff>(line_length));

                        // Write the updated line
                        stats_file_read_and_write << "User: " << user << " " << "Difficulty: " << diff << " "
                                                << "Victories: " << computer_victories << " "
                                                << "Defeats: " << computer_defeats << " "
                                                << "Ties: " << computer_ties << " ";

                        userExists = true; // Set the flag to true
                        break; // Exit the loop since the user was found and updated
                    }else if (user == User){
                        cout<<"False"<<endl;
                        int new_victories = stoi(current_line.substr(vict_pos + 11)) + human_victories;
                        int new_defeats = stoi(current_line.substr(current_line.find("Defeats: ") + 9)) + human_defeats;
                        int new_ties = stoi(current_line.substr(current_line.find("Ties: ") + 6)) + human_ties;
                        size_t line_length = current_line.length()+2; // Adding 1 for the newline character
                        //+ 3//
                        // Seek to the position of the line to be modified
                        cout<< line_object.compare("Frank")<<endl;
                        cout<< "here"<<endl;
                        stats_file_read_and_write.seekp(stats_file_read_and_write.tellg() - static_cast<streamoff>(line_length));

                        // Write the updated line
                        stats_file_read_and_write << "User: " << user << " " << "Difficulty: " << diff << " "
                                                << "Victories: " << human_victories << " "
                                                << "Defeats: " << human_defeats << " "
                                                << "Ties: " << human_ties << " ";

                        userExists = true; // Set the flag to true
                        break; // Exit the loop since the user was found and updated
                    }
                    
                }
            }
        }

        // If the user does not exist in the file, append their data to the end of the file
        if (!userExists) {
            stats_file_read_and_write.close();
            stats_file_read_and_write.open(text_param, ios::out | ios::app); // Reopen in append mode
            if (!stats_file_read_and_write.is_open()) {
                cout << "Error opening file for appending" << endl;
                return -1;
            }

            if (user == "computer&"+User) {
                stats_file_read_and_write << "User: " << user << " " << "Difficulty: " << diff << " "
                                          << "Victories: " << computer_victories << " "
                                          << "Defeats: " << computer_defeats << " "
                                          << "Ties: " << computer_ties<< " "<< endl;
            }else{
                stats_file_read_and_write << "User: " << user << " " << "Difficulty: " << diff << " "
                                          << "Victories: " << human_victories << " "
                                          << "Defeats: " << human_defeats << " "
                                          << "Ties: " << human_ties<< " "<< endl;
            }
        }

        stats_file_read_and_write.close(); // Close the file
    }

    cout << "Operation completed" << endl;
    return 0;
}


int Game::retrievePreviousGame(string user) {
    cout << "Retrieving..." << endl;
    ifstream retriever("previous_game.txt");
    ofstream temp("temp.txt"); // Create a temporary file to write updated data
    string current_line;
    size_t symbol_find;
    bool userFound = false; // Flag to track if the user is found

    if (!retriever.is_open() || !temp.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    } else {
        while (getline(retriever, current_line)) {
            string line_object = "", line_object_2 = "";
            size_t user_pos = current_line.find("User: ");
            size_t human_pos = current_line.find("human: ");
            size_t arrays_pos = current_line.find("arrays: ");

            if (user_pos != string::npos && human_pos != string::npos) {
                line_object = current_line.substr(user_pos + 6, human_pos - user_pos - 7);
            }

            if (line_object == user) {
                cout << "Do you want to retrieve previous game? Y or N ";
                cin >> retrieve_decision;
                if (retrieve_decision == 'Y') {
                    User = user;
                    // Retrieve the game data and set flags
                    symbol_find = current_line.find("human: ");
                    human = current_line.at(symbol_find + 8);
                    symbol_find = current_line.find("nop: ");
                    nop = stoi(current_line.substr(symbol_find + 5));
                    symbol_find = current_line.find("location_on_game_array: ");
                    location_on_game_array = stoi(current_line.substr(symbol_find + 24));
                    symbol_find = current_line.find("array_size: ");
                    array_size = stoi(current_line.substr(symbol_find + 12));
                    symbol_find = current_line.find("difficulty: ");
                    difficulty = current_line.substr(symbol_find + 12, arrays_pos - symbol_find - 13);
                    symbol_find = current_line.find("arrays: ");
                    cout<<current_line.substr(symbol_find)<<endl;
                    for (int i = 0; i < 9; i++) {
                        game_array[i] = current_line.substr(symbol_find+8)[i];
                        cout<<game_array[i]<<endl;
                    }
                    cout<<"Finished"<<endl; 
                    current_line.erase();
                    userFound = true;
                } else if (retrieve_decision == 'N') {
                    // Skip writing this line to the temporary file
                    removeUserFromFile("arrays.txt", User, difficulty);
                    clearArray();
                    continue;
                } else {
                    cout << "Please input a valid option" << endl;
                    execute_option_one();
                }
            }
            // Write the line to the temporary file
            temp << current_line << endl;
        }

        retriever.close();
        temp.close();

        // Replace the original file with the temporary file if the user was found
        if (userFound) {
            remove("previous_game.txt");
            rename("temp.txt", "previous_game.txt");
        } else {
            remove("temp.txt"); // Remove the temporary file if the user was not found
        }

        return 0;
    }
}


void Game::execute_option_one(){
    if(User==""){
        cout <<"Please enter your name"<<endl;
        cin >>User;
        retrievePreviousGame(User);
        cout<<"yeah"<<endl;
        loadStats("temporary_stats.txt", "computer&"+User, difficulty);
        loadStats("temporary_stats.txt", User, difficulty);
        playGame();
    }else{
        retrievePreviousGame(User);
        loadStats("temporary_stats.txt", "computer&"+User, difficulty);
        loadStats("temporary_stats.txt", User, difficulty);
        playGame();
    }
}

void Game::execute_option_two(){
    cout << "Choose who starts the game" <<endl;
    cout << "1 - You ";
    cout << " 2 - Computer"<<endl;
    cin >> this->starter;
    if(this->starter == 2){
        // showTable();
        difficulty==""?difficulty="Elementary":difficulty;
        cout<< "Your symbol is O"<<endl;
        // srand(time(0));
        // game_array[checkRandomNumber()%9] = computer;
        // nop++;
        gameMenu();
    }else if(starter == 1){
        difficulty==""?difficulty="Elementary":difficulty;
        // playGame(); 
        gameMenu();
    }
}

void Game::clearArray(){
    for(int i=0; i<=8; i++){
        game_array[i] = '\0';
    }
}

void Game::resetStats(){
    human_defeats=0;
    human_ties = 0;
    human_victories = 0;
    computer_victories=0;
    computer_ties=0;
    computer_defeats=0;
    nop=0;
    clearArray();
}

void Game::execute_option_three(){
    //You have to input a code here to clear the current game and start a new game.
    cout << "Select difficulty "<<endl;
    cout <<left << setw(20) << setfill(' ')<<"Elementary" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Basic" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Medium" <<endl;
    cin >> difficulty; 
    cout << difficulty << " " << "selected" <<endl;
    resetStats();
    gameMenu();
}

void Game::execute_option_four(){
    saveGame();
    gameMenu();
    cout << "sucessfully saved"<<endl;
}

bool compareVictories(const PlayerStats& player1, const PlayerStats& player2) {
    cout<< player1.victories << player2.victories <<endl;
    return player1.victories > player2.victories;
}

void Game::execute_option_five(PlayerStats player[], int numPlayers){
    sort(player, player + numPlayers, compareVictories);

    // Display stats of the top 10 players
    cout << "Top 10 Players:" << endl;
    for (int i = 0; i < min(10, numPlayers); ++i) {
        cout << "Name: " << player[i].name << setw(10) << " Victories: " << player[i].victories 
             << setw(10) << " Defeats: " << player[i].defeats << setw(10) << " Ties: " << player[i].ties << endl;
    }
    gameMenu();
}


void Game::gameMenu(){ // Lists the options available to the user;
    cout << "Tic Tac Toe." << endl;
    cout << "Menu:" << endl;
    cout <<"Please choose any of the following "<<endl;
    cout << "1- Start or Continue game"<<endl;
    cout << "2- Choose who plays first" <<endl;
    cout << "3- Difficulty"<<endl;
    cout << "4- Pause game"<<endl;
    cout << "5- Statistics"<<endl;
    cout << "6- Exit"<<endl;
    cin >> chosen_option;
    execute_option(chosen_option);
}

void Game::playElementary(){
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn" <<endl;
    cin >> location_on_game_array;
    if(location_on_game_array == 0){
        gameMenu();
    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playElementary();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playElementary();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            srand(time(0));
            game_array[checkRandomNumber()] = computer;
            // showTable();
            checkAndComputeStats();
            nop+=2;
            playElementary();
        }
    }
    // cin >> location_on_game_array;
    
}

void Game::playGreedyWinner() {
    // Check if there is an empty cell to play
    for (int i = 0; i <= 8; i++) {
        if (game_array[i] == '\0') {
            // If an empty cell is found, play there
            game_array[i] = computer;
            // Check if this move leads to a win
            if (checkTable() == computer) return;
            game_array[i] = '\0';
            break; // Exit loop after playing
        }
    }
    // If no win was achieved with the current move, play randomly
    game_array[checkRandomNumber()] = computer;
}

void Game::playGreedy(){
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn, input a number between 0-9" <<endl;
    cin >>location_on_game_array;
    cout << location_on_game_array<<endl;
    if(location_on_game_array==0){
        gameMenu();
    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playGreedy();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playGreedy();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            playGreedyWinner();
            checkAndComputeStats();
            nop+=2;
            playGreedy();
        } 
    }
    
}


void Game::playMediumWinner(){
    for (int i = 0; i<=8; i++) {
        if (game_array[i] == '\0') {
            // If an empty cell is found, try placing the computer's symbol there
            game_array[i] = computer;
            // Check if this move results in a win for the computer
            if (checkTable() == computer) return; // If so, the game is over
            // If not, undo the move and continue searching
            game_array[i] = '\0';
            break;
        }
    }

    // If the computer can't win in the next move, check if the human can win
    for (int i = 0; i<=8; i++) {
        if (game_array[i] == '\0') {
            // If an empty cell is found, try placing the human's symbol there
            game_array[i] = human;
            // Check if this move results in a win for the human
            if (checkTable() == human) {
                // If so, block the human's winning move and return
                game_array[i] = computer;
                return;
            }
            // If not, undo the move and continue searching
            game_array[i] = '\0';
            game_array[checkRandomNumber()] = computer;
            break;
        }
    }

    
    // If no win was achieved with the current move, play randomly
    // game_array[checkRandomNumber()] = computer;
}

void Game::playMedium(){
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn, input a number between 0-9" <<endl;
    cin >> location_on_game_array;
    if(location_on_game_array==0){
        gameMenu();
    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playMedium();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playMedium();
        }else if(location_on_game_array == 0 ){
            gameMenu();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            playMediumWinner();
            checkAndComputeStats();
            nop+=2;
            playMedium();
        } 
    }
    
}

void Game::playGame() {
    /*C is the current players_signs chosen alphabet(X or O) 
    and n is the index on the board intended to play.*/
    difficulty==""?difficulty="Elementary":difficulty;
    if(starter==2){
        srand(time(0));
        game_array[checkRandomNumber()%9] = computer;
        nop++;
    }
    
    if(difficulty == "Elementary"){
        playElementary();
    }else if(difficulty == "Basic"){
        playGreedy();
    }else if(difficulty == "Medium"){
        playMedium();
    }else if(difficulty == "Advanced"){

    }else if(difficulty == "HumanVsHuman"){

    }else if(difficulty == "ComputerVsComputer"){

    }
    // countPlays();
}

int Game::checkRandomNumber(){
    int random_number = rand()%9;
    if (game_array[random_number] != '\0')
    {
        return checkRandomNumber();
    }  
    return random_number;
}

void Game::checkAndComputeStats(){
    if((checkTable() == 'X' && computer == 'X') || (checkTable() == 'O' && computer == 'O')){
        cout << "Computer wins"<<endl;
        computer_victories++;
        human_defeats++;
        readAndWriteStats("temporary_stats.txt", "computer&"+User, difficulty);
        readAndWriteStats("temporary_stats.txt", User, difficulty);
        removeUserFromFile("arrays.txt", User, difficulty);
        nop=0;
        clearArray();
    }else if((checkTable() == 'X' && human == 'X') || (checkTable() == 'O' && human == 'O')){
        cout << "Human wins"<<endl;
        nop=0;
        human_victories++;
        computer_defeats++;
        readAndWriteStats("temporary_stats.txt", "computer&"+User, difficulty);
        readAndWriteStats("temporary_stats.txt", User, difficulty);
        removeUserFromFile("arrays.txt", User, difficulty);
        clearArray();
    }else if(checkTable() == 'N'){
        cout << "It's a tie.!!"<<endl;
        nop=0;
        clearArray();
        computer_ties++;
        human_ties++;
        readAndWriteStats("temporary_stats.txt", "computer&"+User, difficulty);
        readAndWriteStats("temporary_stats.txt", User, difficulty);
        removeUserFromFile("arrays.txt", User, difficulty);
    }
}

char Game::checkTable(){ 
    // statements to check the equality in the table in case there is a winner 
    if(game_array[0] == game_array[1] && game_array[1] == game_array[2]){
        return game_array[0];
    }else if(game_array[3] == game_array[4] && game_array[4] == game_array[5]){
        return game_array[3];
    }else if(game_array[6] == game_array[7] && game_array[7] == game_array[8]){
        return game_array[6];
    }else if(game_array[0] == game_array[3] && game_array[3] == game_array[6]){
        return game_array[0];
    }else if(game_array[1] == game_array[4] && game_array[4] == game_array[7]){
        return game_array[1];
    }else if(game_array[2] == game_array[5] && game_array[5] == game_array[8]){
        return game_array[2];
    }else if(game_array[0] == game_array[4] && game_array[4] == game_array[8]){
        return game_array[0];
    }else if(game_array[2] == game_array[4] && game_array[4] == game_array[6]){
        return game_array[2];
    }else if(nop == 9){
        return 'N'; //N stands for no winner
    }
    return 't';
}

void Game::showTable(){
    cout << right <<"No of plays: "<< nop << "  "<< "Difficulty :" << difficulty <<endl;
    writeGameArrayToFile("arrays.txt");
    readAndPrintGameArrays("arrays.txt");
    cout << "|" << game_array[0] << "|" <<game_array[1] << "|" <<game_array[2]<<endl;
    cout << "-----"<<endl;
    cout << "|" << game_array[3] << "|" <<game_array[4] << "|" <<game_array[5]<<endl;
    cout << "------"<<endl;
    cout << "|" << game_array[6] << "|" <<game_array[7] << "|" <<game_array[8]<<endl;
}

void Game::restart_game(){
    delete this;
    // nop=0;
    // for(int j = 0; j<=array_size; j++){
    //     game_array[j] = ' ';
    // }
}

void Game::exit(){
    if(nop==0){
        ::exit(0);
    }else{
        cout << "Is the game over?. Are you sure that you want to exit ? Yes or No" <<endl;
        cin >> exit_confirmation;
        if(exit_confirmation == "Yes") {
            readAndWriteStats("temporary_stats.txt", "computer&"+User, difficulty);
            readAndWriteStats("temporary_stats.txt", User, difficulty);
            saveGame();
            ::exit(0);
        }else if(exit_confirmation == "No"){
            playGame();
        }else{
            cout << "Please input a valid expression" <<endl;
        }   
    }
    
}

int Game::saveGame(){
    fstream myfile;
    myfile.open("previous_game.txt", ios::in | ios::out);
    string current_line="";
    bool userExists=false;
    if(!myfile.is_open()){
        cout << "Error opening backup file" <<endl;
        return -1;
    }else{
        while (getline(myfile, current_line)) {
            string line_object = "", line_object_2 = "";
            // Check if the line contains "User:"
            size_t user_pos = current_line.find("User: ");
            size_t human_pos = current_line.find("human: ");

            if (user_pos != string::npos && human_pos != string::npos) {
                // Extract user, difficulty, and victories substrings
                line_object = current_line.substr(user_pos + 6, human_pos - user_pos - 7);
                if ((line_object == User)) {
                    cout<<line_object<<endl;
                    cout<<line_object_2<<endl;
                    cout<<"Saving your game"<<endl;
                    size_t line_length = current_line.length()+2; // Adding 1 for the newline character
                    myfile.seekp(myfile.tellg() - static_cast<streamoff>(line_length));
                    myfile <<"User: " << User<< " " << "human:  " << human<< " " 
                        <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
                        <<  "location_on_game_array: "<<location_on_game_array<< " " 
                        << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
                    myfile << "arrays: ";
                    for (int i = 0; i < 9; ++i) {
                        myfile << game_array[i];
                    }
                    userExists = true; // Set the flag to true
                    break; // Exit the loop since the user was found and updated
                }
            }
        }

        if (!userExists) {
            myfile.close();
            myfile.open("previous_game.txt", ios::out | ios::app); // Reopen in append mode
            if (!myfile.is_open()) {
                cout << "Error opening file for appending" << endl;
                return -1;
            }
            cout<<"Resaving"<<endl;
           
            myfile <<"User: " << User<< " " << "human:  " << human<< " " 
                <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
                <<  "location_on_game_array: "<<location_on_game_array<< " " 
                << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
                myfile << "arrays: ";
                for (int i = 0; i < 9; ++i) {
                    myfile << game_array[i];
                }
                myfile<<endl;
            
        }

        myfile.close(); // Close the file
        cout << "Operation completed" << endl;
        return 0;
    }   
}

// void Game::saveArrays(string file_name){
//      fstream myfile;
//     myfile.open(file_name, ios::in | ios::out);
//     string current_line="";
//     bool userExists=false;
//     if(!myfile.is_open()){
//         cout << "Error opening backup file" <<endl;
//         return -1;
//     }else{
//         while (getline(myfile, current_line)) {
//             string line_object = "", line_object_2 = "";
//             // Check if the line contains "User:"
//             size_t user_pos = current_line.find("User: ");
//             size_t human_pos = current_line.find("human: ");

//             if (user_pos != string::npos && human_pos != string::npos) {
//                 // Extract user, difficulty, and victories substrings
//                 line_object = current_line.substr(user_pos + 6, human_pos - user_pos - 7);
//                 if ((line_object == User)) {
//                     cout<<line_object<<endl;
//                     cout<<line_object_2<<endl;
//                     cout<<"Saving your game"<<endl;
//                     size_t line_length = current_line.length()+2; // Adding 1 for the newline character
//                     myfile.seekp(myfile.tellg() - static_cast<streamoff>(line_length));
//                     myfile <<"User: " << User<< " " << "human:  " << human<< " " 
//                         <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
//                         <<  "location_on_game_array: "<<location_on_game_array<< " " 
//                         << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
//                     myfile << "arrays: ";
//                     for (int i = 0; i < 9; ++i) {
//                         myfile << game_array[i];
//                     }
//                     userExists = true; // Set the flag to true
//                     break; // Exit the loop since the user was found and updated
//                 }
//             }
//         }

//         if (!userExists) {
//             myfile.close();
//             myfile.open("previous_game.txt", ios::out | ios::app); // Reopen in append mode
//             if (!myfile.is_open()) {
//                 cout << "Error opening file for appending" << endl;
//                 return -1;
//             }
//             cout<<"Resaving"<<endl;
           
//             myfile <<"User: " << User<< " " << "human:  " << human<< " " 
//                 <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
//                 <<  "location_on_game_array: "<<location_on_game_array<< " " 
//                 << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
//                 myfile << "arrays: ";
//                 for (int i = 0; i < 9; ++i) {
//                     myfile << game_array[i];
//                 }
//                 myfile<<endl;
            
//         }

//         myfile.close(); // Close the file
//         cout << "Operation completed" << endl;
//         return 0;
//     }   
// }

// void Game::showArrays(){
//     fstream myfile;
//     myfile.open("arrays.txt", ios::in | ios::out);
//     string current_line="";
//     bool userExists=false;
//     if(!myfile.is_open()){
//         cout << "Error opening backup file" <<endl;
//         return -1;
//     }else{
//         while (getline(myfile, current_line)) {
//             string line_object = "", line_object_2 = "";
//             // Check if the line contains "User:"
//             size_t user_pos = current_line.find("User: ");
//             size_t human_pos = current_line.find("human: ");

//             if (user_pos != string::npos && human_pos != string::npos) {
//                 // Extract user, difficulty, and victories substrings
//                 line_object = current_line.substr(user_pos + 6, human_pos - user_pos - 7);
//                 if ((line_object == User)) {
//                     cout<<line_object<<endl;
//                     cout<<line_object_2<<endl;
//                     cout<<"Saving your game"<<endl;
//                     size_t line_length = current_line.length()+2; // Adding 1 for the newline character
//                     myfile.seekp(myfile.tellg() - static_cast<streamoff>(line_length));
//                     myfile <<"User: " << User<< " " << "human:  " << human<< " " 
//                         <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
//                         <<  "location_on_game_array: "<<location_on_game_array<< " " 
//                         << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
//                     myfile << "arrays: ";
//                     for (int i = 0; i < 9; ++i) {
//                         myfile << game_array[i];
//                     }
//                     userExists = true; // Set the flag to true
//                     break; // Exit the loop since the user was found and updated
//                 }
//             }
//         }

//         if (!userExists) {
//             myfile.close();
//             myfile.open("previous_game.txt", ios::out | ios::app); // Reopen in append mode
//             if (!myfile.is_open()) {
//                 cout << "Error opening file for appending" << endl;
//                 return -1;
//             }
//             cout<<"Resaving"<<endl;
           
//             myfile <<"User: " << User<< " " << "human:  " << human<< " " 
//                 <<  "computer:  "<<computer << " " << "nop: "<< nop << " " 
//                 <<  "location_on_game_array: "<<location_on_game_array<< " " 
//                 << "array_size: "<<array_size<< " " << "difficulty: "<<difficulty << " ";
//                 myfile << "arrays: ";
//                 for (int i = 0; i < 9; ++i) {
//                     myfile << game_array[i];
//                 }
//                 myfile<<endl;
            
//         }

//         myfile.close(); // Close the file
//         cout << "Operation completed" << endl;
//         return 0;
//     }   
// }

// void Game::writeGameArrayToFile(const char* filename, const char* user, const char* difficulty) {
//     ofstream outfile(filename, ios::app);
//     if (outfile.is_open()) {
//         outfile << "User: " << user << " Difficulty: " << difficulty << endl;
//         for (int i = 0; i < 9; ++i) {
//             outfile << game_array[i];
//         }
//         outfile << endl;
//         outfile.close();
//     } else {
//         cout << "Unable to open file: " << filename << endl;
//     }
// }

void Game::writeGameArrayToFile(const char* filename) {
    ifstream infile(filename);
    ofstream outfile("temp.txt"); // Temporary file to store modified content
    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    string line;
    bool userFound = false;

    while (getline(infile, line)) {
        if (line.find("User: ") != string::npos && line.find("Difficulty: ") != string::npos) {
            size_t user_pos = line.find("User: ");
            size_t difficulty_pos = line.find("Difficulty: ");
            string user = line.substr(user_pos + 6, difficulty_pos - user_pos - 6);
            string difficulty = line.substr(difficulty_pos + 12);
            if (user == User && difficulty == this->difficulty) {
                // Found the specific user and difficulty, append the game array
                userFound = true;
                outfile << line << endl; // Write back the user and difficulty
                outfile << "Game Array: ";
                for (int j = 0; j < 9; ++j) {
                    outfile << game_array[j];
                }
                outfile << endl;
            } else {
                outfile << line << endl; // Write back unchanged for other users
            }
        } else if (userFound && line.find("Game Array") != string::npos) {
            // Skip over existing game arrays for the same user and difficulty
        } else {
            outfile << line << endl; // Write back unchanged for other lines
        }
    }

    // If user not found, append user and game array at the end
    if (!userFound) {
        outfile << "User: " << User << " Difficulty: " << difficulty << endl;
        outfile << "Game Array: ";
        for (int j = 0; j < 9; ++j) {
            outfile << game_array[j];
        }
        outfile << endl;
    }

    infile.close();
    outfile.close();

    // Rename temporary file to original filename
    if (remove(filename) != 0) {
        cout << "Error removing file: " << filename << endl;
        return;
    }
    if (rename("temp.txt", filename) != 0) {
        cout << "Error renaming file: temp.txt to " << filename << endl;
    }
    cout << "Game array successfully written to file: " << filename << endl;
}


void Game::readAndPrintGameArrays(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    string line;
    string user, difficulty;
    bool readingGameArrays = false;
    vector<string> gameArrays;

    while (getline(infile, line)) {
        if (line.find("User: ") != string::npos && line.find("Difficulty: ") != string::npos) {
            // Extract user and difficulty from the line
            size_t user_pos = line.find("User: ");
            size_t difficulty_pos = line.find("Difficulty: ");
            user = line.substr(user_pos + 6, difficulty_pos - user_pos - 6);
            difficulty = line.substr(difficulty_pos + 12);
            cout << "User: " << user << " Difficulty: " << difficulty << endl;
            readingGameArrays = true;
        } else if (readingGameArrays && line.find("Game Array") != string::npos) {
            // Extract and store the game array
            size_t array_pos = line.find(":") + 2; // Move past the colon and space
            string gameArrayStr = line.substr(array_pos);
            gameArrays.push_back(gameArrayStr);
        }
    }

    // Print the game arrays side by side
    int numArrays = gameArrays.size();
    int numRows = 3; // Assuming Tic Tac Toe board is 3x3
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numArrays; ++j) {
            string currentArray = gameArrays[j];
            // Print each cell of the current array
            for (int k = 0; k < 3; ++k) {
                cout << "| " << currentArray[i * 3 + k] << " ";
            }
            cout << "..... ";

        }
        cout << endl;
    }

    infile.close();
}


void Game::removeUserFromFile(const string& filename, const string& user, const string& difficulty) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    // Create a temporary file
    ofstream tempFile("temp2.txt");
    if (!tempFile.is_open()) {
        cout << "Error opening temporary file for writing." << endl;
        return;
    }

    string line;
    string current_user, current_difficulty;
    bool foundUser = false;
    bool skipLines = false;

    while (getline(infile, line)) {
        if (line.find("User: ") != string::npos && line.find("Difficulty: ") != string::npos) {
            // Extract user and difficulty from the line
            size_t user_pos = line.find("User: ");
            size_t difficulty_pos = line.find("Difficulty: ");
            current_user = line.substr(user_pos + 6, difficulty_pos - user_pos - 7);
            current_difficulty = line.substr(difficulty_pos + 12); // Adjusted substring extraction
            cout<< user <<difficulty<<endl;
            // Check if this is the user and difficulty we want to remove
            if (current_user == user && current_difficulty == difficulty) {
                foundUser = true;
                skipLines = true;
            } else {
                skipLines = false;
            }
        }

        // If we're not skipping lines, write the line to the temp file
        if (!skipLines) {
            tempFile << line << endl;
        }
    }

    infile.close();
    tempFile.close();

    // Remove the original file
    if (remove(filename.c_str()) != 0) {
        cout << "Error deleting file: " << filename << endl;
        return;
    }

    // Rename the temp file to the original filename
    if (rename("temp2.txt", filename.c_str()) != 0) {
        cout << "Error renaming file: temp.txt to " << filename << endl;
        return;
    }

    if (foundUser) {
        cout << "User " << user << " with difficulty " << difficulty << " has been removed from file." << endl;
    } else {
        cout << "User " << user << " with difficulty " << difficulty << " not found in file." << endl;
    }
}



int main(){
    Game game1;
    game1.gameMenu();
    return 0;
}