#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int Player1_bat(string array[2][12], int Player2_Batting[12][5], int overs, int select_Player1, int player2_bowling[5][6], int&, int&);
void Player2_bat(string array[2][12], int Player2_Batting[12][5], int overs, int select_Player1, int player1_bowling[5][6], int&);
int probability(int& batsmen_at_crease, int Player_batting[12][5], int bowler_at_crease);
void batsmen_swap(int&, int&);
void display_batsmen(string array[2][12], int player_batting[12][5], int batsmen_at_crease, int select_player1, int bowler);
int total_wickets(int player_batting[12][5]);
int total_runs(int player_batting[12][5]);
void F_scorecard(string array[2][12], int Player_Batting[12][5], int overs, int select_Player1, int player_bowling[5][6], int bowler, int& inning);


int main() {
	srand((unsigned int)time(0));
	string array[2][12] = { "Pakistan","Babar Azam (C)","Fakher Zaman","Imam-ul-Haq","Mohammad Rizwan","Khushdil Shah","Shadab Khan","Shahid Afridi","Muhammad Harris","Hasan Ali","Shaheen Afridi","Haris Rauf","India","Ishan Kishan","Ruturaj Gaiwad","Virat Kholi (C)","Risabh Pant","Hardik Pandya","Dinesh Karthik","Axer  Patel","Harsh Patel","Avesh Khan ","Bhuv Kumar ","Abhinandan " };
	int Player1_Batting[12][5] = { 0 };
	int Player2_Batting[12][5] = { 0 };
	int select_Player1, select_Player2;
	ofstream F("First innings.txt");
	F.close();
	ofstream S("Second innings.txt");
	S.close();
	cout << "----Welcome to your cricket simulator----" << endl;
	//select tour team
	cout << "Player 1  Select your team:" << endl;
	for (int i = 0; i < 2; i++)
		cout << i + 1 << "    " << array[i][0] << endl;
	cout << "Enter the respective number to select your team: ";
	cin >> select_Player1;
	while (select_Player1 <= 0 || select_Player1 >= 3) {
		cout << "Enter a valid number: ";
		cin >> select_Player1;
	}
	if (select_Player1 == 1) {

		select_Player2 = 2;
	}
	else {
		select_Player2 = 1;
	}

	cout << endl << "Player 1 team: " << array[select_Player1 - 1][0] << endl;
	cout << endl << "Player 2 team: " << array[select_Player2 - 1][0] << endl;
	int overs;
	//overs of the match
	cout << endl << endl << "Number of overs has been selected from file (configuration.txt) " << endl;

	ifstream obj("configuration.txt");
	obj >> overs;
	obj.close();
	if (overs <= 0 || overs >= 51) {
		cout << "invalid number in the file" << endl;
		cout << "Valid  number is between 1 to 50(included)" << endl;
		while (overs <= 0 || overs >= 51) {
			cout << "Enter a valid number for the overs";
			cin >> overs;
		}
	}
	cout << endl << "IT IS A  " << overs << "  MATCH " << endl;

	cout << endl << endl << "NOW TIME FOR THE TOSS" << endl;
	int Toss = rand() % 2;
	if (Toss == 0) {
		cout << "Player 1 won the toss" << endl;
	}
	else {
		cout << "Player 2 won the toss" << endl;

	}
	cout << "Player " << Toss + 1 << " Select the following" << endl;
	cout << "1. BAT" << endl;
	cout << "2. BALL" << endl;
	int select_Toss;
	cin >> select_Toss;
	while (select_Toss <= 0 || select_Toss >= 3) {
		cout << "Enter a valid number" << endl;
		cin >> select_Toss;
	}
	cout << endl << endl << "* FIRST INNING *" << endl;
	int player1_Bowling[5][6] = { 0 };
	int player2_Bowling[5][6] = { 0 };
	int inning = 1;
	int target;
	int won;
	if (Toss == 0) {
		if (select_Toss == 1) {
			Player1_bat(array, Player1_Batting, overs, select_Player1, player2_Bowling, inning, target);
			cout << endl << "__Second Inning_" << endl << endl;
			won = Player1_bat(array, Player2_Batting, overs, select_Player2, player1_Bowling, inning, target);

		}
		else
		{
			Player1_bat(array, Player2_Batting, overs, select_Player1, player1_Bowling, inning, target);
			cout << endl << "__Second Inning_" << endl << endl;
			won = Player1_bat(array, Player1_Batting, overs, select_Player1, player2_Bowling, inning, target);
		}
	}
	else
	{
		if (select_Toss == 1) {
			Player1_bat(array, Player2_Batting, overs, select_Player2, player1_Bowling, inning, target);
			cout << endl << "__Second Inning_" << endl << endl;
			won = Player1_bat(array, Player1_Batting, overs, select_Player1, player2_Bowling, inning, target);

		}
		else
		{
			Player1_bat(array, Player1_Batting, overs, select_Player1, player2_Bowling, inning, target);
			cout << endl << "__Second Inning_" << endl << endl;
			won = Player1_bat(array, Player2_Batting, overs, select_Player2, player1_Bowling, inning, target);
		}
	}
	cout << "Congratulation to " << array[won - 1][0] << " for winning the match" << endl;


}


