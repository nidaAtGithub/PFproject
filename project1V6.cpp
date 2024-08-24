//All the libraries taht are used
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;
//All thr prototypes of the functions that are made
int toss();
void wicketFall(int &);
void oversBowled(int &);
int drawLiveScoreBoard();
void swapTeams(string [], string [],const int);
void scoreCompare(string, string, int &, int &);
int totalScore(int &, int &);
void swapPlayers(string &,string &);
void ballingFunc(string [], const int , int &, int &, int &, int &, int &);
void battingFunc(string [],string & , string &, int &, const int, int &, int &);
void teamNames(string [], string [] , string &, string &,const  int, int &);
void file1(string [], string [], string &, string &, const int, int &, int &, int &);
void file2(int &, int &, int &, int &, string [], string [], const int);

int main()
{
    drawLiveScoreBoard();
    return 0;
}

int drawLiveScoreBoard()
{
    const int size =11;
    string team1_players[size];
    string team2_players[size];

    string team1Win;
    string team2Win;


    //Variables for assignment of the team players to theses variables
    string ballingTeam[size];
    string battingTeam[size];

    //Used in filing function
    string fTeam1[size];
    string fTeam2[size];
    string Nteam1;
    string Nteam2;
  
    int overs =0;
    int TResult =0;   //Toss result
    string team1;
    string team2; 
    int innings =0;
    
    //These variables re passed to the balling function
    int gameOvers =0;   // to find the max balls that the one player can play
    int playerball_count =0;
    int oversCount =1;
    int maxBalls =0;
    
    //These variables pass to the totalScore function
    int score_result =0;
    int total_score =0;
    int scoreResult =0;

    //These variables are used in the batting function and pass to that as parameters
    int battingIndex =0;
    string player1;
    string player2;
    int outCounter =0;

    teamNames(team1_players, team2_players, team1, team2, size, overs);
    cout << "Runs: " << overs << endl;
    gameOvers = overs / 5;
    maxBalls = gameOvers*6;
    cout << "Max overs that a player can play is :  " << gameOvers << endl;
    cout << "The max balls that the player can bowl:   " << maxBalls << endl;
    TResult = toss();  //function calling to the toss function and the result will be store in the variable TResult
    Nteam1 = team1;
    Nteam2 = team2;
    
    //Assignment of an array that will pass to the file function
    for(int i=0; i<size; i++)
    {
        fTeam1[i] = team1_players[i]; 
    }
    for(int i=0; i<size; i++)
    {
        fTeam2[i] = team2_players[i]; 
    }

    if(TResult == 0)
    {
         cout << "Team1 won the toss\n";
         //Assignment of one array to the other
         for(int i =0; i< size; i++)
         {
            battingTeam[i] = team1_players[i];
         }
        //Assignment of one array to the other
         for(int i=0; i<size; i++)
         {
            ballingTeam[i] = team2_players[i];
         }
    //Assign team name to these variables after this tis will pass to the score compare functuoin
    team1Win = team1;
    team2Win = team2;

         
    }
    else
    {
         cout << "Team2 won the toss\n";
         //Assigninig the values to the other array
         for(int i=0; i<size; i++)
         {
            battingTeam[i] = team2_players[i];
         }
         for(int i=0; i<size; i++)
         {
            ballingTeam[i]  = team1_players[i];
         }
    team1Win = team2;
    team2Win = team1;
    }
    player1= battingTeam[battingIndex++];
    player2= battingTeam[battingIndex++];
    int playerBallIndex = 10;
    int scoreTeam1 =0;
    int scoreTeam2 =0;

   cout <<"|------------------------------------------First innings of match-----------------------------------------------|\n";
   cout <<"|***************************************************************************************************************|\n";
   //In this loop all the fuinctions are called and will perform the innings of teh match
   while(true)
   {
        oversBowled(oversCount);
        ballingFunc(ballingTeam, size, maxBalls, playerball_count, oversCount, gameOvers, playerBallIndex);
        scoreResult = totalScore(score_result,total_score);
        cout << "Score is: " << scoreResult << endl;
        battingFunc(battingTeam,player1, player2, scoreResult, size, battingIndex, outCounter);
        wicketFall(outCounter);
        if(oversCount >= overs || outCounter >= 10)
        {
            innings++;
            if( innings >=2 )
            {
                break;
            }
            cout << "|------------------------------------------------------Second innings started--------------------------------------|\n";
            cout << "|******************************************************************************************************************|\n";
            scoreTeam1 = total_score;
            gameOvers = overs / 5;
            maxBalls = gameOvers*6;
            battingIndex = 0;
            playerBallIndex = 10;
            swapTeams(battingTeam, ballingTeam, size);


            player1= battingTeam[battingIndex++];
            player2= battingTeam[battingIndex++];
            scoreResult = 0;
            playerball_count = 0;
            oversCount = 1;
            score_result =0;
            total_score =0;
            outCounter =0;
        }
   }
   scoreTeam2 = total_score;
   //Below show the summary of the program
   cout << "--------------------------------------Summary of the match--------------------------------------------\n";
   cout << "******************************************************************************************************\n";
   cout << "BattingTeam was\n";
   cout <<"------------------------------------------------\n";
   for(int i =0; i<size; i++)
   {
       cout << battingTeam[i] << endl;
   }
   cout << "Balling Team was\n";
   cout << "-----------------------------------------------\n";
   for(int i =0; i<size; i++)
   {
       cout << ballingTeam[i] << endl;
   }

    cout << "Total score of team1 is:  " << scoreTeam1 << endl;
    cout << "Total Score of team2 is:  " << scoreTeam2 << endl;
    scoreCompare(team1, team2, scoreTeam1,total_score);
    file1(fTeam1, fTeam2, Nteam1, Nteam2, size, overs, gameOvers, maxBalls);    //Function calling to the file1
    file2(maxBalls, gameOvers,scoreTeam1, scoreTeam2, ballingTeam, battingTeam , size);
    return 0;
}
//File2 that will write all the data of match
void file2(int &maxBalls, int &gameOvers, int &scoreTeam1, int &scoreTeam2, string ballingTeam[], string battingTeam[], const int size)
{
    ofstream fout;
    fout.open("Output.txt");
    if(!fout)
    {
        cout << "File2 not opend\n";
    }
    fout << "Maximum overs that the player can play is:  " << gameOvers << endl;
    fout << "Maximum balls that the baller can bowl is:   " << maxBalls << endl;
    fout << "Batting team players are\n";
    fout << "-----------------------------------------------\n";
    for(int i =0; i<size; i++ )
    {
        fout << battingTeam[i] << endl; 
    }
    fout << "Balling team polayers are\n";
    fout << "--------------------------------------------------\n";
    for(int i=0; i<size; i++)
    {
        fout << ballingTeam[i] << endl;
    }
    fout << "So now final result is\n";
    fout << "Score earn by team1 are:   " << scoreTeam1 << endl;
    fout << "Score earn by team2 are:   " << scoreTeam2 << endl;
    fout.close();
}
//Score function for comparing the scores
void scoreCompare(string team1, string team2, int &scoreTeam1, int &total_score)
{
    if(scoreTeam1 > total_score)
    {
        cout << team1 << " win the match with " << scoreTeam1 << endl;
    }
    else
    {
        cout << team2 << " win the match with " << total_score << endl;
    }
}
//Swap teams after the first innings
void swapTeams(string battingTeam[], string ballingTeam[], const int size)
{
    string temp[size];
    //Swapping of teams in an array
    for(int i=0; i<size; i++)
    {
        temp[i] = battingTeam[i];
        battingTeam[i] = ballingTeam[i];
        ballingTeam[i] = temp[i];
    }
    /*for(int i=0; i<size; i++) system("clear");
    {
            cout << "Swapping\n";
        cout << battingTeam[i] << "  " << endl;
    }*/
}
//Fall of wicket function
void wicketFall(int &outCounter)
{
    cout << "Players out are:  " << outCounter << endl;
}

