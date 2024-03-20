#include<iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

int diffrentNumbers(const std::vector<int>& numbers) {
	std::set<int> diffrentNumbers; // Создаем множество для хранения уникальных чисел
	for (int i : numbers) {
		diffrentNumbers.insert(i); // Добавляем число в множество
	}
	return diffrentNumbers.size(); // Возвращаем количество уникальных чисел
}

int numberOfMoves(std::vector<int>& player_1, std::vector<int>& player_2) {
	std::queue<int> table; // Создаем очередь для карт на столе
	int k = 0; // Инициализируем переменную для подсчета ходов
	while (!player_1.empty() && !player_2.empty() && k < 1000000) { // Бесконечный цикл, пока у обоих игроков есть карты и не превышен лимит ходов
		int card1 = player_1.front(); // Получаем верхнюю карту первого игрока
		int card2 = player_2.front(); // Получаем верхнюю карту второго игрока
		player_1.erase(player_1.begin()); // Удаляем верхнюю карту из колоды первого игрока
		player_2.erase(player_2.begin()); // Удаляем верхнюю карту из колоды второго игрока

		table.push(card1); // Помещаем карту первого игрока на стол
		table.push(card2); // Помещаем карту второго игрока на стол

		if ((card1 == 0 && card2 == 9) || (card1 > card2 && !(card1 == 9 && card2 == 0))) { // Проверка победителя по правилам игры
			while (!table.empty()) { // Пока на столе есть карты
				player_1.push_back(table.front()); // Перемещаем карты со стола в колоду первого игрока
				table.pop(); // Убираем верхнюю карту со стола
			}
		}
		else {
			while (!table.empty()) { // Пока на столе есть карты
				player_2.push_back(table.front()); // Перемещаем карты со стола в колоду второго игрока
				table.pop(); // Убираем верхнюю карту со стола
			}
		}
		k++; // Увеличиваем счетчик ходов
	}
	return k;
}

bool correctSequence(const std::string& stamples) {
	std::stack<char> stamples_2;  // Инициализация стека для отслеживания скобок

	// Перебор всех скобок в последовательности
	for (char i : stamples) {
		// Если текущая скобка является открывающей, помещаем её в стек
		if (i == '(' || i == '[' || i == '{') {
			stamples_2.push(i);
		}
		else {  // Если текущая скобка является закрывающей
			// Проверяем, что стек не пустой (должна быть соответствующая открывающая скобка)
			if (stamples_2.empty()) {
				return false;  // Если стек пустой, последовательность неправильная
			}
			char bracket = stamples_2.top();  // Получаем верхний элемент из стека
			// Проверяем соответствие текущей закрывающей скобки последней открывающей в стеке
			if ((i == ')' && bracket == '(') ||
				(i == ']' && bracket == '[') ||
				(i == '}' && bracket == '{')) {
				stamples_2.pop();  // Если скобки совпадают, удаляем открывающую из стека
			}
			else {
				return false;  // Если скобки не совпадают, последовательность неправильная
			}
		}
	}
	return stamples_2.empty();  // После обработки всех скобок, проверяем, что стек пустой
}

int result(const std::string& sequence) { // Объявляем функцию result с параметром sequence типа const ссылка на строку
	std::stack<int> stack; // Создаем стек для хранения чисел
	for (char i : sequence) { // Проходим по строке sequence посимвольно
		if ((i != '+') && (i != '-') && (i != '*') && (i != '/')) { // Если символ не является оператором
			stack.push(int(i - '0')); // Преобразуем символ в число и добавляем его в стек
		}
		else { // Если символ является оператором
			int num_1, num_2; // Объявляем переменные для хранения чисел
			num_2 = stack.top(); // Получаем верхний элемент из стека и присваиваем его num_2
			stack.pop(); // Удаляем верхний элемент из стека
			num_1 = stack.top(); // Получаем новый верхний элемент из стека и присваиваем его num_1
			stack.pop(); // Удаляем верхний элемент из стека
			switch (i) { // Выполняем операцию в зависимости от оператора
			case '+':
				stack.push(num_1 + num_2); // Складываем числа и добавляем результат в стек
				break;
			case '-':
				stack.push(num_1 - num_2); // Вычитаем числа и добавляем результат в стек
				break;
			case '*':
				stack.push(num_1 * num_2); // Умножаем числа и добавляем результат в стек
				break;
			case '/':
				stack.push(num_1 / num_2); // Делим числа и добавляем результат в стек
				break;
			}
		}
	}
	return stack.top(); // Возвращаем верхний элемент из стека (результат вычислений)
}