int Player1_bat(string array[2][12], int Player1_Batting[12][5], int overs, int select_Player1, int player2_bowling[5][6], int& innings, int& target)
{
	static int bowler;
	int batsmen_at_crease = 1;
	int batsmen_at_running_end = 2;
	if (innings == 1) {
		if (select_Player1 == 1) {

			bowler = 2;
		}
		else {
			bowler = 1;
		}

		cout << "Player one Batting lineup " << endl;
		for (int i = 0; i < 12; i++) {
			if (i != 0)
				cout << i << ". " << array[select_Player1 - 1][i] << endl;
		}
		//bowler line up
		cout << endl << "Player two bowling lineup" << endl;
		for (int i = 7; i < 12; i++) {

			cout << i << ". " << array[bowler - 1][i] << endl;
		}
		int BOWLERS[5][6] = { 0 };
		int bowler_at_crease = 11;
		for (int i = 0; i < overs; i++) {
			if (bowler_at_crease == 6) {
				bowler_at_crease = 7;
			}
			cout << endl << endl << "Bowler: " << array[bowler - 1][bowler_at_crease] << endl;
			for (int j = 0; j < 6; j++) {
				int* ball = new int;
				cin.get();
				cout << i << "." << j << " ";//over and ball
				//ball
				*ball = probability(batsmen_at_crease, Player1_Batting, bowler_at_crease);
				// batsmen swap
				if (*ball != -1) {
					cout << *ball;
				}
				if (*ball == 1 || *ball == 3 || *ball == 5) {
					batsmen_swap(batsmen_at_crease, batsmen_at_running_end);
				}
				//out
				if (*ball == -1) {
					//bowler wicket update 
					player2_bowling[bowler_at_crease][2] += 1;
					cout << endl << "NAME            R     B     4s     6     " << endl;
					display_batsmen(array, Player1_Batting, batsmen_at_crease, select_Player1, bowler);
					cout << endl << total_runs(Player1_Batting) << "/" << total_wickets(Player1_Batting) << endl;
					//new player
					if (Player1_Batting[batsmen_at_running_end + 1][0] == 0 && batsmen_at_running_end + 1 != batsmen_at_crease) {
						batsmen_at_crease = batsmen_at_running_end + 1;
					}
					else
					{
						batsmen_at_crease += 1;
					}

				}
				//bowler run add
				if (*ball != -1) {
					player2_bowling[bowler_at_crease - 7][1] += *ball;
				}

				delete ball;
			}
			cout << endl;
			string view;
			batsmen_swap(batsmen_at_crease, batsmen_at_running_end);
			player2_bowling[bowler_at_crease - 7][5]++;
			cout << "Do you wish to view scorecard if yes then press (Y/y)" << endl;
			cout << "Press any other button to continue" << endl;
			cin >> view;
			if (view == "Y" || view == "y") {
				F_scorecard(array, Player1_Batting, overs, select_Player1, player2_bowling, bowler, innings);
			}
			bowler_at_crease--;
		}
		target = total_runs(Player1_Batting);
		innings++;
		return 0;
	}
	else
	{
		if (select_Player1 == 1) {

			bowler = 2;
		}
		else {
			bowler = 1;
		}

		cout << "Player one Batting lineup " << endl;
		for (int i = 0; i < 12; i++) {
			if (i != 0)
				cout << i << ". " << array[select_Player1 - 1][i] << endl;
		}
		//bowler line up
		cout << endl << "Player two bowling lineup" << endl;
		for (int i = 7; i < 12; i++) {

			cout << i << ". " << array[bowler - 1][i] << endl;
		}
		int BOWLERS[5][6] = { 0 };
		int bowler_at_crease = 11;
		for (int i = 0; i < overs; i++) {
			if (bowler_at_crease == 6) {
				bowler_at_crease = 7;
			}
			cout << endl << endl << "Bowler: " << array[bowler - 1][bowler_at_crease] << endl;
			for (int j = 0; j < 6; j++) {
				int* ball = new int;
				cin.get();
				cout << i << "." << j << " ";//over and ball
				//ball
				*ball = probability(batsmen_at_crease, Player1_Batting, bowler_at_crease);
				// batsmen swap
				if (*ball != -1) {
					cout << *ball;
				}
				if (*ball == 1 || *ball == 3 || *ball == 5) {
					batsmen_swap(batsmen_at_crease, batsmen_at_running_end);
				}
				//out
				if (*ball == -1) {
					//bowler wicket update 
					player2_bowling[bowler_at_crease][2] += 1;
					cout << endl << "NAME            R     B     4s     6     " << endl;
					display_batsmen(array, Player1_Batting, batsmen_at_crease, select_Player1, bowler);
					cout << endl << total_runs(Player1_Batting) << "/" << total_wickets(Player1_Batting) << endl;
					//new player
					if (Player1_Batting[batsmen_at_running_end + 1][0] == 0 && batsmen_at_running_end + 1 != batsmen_at_crease) {
						batsmen_at_crease = batsmen_at_running_end + 1;
					}
					else
					{
						batsmen_at_crease += 1;
					}

				}
				//bowler run add
				if (*ball != -1) {
					player2_bowling[bowler_at_crease - 7][1] += *ball;
				}
				if (total_runs(Player1_Batting) >= target) {
					F_scorecard(array, Player1_Batting, overs, select_Player1, player2_bowling, bowler, innings);
					cout << array[select_Player1 - 1][0] << "  WON THE MATCH" << endl;
					return select_Player1;
				}
				delete ball;
			}
			cout << endl;
			string view;
			batsmen_swap(batsmen_at_crease, batsmen_at_running_end);
			player2_bowling[bowler_at_crease - 7][5]++;
			cout << "Do you wish to view scorecard if yes then press (Y/y)" << endl;
			cout << "Press any other button to continue" << endl;
			cin >> view;
			if (view == "Y" || view == "y") {
				F_scorecard(array, Player1_Batting, overs, select_Player1, player2_bowling, bowler, innings);
			}

		}

		innings++;
	}
	return bowler;

}



