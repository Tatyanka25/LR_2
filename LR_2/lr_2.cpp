#include<iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

int diffrentNumbers(const std::vector<int>& numbers) {
	std::set<int> diffrentNumbers; // ������� ��������� ��� �������� ���������� �����
	for (int i : numbers) {
		diffrentNumbers.insert(i); // ��������� ����� � ���������
	}
	return diffrentNumbers.size(); // ���������� ���������� ���������� �����
}

int numberOfMoves(std::vector<int>& player_1, std::vector<int>& player_2) {
	std::queue<int> table; // ������� ������� ��� ���� �� �����
	int k = 0; // �������������� ���������� ��� �������� �����
	while (!player_1.empty() && !player_2.empty() && k < 1000000) { // ����������� ����, ���� � ����� ������� ���� ����� � �� �������� ����� �����
		int card1 = player_1.front(); // �������� ������� ����� ������� ������
		int card2 = player_2.front(); // �������� ������� ����� ������� ������
		player_1.erase(player_1.begin()); // ������� ������� ����� �� ������ ������� ������
		player_2.erase(player_2.begin()); // ������� ������� ����� �� ������ ������� ������

		table.push(card1); // �������� ����� ������� ������ �� ����
		table.push(card2); // �������� ����� ������� ������ �� ����

		if ((card1 == 0 && card2 == 9) || (card1 > card2 && !(card1 == 9 && card2 == 0))) { // �������� ���������� �� �������� ����
			while (!table.empty()) { // ���� �� ����� ���� �����
				player_1.push_back(table.front()); // ���������� ����� �� ����� � ������ ������� ������
				table.pop(); // ������� ������� ����� �� �����
			}
		}
		else {
			while (!table.empty()) { // ���� �� ����� ���� �����
				player_2.push_back(table.front()); // ���������� ����� �� ����� � ������ ������� ������
				table.pop(); // ������� ������� ����� �� �����
			}
		}
		k++; // ����������� ������� �����
	}
	return k;
}

bool correctSequence(const std::string& stamples) {
	std::stack<char> stamples_2;  // ������������� ����� ��� ������������ ������

	// ������� ���� ������ � ������������������
	for (char i : stamples) {
		// ���� ������� ������ �������� �����������, �������� � � ����
		if (i == '(' || i == '[' || i == '{') {
			stamples_2.push(i);
		}
		else {  // ���� ������� ������ �������� �����������
			// ���������, ��� ���� �� ������ (������ ���� ��������������� ����������� ������)
			if (stamples_2.empty()) {
				return false;  // ���� ���� ������, ������������������ ������������
			}
			char bracket = stamples_2.top();  // �������� ������� ������� �� �����
			// ��������� ������������ ������� ����������� ������ ��������� ����������� � �����
			if ((i == ')' && bracket == '(') ||
				(i == ']' && bracket == '[') ||
				(i == '}' && bracket == '{')) {
				stamples_2.pop();  // ���� ������ ���������, ������� ����������� �� �����
			}
			else {
				return false;  // ���� ������ �� ���������, ������������������ ������������
			}
		}
	}
	return stamples_2.empty();  // ����� ��������� ���� ������, ���������, ��� ���� ������
}

int result(const std::string& sequence) { // ��������� ������� result � ���������� sequence ���� const ������ �� ������
	std::stack<int> stack; // ������� ���� ��� �������� �����
	for (char i : sequence) { // �������� �� ������ sequence �����������
		if ((i != '+') && (i != '-') && (i != '*') && (i != '/')) { // ���� ������ �� �������� ����������
			stack.push(int(i - '0')); // ����������� ������ � ����� � ��������� ��� � ����
		}
		else { // ���� ������ �������� ����������
			int num_1, num_2; // ��������� ���������� ��� �������� �����
			num_2 = stack.top(); // �������� ������� ������� �� ����� � ����������� ��� num_2
			stack.pop(); // ������� ������� ������� �� �����
			num_1 = stack.top(); // �������� ����� ������� ������� �� ����� � ����������� ��� num_1
			stack.pop(); // ������� ������� ������� �� �����
			switch (i) { // ��������� �������� � ����������� �� ���������
			case '+':
				stack.push(num_1 + num_2); // ���������� ����� � ��������� ��������� � ����
				break;
			case '-':
				stack.push(num_1 - num_2); // �������� ����� � ��������� ��������� � ����
				break;
			case '*':
				stack.push(num_1 * num_2); // �������� ����� � ��������� ��������� � ����
				break;
			case '/':
				stack.push(num_1 / num_2); // ����� ����� � ��������� ��������� � ����
				break;
			}
		}
	}
	return stack.top(); // ���������� ������� ������� �� ����� (��������� ����������)
}

