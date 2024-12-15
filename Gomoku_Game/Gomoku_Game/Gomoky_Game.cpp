#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> // 랜덤 위치 생성을 위한 시간 정보
using namespace std;

// 오목판 크기와 기본 값 정의
const int BOARD_SIZE = 15;  // 오목판의 크기
const char EMPTY = '.'; // 빈칸을 나타내는 문자
const char PLAYER1 = 'X'; // 플레이어 1의 표시 문자
const char PLAYER2 = 'O'; // 플레이어 2의 표시 문자

// 오목판을 나타내는 2차원 벡터 초기화 ( 15 X 15 크기, 모든 칸을 EMPTY로 초기화 )
vector<vector<char>>board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));

//오목판 출력 함수
void printBoard()
{
	//열 번호 출력
	cout << "  ";
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		cout << i % 10 << " ";
	}
	cout << endl;

	// 행 번호와 오폭판 내용 출력
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		cout << i % 10 << " "; // 행 번호 출력
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			cout << board[i][j] << " "; // 오목판에 각 칸 출력
		}
		cout << endl;
	}
}

//플레이어가 선택한 위치가 유효한지 확인하는 함수
bool isValidMove(int x, int y)
{
	//오목판 범위 내에 있고 빈칸이면 유효한 움직임
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == EMPTY;
}


//승리 조건 확인 함수
bool checkWin(int x, int y, char player)
{
	// 4가지 방향 : 가로, 세로, 대각선 (/), 대각선 (\)
	const int dx[4] = { 1, 0, 1, 1 };
	const int dy[4] = { 0, 1, 1, -1 };

	for ( int direction = 0; direction < 4; ++direction)
	{
		int count = 1; // 현재 위치 포함

		//해당 방향으로 연속된 같은 표시 개수 세기 ( 정방향 )
		for (int step = 1; step < 5; ++step)
		{
			int nx = x + dx[direction] * step;
			int ny = y + dy[direction] * step;
			if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && BOARD_SIZE && board[nx][ny] == player)
			{
				count++;
			}
			else
			{
				break;
			}
		}

		//해당 방향으로 연속된 같은 표시 개수 세기 ( 역방향 )
		for (int step = 1; step < 5; ++step)
		{
			int nx = x - dx[direction] * step;
			int ny = y - dy[direction] * step;
			if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == player)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		//같은 표시가 5개 이상 연속되면 승리
		if (count >= 5) return true;
	}
	return false;
}

// 컴퓨터의 움직임 결정 함수
void computerMove()
{
	while (true)
	{
		int x = rand() % BOARD_SIZE;
		int y = rand() % BOARD_SIZE;

		if (isValidMove(x, y))
		{
			board[x][y] = PLAYER2;
			cout << "Computer가 놓은 위치: " << x << "," << y << endl;
			break;
		}
	}
}


//1인용 게임
void playSinglePlayerGame()
{
	srand(time(0)); // 랜덤 시드 설정
	char currentPlayer = PLAYER1; // 시작 플레이어 설정
	while (true)
	{
		system("cls");
		cout << "1인용 오목 게임\n";
		printBoard(); //현재 오목판 상태 출력

		if (currentPlayer == PLAYER1)
		{
			cout << "Player " << currentPlayer << "의 순서입니다.\n 행과 열을 입력하세요:";
			int x, y;
			cin >> x >> y; // 플레이어가 놓을 위치 입력

			// 유효하지 않은 위치 처리
			if (!isValidMove(x, y)) {
				cout << "Invalid move. Try again.\n";
				continue;
			}

			// 오목판에 현재 플레이어의 표시 추가
			board[x][y] = currentPlayer;

			// 승리 조건 확인
			if (checkWin(x, y, currentPlayer)) {
				system("cls");
				cout << "1인용 오목 게임\n";
				printBoard();
				cout << "Player " << currentPlayer << " wins!\n";
				break;
			}
		}
		else
		{
			computerMove(); //컴퓨터의 차례

			// 승리 조건 확인
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					if (board[i][j] == PLAYER2 && checkWin(i, j, PLAYER2))
					{
						printBoard();
						cout << "컴퓨터가 이겼습니다!\n";
						return;
					}
				}
			}
		}
		// 플레이어 교체
		currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
	}
}


//2인용 게임
void playTwoPlayerGame()
{
	char currentPlayer = PLAYER1; //시작 플레이어 설정
	while (true)
	{
		system("cls");
		cout << "            오목 게임\n"; // 게임 시작 메시지
		printBoard(); // 현재 오목판 상태 출력
		cout << "\nPlayer" << currentPlayer << "의 순서 입니다.\n행과 열을 입력하세요";
		int x, y;
		cin >> x >> y; // 플레이어가 놓을 위치 입력

		// 유효하지 않은 위치 처리
		if (!isValidMove(x, y))
		{
			cout << "유효하지 않은 움직임 입니다. 다시 시도해 주세요\n";
			continue;
		}

		//오목판에 현재 플레이어의 표시 추가
		board[x][y] = currentPlayer;

		//승리 조건 확인
		if (checkWin(x, y, currentPlayer))
		{
			printBoard();
			cout << "Player " << currentPlayer << "승리했습니다!\n";
			break;
		}

		//플레이어 교체
		currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
	}
}



int main()
{
	cout << "오목게임에 오신것을 환영합니다!!\n";
	int gameMode;
	cout << "게임모드를 선택해주세요: 1(1인용) or 2(2인용):";
	cin >> gameMode;

	if (gameMode == 1)
	{
		playSinglePlayerGame(); // 1인용 게임 실행
	}
	else if (gameMode == 2)
	{
		playTwoPlayerGame(); // 게임 실행
	}
	else
	{
		cout << "올바르지 않은 입력입니다. 게임을 종료합니다.\n";
	}
	return 0;
}