void Player2_bat(string array[2][12], int Player2_Batting[12][5], int overs, int select_Player2, int player1_bowling[5][6])
{
	static int bowler;
	if (select_Player2 == 1) {

		bowler = 2;
	}
	else {
		bowler = 1;
	}
	//batting line up
	cout << "Player Two Batting Lineup" << endl;
	for (int i = 0; i < 12; i++) {
		if (i != 0)
			cout << i << ". " << array[select_Player2 - 1][i] << endl;
	}
	//bowler line up
	//int BOWLERS[5][5];
	cout << "Player one bowling lineup" << endl;
	for (int i = 6; i < 12; i++) {

		cout << i << ". " << array[bowler - 1][i] << endl;
	}


}


int probability(int& batsmen_at_crease, int Player_batting[12][5], int bowler_at_crease) {
	if (batsmen_at_crease < 6) {
		int prob = rand() % 10;
		if (prob == 0) {
			//batting stats update after out
			Player_batting[batsmen_at_crease][0] = bowler_at_crease;
			Player_batting[batsmen_at_crease][2]++;
			return -1;
		}
		else {
			//batsmen stats after a ball
			prob = rand() % 7;
			Player_batting[batsmen_at_crease][1] += prob;
			Player_batting[batsmen_at_crease][2]++;
			if (prob == 4)
				Player_batting[batsmen_at_crease][3]++;
			if (prob == 6)
				Player_batting[batsmen_at_crease][4]++;
			return prob;

		}
	}
	else {
		int prob = rand() % 2;
		if (prob == 0) {
			//batting stats update after out
			Player_batting[batsmen_at_crease][0] = bowler_at_crease;
			Player_batting[batsmen_at_crease][2]++;
			return -1;
		}
		else {
			//batsmen stats after a ball
			prob = rand() % 7;
			Player_batting[batsmen_at_crease][1] += prob;
			Player_batting[batsmen_at_crease][2]++;
			if (prob == 4)
				Player_batting[batsmen_at_crease][3]++;
			if (prob == 6)
				Player_batting[batsmen_at_crease][4]++;
			return prob;
		}
	}
}

void batsmen_swap(int& batsmen_at_crease, int& batsmen_at_running_end) {
	int temp;
	temp = batsmen_at_crease;
	batsmen_at_crease = batsmen_at_running_end;
	batsmen_at_running_end = batsmen_at_crease;

}

void display_batsmen(string array[2][12], int player_batting[12][5], int batsmen_at_crease, int select_player1, int bowler) {

	float runs = player_batting[batsmen_at_crease][1];
	float balls = player_batting[batsmen_at_crease][2] * 1.0;
	float Strike_rate = (runs / balls) * 100;
	cout << array[select_player1 - 1][batsmen_at_crease] << "    " << player_batting[batsmen_at_crease][1] << "     " << player_batting[batsmen_at_crease][2] << "     " << player_batting[batsmen_at_crease][3] << "    " << player_batting[batsmen_at_crease][4] << "     " << Strike_rate;
}