void processOperations(const std::vector<std::string>& operations) { // Объявляем функцию processOperations с параметром operations типа const ссылка на вектор строк
	std::unordered_set<std::string> set; // Создаем хэш-множество строк

	for (const std::string& op : operations) { // Проходим по вектору operations по каждой операции
		char operation = op[0]; // Получаем первый символ операции
		std::string word = op.substr(2); // Получаем строку, начиная с третьего символа операции

		if (operation == '+') { // Если операция - добавление
			set.insert(word); // Добавляем слово в хэш-множество
		}
		else if (operation == '-') { // Если операция - удаление
			set.erase(word); // Удаляем слово из хэш-множества
		}
		else if (operation == '?') { // Если операция - проверка наличия
			if (set.find(word) != set.end()) { // Если слово найдено в хэш-множестве
				std::cout << "YES" << std::endl; // Выводим "YES"
			}
			else {
				std::cout << "NO" << std::endl; // Иначе выводим "NO"
			}
		}
	}
}

int main() {
	//Задача: А.Разные
	int N = 0;
	std::cin >> N; // Считываем количество чисел
	std::vector<int> numbers(N); // Создаем вектор для хранения чисел
	numbers.reserve(100000); // Резервируем место в векторе
	for (int i = 0; i != N; i++) {
		std::cin >> numbers[i]; // Считываем числа и добавляем их в вектор
	}
	std::cout << diffrentNumbers(numbers); // Выводим результат работы функции
	//Задача: C.Игра в пьяницу
	std::vector<int> player_1(5); // Создаем вектор для карт первого игрока размером 5
	std::vector<int> player_2(5); // Создаем вектор для карт второго игрока размером 5

	//Ввод карт для каждого игрока
	for (int i = 0; i < 5; ++i) {
		std::cin >> player_1[i]; // Вводим карты первого игрока
	}
	for (int i = 0; i < 5; ++i) {
		std::cin >> player_2[i]; // Вводим карты второго игрока
	}
	int k = numberOfMoves(player_1, player_2);
	if (k >= 1000000) { // Если достигнут лимит ходов
		std::cout << "botva" << std::endl; // Выводим "ботву"
	}
	else {
		if (player_1.empty()) { // Если у первого игрока нет карт
			std::cout << "second " << k << std::endl; // Выводим "second" (второй игрок выиграл) и количество ходов
		}
		else {
			std::cout << "first " << k << std::endl; // Выводим "first" (первый игрок выиграл) и количество ходов
		}
	}
	//Задача: D.Правильная скобочная последовательность
	std::string stamples;
	std::cin >> stamples;  // Считываем скобочную последовательность

	if (correctSequence(stamples)) {
		std::cout << "yes" << std::endl;  // Выводим "yes", если скобочная последовательность правильная
	}
	else {
		std::cout << "no" << std::endl;  // Выводим "no", если скобочная последовательность неправильная
	}
	//Задача: Е.Постфиксная запись
	std::string Sequence; // Объявляем строку Sequence
	getline(std::cin, Sequence); // Считываем строку с пробелами из потока ввода и сохраняем в Sequence
	std::string sequence; // Объявляем строку sequence
	for (char i : Sequence) if (i != ' ') sequence += i; // Удаляем пробелы из строки Sequence и сохраняем в строке sequence
	std::cout << result(sequence); // Выводим результат работы функции result на строке sequence
	//Задача: G.Хеширование с удалением
	std::vector<std::string> operations; // Объявляем вектор строк operations
	std::string operation; // Объявляем строку operation
	while (getline(std::cin, operation) && operation != "#") { // Читаем строки из ввода до символа "#" и добавляем их в вектор operations
		operations.push_back(operation);
	}
	processOperations(operations); // Вызываем функцию processOperations с вектором операций
	return 0; // Возвращаем 0, обозначая успешное завершение программы
}