void processOperations(const std::vector<std::string>& operations) { // ��������� ������� processOperations � ���������� operations ���� const ������ �� ������ �����
	std::unordered_set<std::string> set; // ������� ���-��������� �����

	for (const std::string& op : operations) { // �������� �� ������� operations �� ������ ��������
		char operation = op[0]; // �������� ������ ������ ��������
		std::string word = op.substr(2); // �������� ������, ������� � �������� ������� ��������

		if (operation == '+') { // ���� �������� - ����������
			set.insert(word); // ��������� ����� � ���-���������
		}
		else if (operation == '-') { // ���� �������� - ��������
			set.erase(word); // ������� ����� �� ���-���������
		}
		else if (operation == '?') { // ���� �������� - �������� �������
			if (set.find(word) != set.end()) { // ���� ����� ������� � ���-���������
				std::cout << "YES" << std::endl; // ������� "YES"
			}
			else {
				std::cout << "NO" << std::endl; // ����� ������� "NO"
			}
		}
	}
}

int main() {
	//������: �.������
	int N = 0;
	std::cin >> N; // ��������� ���������� �����
	std::vector<int> numbers(N); // ������� ������ ��� �������� �����
	numbers.reserve(100000); // ����������� ����� � �������
	for (int i = 0; i != N; i++) {
		std::cin >> numbers[i]; // ��������� ����� � ��������� �� � ������
	}
	std::cout << diffrentNumbers(numbers); // ������� ��������� ������ �������
	//������: C.���� � �������
	std::vector<int> player_1(5); // ������� ������ ��� ���� ������� ������ �������� 5
	std::vector<int> player_2(5); // ������� ������ ��� ���� ������� ������ �������� 5

	//���� ���� ��� ������� ������
	for (int i = 0; i < 5; ++i) {
		std::cin >> player_1[i]; // ������ ����� ������� ������
	}
	for (int i = 0; i < 5; ++i) {
		std::cin >> player_2[i]; // ������ ����� ������� ������
	}
	int k = numberOfMoves(player_1, player_2);
	if (k >= 1000000) { // ���� ��������� ����� �����
		std::cout << "botva" << std::endl; // ������� "�����"
	}
	else {
		if (player_1.empty()) { // ���� � ������� ������ ��� ����
			std::cout << "second " << k << std::endl; // ������� "second" (������ ����� �������) � ���������� �����
		}
		else {
			std::cout << "first " << k << std::endl; // ������� "first" (������ ����� �������) � ���������� �����
		}
	}
	//������: D.���������� ��������� ������������������
	std::string stamples;
	std::cin >> stamples;  // ��������� ��������� ������������������

	if (correctSequence(stamples)) {
		std::cout << "yes" << std::endl;  // ������� "yes", ���� ��������� ������������������ ����������
	}
	else {
		std::cout << "no" << std::endl;  // ������� "no", ���� ��������� ������������������ ������������
	}
	//������: �.����������� ������
	std::string Sequence; // ��������� ������ Sequence
	getline(std::cin, Sequence); // ��������� ������ � ��������� �� ������ ����� � ��������� � Sequence
	std::string sequence; // ��������� ������ sequence
	for (char i : Sequence) if (i != ' ') sequence += i; // ������� ������� �� ������ Sequence � ��������� � ������ sequence
	std::cout << result(sequence); // ������� ��������� ������ ������� result �� ������ sequence
	//������: G.����������� � ���������
	std::vector<std::string> operations; // ��������� ������ ����� operations
	std::string operation; // ��������� ������ operation
	while (getline(std::cin, operation) && operation != "#") { // ������ ������ �� ����� �� ������� "#" � ��������� �� � ������ operations
		operations.push_back(operation);
	}
	processOperations(operations); // �������� ������� processOperations � �������� ��������
	return 0; // ���������� 0, ��������� �������� ���������� ���������
}