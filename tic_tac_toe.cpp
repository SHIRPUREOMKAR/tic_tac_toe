#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>

using namespace std;

char board[3][3], mode, playerOne = 'o', playerTwo = 'x';
char anotherGame;
int row, column;

void displayBoard(){
    cout << "\033[2J\033[1;1H";
        cout<<"Player 1 : "<<playerOne<<"\t\t"<<"Player 2 / AI : "<<playerTwo<<"\n\n"; 
        cout<<" "<<board[0][0]<<" "<<"|"<<" "<<board[0][1]<<" "<<"|"<<" "<<board[0][2]<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<board[1][0]<<" "<<"|"<<" "<<board[1][1]<<" "<<"|"<<" "<<board[1][2]<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<board[2][0]<<" "<<"|"<<" "<<board[2][1]<<" "<<"|"<<" "<<board[2][2]<<endl;
}

void resetBoard(){
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) board[i][j] = ' ';
}

bool movesLeft(){
    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(board[i][j] == ' ') return false;  
    return true;
}

bool checkMove(int i, int j){
    if((i >= 3 || i < 0) || (j >= 3 || j < 0)) return 0;
    else if(board[i][j] != ' ') return 0;
    else return 1;
}

int checkWin(){
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[2][i] == board[1][i]){
            if(board[0][i] == 'x') return 100;
            else if(board[0][i] == 'o') return -100;
        }
    }
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if(board[i][0] == 'x') return 100;
            else if(board[i][0] == 'o') return -100;
        }
    }

    if((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0])){
        if(board[1][1] == 'x') return 100;
        else if(board[1][1] == 'o') return -100;
    }
    return 0;   
}

bool getMode(){
    cout<<"Select the mode : "<<"\n"<<"\n";
    cout<<"Enter 'M' - 2 Player mode or 'A' - AI mode.\n";
    cin>>mode;
    if(mode == 'M') return true;
    else if(mode == 'A') return false;
    else getMode();
}

int two_player_mode(){
    srand(time(0));
    int r = rand()%2;
    for(int i=0;i<9; i++){
        if(i%2 == r){
                displayBoard();
                cout<<"\nPlayer 1's turn, select a square : \n\n";
                cout<<"Enter row number : ";
                cin>>row;
                cout<<"\nEnter column number : ";
                cin>>column;
                while(checkMove(row-1,column-1) == 0){
                    cout<<"Invalid square...!! \n";
                    cout<<"Enter row number : ";
                    cin>>row;
                    cout<<"\nEnter column number : ";
                    cin>>column;
                }
                board[row-1][column-1] = playerOne;
                if(checkWin() == 100){
                    cout<<"Player 1 won..!!!";
                    break;
                }
            }
        else{
            displayBoard();
            cout<<"\nPlayer 2's turn, select a square : \n\n";
            cout<<"Enter row number : ";
            cin>>row;
            cout<<"\nEnter column number : ";
            cin>>column;
            while(checkMove(row-1,column-1) == 0){
                cout<<"Invalid square...!! \n";
                cout<<"Enter row number : ";
                cin>>row;
                cout<<"\nEnter column number : ";
                cin>>column;
            }
            board[row-1][column-1] = playerTwo;
            if(checkWin() == -100){
                cout<<"Player 2 won..!!!";
                break;
            }
        }
    }
    if(movesLeft() == true && checkWin() == 0) cout<<"\nTied..!!!\n";
    return 0;
    }
    
int minmax(bool maxplayer){
    int score = checkWin();

    if (score == 100 || score == -100) return score;

    if(movesLeft()) return 0;

    if(maxplayer){
        int best = INT_MIN;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'x';
                    best = max(best, minmax(!maxplayer));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else{
        int best = INT_MAX;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'o';
                    best = min(best, minmax(!maxplayer));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

int ai_mode(){
    srand(time(0));

    int r = rand()%2;
    for(int i=0; i < 9 ; i++){
        if(i%2 == r){
            displayBoard();
            cout<<"\nPlayer's turn, select a square : \n\n";
            cout<<"Enter row number : ";
            cin>>row;
            cout<<"\nEnter column number : ";
            cin>>column;
            while(checkMove(row-1,column-1) == 0){
                cout<<"Invalid square...!! \n";
                cout<<"Enter row number : ";
                cin>>row;
                cout<<"\nEnter column number : ";
                cin>>column;
            }
            board[row-1][column-1] = 'o';

            if(checkWin() == -100){
                cout<<"You won..!!!";
                break;
            }
        }
                else{
                int bestScore = INT_MIN, bestMoveRow = -1, bestMoveCol = -1;
                for (int k = 0; k < 3; ++k) {
                    for (int j = 0; j < 3; ++j) {
                        if (board[k][j] == ' ') {
                            board[k][j] = 'x';
                            int moveScore = minmax(false);
                            board[k][j] = ' ';
                            if (moveScore > bestScore) {
                                bestScore = moveScore;
                                bestMoveRow = k;
                                bestMoveCol = j;
                            }
                        }
                    }
                }
                board[bestMoveRow][bestMoveCol] = 'x';
                displayBoard();
                if(checkWin() == 100){
                    cout<<"You lose..!!!";
                    break;
                }
            }
        }
    if(movesLeft() == true && checkWin() == 0) cout<<"\nTied..!!!\n";
    return 0;
}

int gameEng(){
    resetBoard();
    cout << "\033[2J\033[1;1H";
    if(getMode()) two_player_mode();
    else ai_mode();
    cout<<"\nAnother game? (y/n)\n";
    cin>>anotherGame;
    if(anotherGame == 'y' || anotherGame == 'Y'){
        resetBoard();
        gameEng();
    }
    else if(anotherGame == 'n' || anotherGame == 'N') cout<<"Thank You for playing the game. \n";
}

int main(){
    gameEng();
}