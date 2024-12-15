#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> // ���� ��ġ ������ ���� �ð� ����
using namespace std;

// ������ ũ��� �⺻ �� ����
const int BOARD_SIZE = 15;  // �������� ũ��
const char EMPTY = '.'; // ��ĭ�� ��Ÿ���� ����
const char PLAYER1 = 'X'; // �÷��̾� 1�� ǥ�� ����
const char PLAYER2 = 'O'; // �÷��̾� 2�� ǥ�� ����

// �������� ��Ÿ���� 2���� ���� �ʱ�ȭ ( 15 X 15 ũ��, ��� ĭ�� EMPTY�� �ʱ�ȭ )
vector<vector<char>>board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));

//������ ��� �Լ�
void printBoard()
{
	//�� ��ȣ ���
	cout << "  ";
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		cout << i % 10 << " ";
	}
	cout << endl;

	// �� ��ȣ�� ������ ���� ���
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		cout << i % 10 << " "; // �� ��ȣ ���
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			cout << board[i][j] << " "; // �����ǿ� �� ĭ ���
		}
		cout << endl;
	}
}

//�÷��̾ ������ ��ġ�� ��ȿ���� Ȯ���ϴ� �Լ�
bool isValidMove(int x, int y)
{
	//������ ���� ���� �ְ� ��ĭ�̸� ��ȿ�� ������
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[x][y] == EMPTY;
}


//�¸� ���� Ȯ�� �Լ�
bool checkWin(int x, int y, char player)
{
	// 4���� ���� : ����, ����, �밢�� (/), �밢�� (\)
	const int dx[4] = { 1, 0, 1, 1 };
	const int dy[4] = { 0, 1, 1, -1 };

	for ( int direction = 0; direction < 4; ++direction)
	{
		int count = 1; // ���� ��ġ ����

		//�ش� �������� ���ӵ� ���� ǥ�� ���� ���� ( ������ )
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

		//�ش� �������� ���ӵ� ���� ǥ�� ���� ���� ( ������ )
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
		//���� ǥ�ð� 5�� �̻� ���ӵǸ� �¸�
		if (count >= 5) return true;
	}
	return false;
}

// ��ǻ���� ������ ���� �Լ�
void computerMove()
{
	while (true)
	{
		int x = rand() % BOARD_SIZE;
		int y = rand() % BOARD_SIZE;

		if (isValidMove(x, y))
		{
			board[x][y] = PLAYER2;
			cout << "Computer�� ���� ��ġ: " << x << "," << y << endl;
			break;
		}
	}
}


//1�ο� ����
void playSinglePlayerGame()
{
	srand(time(0)); // ���� �õ� ����
	char currentPlayer = PLAYER1; // ���� �÷��̾� ����
	while (true)
	{
		system("cls");
		cout << "1�ο� ���� ����\n";
		printBoard(); //���� ������ ���� ���

		if (currentPlayer == PLAYER1)
		{
			cout << "Player " << currentPlayer << "�� �����Դϴ�.\n ��� ���� �Է��ϼ���:";
			int x, y;
			cin >> x >> y; // �÷��̾ ���� ��ġ �Է�

			// ��ȿ���� ���� ��ġ ó��
			if (!isValidMove(x, y)) {
				cout << "Invalid move. Try again.\n";
				continue;
			}

			// �����ǿ� ���� �÷��̾��� ǥ�� �߰�
			board[x][y] = currentPlayer;

			// �¸� ���� Ȯ��
			if (checkWin(x, y, currentPlayer)) {
				system("cls");
				cout << "1�ο� ���� ����\n";
				printBoard();
				cout << "Player " << currentPlayer << " wins!\n";
				break;
			}
		}
		else
		{
			computerMove(); //��ǻ���� ����

			// �¸� ���� Ȯ��
			for (int i = 0; i < BOARD_SIZE; ++i)
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					if (board[i][j] == PLAYER2 && checkWin(i, j, PLAYER2))
					{
						printBoard();
						cout << "��ǻ�Ͱ� �̰���ϴ�!\n";
						return;
					}
				}
			}
		}
		// �÷��̾� ��ü
		currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
	}
}


//2�ο� ����
void playTwoPlayerGame()
{
	char currentPlayer = PLAYER1; //���� �÷��̾� ����
	while (true)
	{
		system("cls");
		cout << "            ���� ����\n"; // ���� ���� �޽���
		printBoard(); // ���� ������ ���� ���
		cout << "\nPlayer" << currentPlayer << "�� ���� �Դϴ�.\n��� ���� �Է��ϼ���";
		int x, y;
		cin >> x >> y; // �÷��̾ ���� ��ġ �Է�

		// ��ȿ���� ���� ��ġ ó��
		if (!isValidMove(x, y))
		{
			cout << "��ȿ���� ���� ������ �Դϴ�. �ٽ� �õ��� �ּ���\n";
			continue;
		}

		//�����ǿ� ���� �÷��̾��� ǥ�� �߰�
		board[x][y] = currentPlayer;

		//�¸� ���� Ȯ��
		if (checkWin(x, y, currentPlayer))
		{
			printBoard();
			cout << "Player " << currentPlayer << "�¸��߽��ϴ�!\n";
			break;
		}

		//�÷��̾� ��ü
		currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
	}
}



int main()
{
	cout << "������ӿ� ���Ű��� ȯ���մϴ�!!\n";
	int gameMode;
	cout << "���Ӹ�带 �������ּ���: 1(1�ο�) or 2(2�ο�):";
	cin >> gameMode;

	if (gameMode == 1)
	{
		playSinglePlayerGame(); // 1�ο� ���� ����
	}
	else if (gameMode == 2)
	{
		playTwoPlayerGame(); // ���� ����
	}
	else
	{
		cout << "�ùٸ��� ���� �Է��Դϴ�. ������ �����մϴ�.\n";
	}
	return 0;
}