//Batting Function
void battingFunc(string battingTeam[],string &player1, string &player2, int &scoreResult,const  int size, int &battingIndex, int &outCounter)
{
    cout << "Batting Player:   " << player1<< endl;
    cout << "Wicket Player:   " << player2 << endl;
                    
    
    switch(scoreResult)
    {
        case -1:  
              cout << "OUT Player:" << player1 << "\n";
              outCounter++;
              player1 = battingTeam[battingIndex++];
              break;
        case 1:
            swapPlayers(player1, player2);
            break; 
        case 3:
            swapPlayers(player1, player2);
            break;
        case 5:   
            swapPlayers(player1, player2);
            break;
        case 2:
            break;
        case 4:
            break;
        case 6:   
          break;
    }
}
//This function is going to swap the players according to their scores
void swapPlayers(string &player1, string &player2)
{
    string temp= "";
    temp = player1;
    player1 = player2;
    player2 = temp;
}
//This will done the balling of the match
void ballingFunc(string ballingTeam[], const int size, int &maxBalls, int &playerball_count, int &oversCount, int &gameOvers, int &playerBallIndex)
{

    cout << "Bowler is:  " << ballingTeam[playerBallIndex] << endl;
    cout << "Current Over Ball is " << playerball_count+1 << endl;
    cout << "Press the enter key to bowl the ball\n";
    cin.get();
    playerball_count++;

    if(playerball_count > 5 )
    {
        //To reset the values one the ballers index becomes less than 6
        if (playerBallIndex <= 6)
            playerBallIndex = 10;

        oversCount = oversCount + 1;
        playerball_count = 0; 
        cout << "Bowler changed!!\n"; 

    }
    
    
}
void oversBowled(int & oversCount)
{
    cout << "Inning's Over: " << oversCount << endl;
}