int total_wickets(int player_batting[12][5]) {
	int wicket = 0;
	for (int i = 0; i < 12; i++) {
		if (player_batting[i][0] != 0) {
			wicket++;
		}
	}
	return wicket;
}

int total_runs(int player_batting[12][5]) {
	int runs = 0;
	for (int i = 0; i < 12; i++) {
		runs += player_batting[i][1];
	}
	return runs;
}

void F_scorecard(string array[2][12], int Player_Batting[12][5], int overs, int select_Player1, int player2_bowling[5][6], int bowler, int& inning) {
	if (inning == 1) {
		ofstream F("First innings.txt", ios::out | ios::binary);
		F.clear();
		string temp;
		//batting stats
		F << array[select_Player1 - 1][0] << endl;
		F << "NAME                         R     B     4s     6     SR" << endl;
		for (int i = 1; i <= 11; i++) {
			F << array[select_Player1 - 1][i];
			if (Player_Batting[i][0] != 0) {
				F << "   bowled by " << array[bowler - 1][Player_Batting[select_Player1 - 1][0]];
			}
			else {
				F << "                        ";
			}
			for (int j = 1; j < 5; j++)
			{
				F << "   " << Player_Batting[i][j];
			}
			F << "\n" << endl;
		}
		F << "Total          " << total_runs(Player_Batting) << "/" << total_wickets(Player_Batting) << "\n";
		//bowling stats
		F << "NAME           O     R     M     W     Econ\n";
		F << array[bowler - 1][0] << "\n";
		for (int i = 7; i < 12; i++) {
			F << array[bowler - 1][i];

			F << "   " << player2_bowling[i - 7][5];
			F << "   " << player2_bowling[i - 7][1];
			F << "    0";
			F << "   " << player2_bowling[i - 7][2];
			float runs = player2_bowling[i - 7][1];
			float over = player2_bowling[i - 7][2];
			float econ = (runs / overs) * 100;

			F << "  " << econ << "\n" << endl;

		}
		F.close();
		cout << array[select_Player1 - 1][0] << endl;
		cout << "NAME          R     B     4s     6     " << endl;
		for (int i = 1; i <= 11; i++) {

			cout << array[select_Player1 - 1][i];

			for (int j = 1; j < 5; j++)
			{
				cout << "    " << Player_Batting[i][j];
			}
			cout << "\n" << endl;
		}
		cout << "Total          " << total_runs(Player_Batting) << "/" << total_wickets(Player_Batting) << "\n";
		//bowling stats

		cout << array[bowler - 1][0] << "\n";
		cout << "NAME           O     R     M     W     " << endl;
		for (int i = 7; i < 12; i++) {
			cout << array[bowler - 1][i];

			cout << "   " << player2_bowling[i - 7][5];
			cout << "   " << player2_bowling[i - 7][1];
			cout << "    0";
			cout << "   " << player2_bowling[i - 7][2] << endl;
			float runs = player2_bowling[i - 7][1];
			float over = player2_bowling[i - 7][2];
			float econ = (runs / over) * 100;



		}
	}
	else
	{
		ofstream R("Second innings.txt", ios::out | ios::binary);
		R.clear();
		string temp;
		//batting stats
		R << array[select_Player1 - 1][0] << endl;
		R << "NAME                         R     B     4s     6     SR" << endl;
		for (int i = 1; i <= 11; i++) {
			R << array[select_Player1 - 1][i];
			if (Player_Batting[i][0] != 0) {
				R << "   bowled by " << array[bowler - 1][Player_Batting[select_Player1 - 1][0]];
			}
			else {
				R << "                        ";
			}
			for (int j = 1; j < 5; j++)
			{
				R << "   " << Player_Batting[i][j];
			}
			R << "\n" << endl;
		}
		R << "Total          " << total_runs(Player_Batting) << "/" << total_wickets(Player_Batting) << "\n";
		//bowling stats
		R << "NAME           O     R     M     W     Econ\n";
		R << array[bowler - 1][0] << "\n";
		for (int i = 7; i < 12; i++) {
			R << array[bowler - 1][i];

			R << "   " << player2_bowling[i - 7][5];
			R << "   " << player2_bowling[i - 7][1];
			R << "    0";
			R << "   " << player2_bowling[i - 7][2];
			float runs = player2_bowling[i - 7][1];
			float over = player2_bowling[i - 7][2];
			float econ = (runs / overs) * 100;

			R << "  " << econ << "\n" << endl;
		}
	}
}