//This function will get the names of teh team and teh team pkayer from the user
void teamNames(string team1_players[], string team2_players[], string &team1, string &team2,const int size, int &overs)
{
    
    //These lines of code will get names of the team from the user
    cout << "Enter the name of the team1:  ";
    getline(cin, team1);
    cout << "Enter the name of the team2:  ";
    getline(cin, team2);

    //Loops below will gwet the names of teh player from the user
    cout << "Enter the names of the team1 Player:\n";
    for(int i=0; i<size; i++)
    {
        cout << "Player" << i+1 << " is: ";
        getline(cin, team1_players[i]);
    }
    cout << endl;
    cout << "----------------------------------------------\n";
    cout << "Enter the names of the team2 Player:\n";
    for(int i=0; i<size; i++)
    {
        cout << "Player" << i+1 << " is: ";
        getline(cin, team2_players[i]);
    }
    cout << endl;

    //Overs Input  
    cout << "Enter the overs for which the match is going to play:  ";
    cin >> overs;

    //Below 2 loops will print the names of the players 
    cout << "Players of team1 are:\n";
	cout << "---------------------------------------\n";
	for(int i =0; i<size; i++)
	{
            cout << i+1 << "-" << team1_players[i] << endl;
    }
    cout << "Players of team2 are:\n";
	cout << "----------------------------------\n";
	for(int i =0; i<size; i++)
	{
		cout << i+1 << "-" << team2_players[i] << endl;
	}
}

//This function will toss between the two teams and return the result ot the main function
int toss()
{
    srand(time(0));
    //const int size =11;
    int toss_result =0;
    toss_result =  rand()%2;   //I use random function for toss this will generate number 0 and 1 only
    return toss_result;
}


//This file1 function will read and write data to the function 
void file1(string fTeam1[], string fTeam2[], string &Nteam1, string &Nteam2,const  int size, int &overs, int &gameOvers, int &maxBalls )
{
    ofstream fout;    //fout is the variable that will use to write data to file
    //All the players name and and team names will be store in theis file including the no of overs
    fout.open("configuration.txt");
   
    if(!fout)
    {
        cout << "File not opened\n";
    }
	fout << "Total overs:\t" << overs << endl;
    fout << "Max Overs that a baller can play are:\t" << gameOvers << endl;
    fout << "Max balls are:\t" << maxBalls << endl;

	fout << "Name of the teams that are going to play\n";
	fout << Nteam1 << endl;
	fout << Nteam2 << endl;
	fout << "Players of team1 are\n";
	fout << "-------------------------------------------\n";
	for(int i =0; i<size; i++)
	{
		fout << i << "-" << fTeam1[i] << endl;
	}
	fout << endl; 
	fout << "Players of team2 are:\n";
	fout << "----------------------------------------\n";
	for(int i =0; i<size; i++)
	{
		fout << i << "-" << fTeam2[i] << endl;
	}
	fout << endl;
	fout.close();
}
//Function which will find the score and the toatal score of the players
int totalScore(int &score_result, int &total_score)
{
    srand(time(0));
    
    //do-loop is use so that condition must check once before the condition becomes false
    do
    {
        score_result = ((rand()%7) -1);
        total_score += score_result;
        cout << "Current score:  " << score_result << endl;
        cin.get();
        //system("clear");
        return score_result;
    }
    while(score_result != -1);
}