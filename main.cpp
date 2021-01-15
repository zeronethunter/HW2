#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>

void delete_last(vector<T>& vec, int count) { //удаляем с конца вектора count обьектов
    for (int i = 0; i < count; ++i) {
        vec.pop_back();
    }
}

void make_op(const string& op, float last, float pre_last, float& ans) { // делаем операцию
    if (op == "+") {
        ans = last + pre_last;
    } else if (op == "-") {
        ans = pre_last - last;
    } else if (op == "*") {
        ans = last * pre_last;
    } else if (op == "/") {
        if (last == 0) {
            throw runtime_error("!!!Can't divide by zero!!!");
        } else {
            ans = pre_last / last;
        }
    } else if (op == "sqrt") {
        ans = sqrt(last);
    } else if (op == "sin") {
        ans = sin(last);
    } else if (op == "cos") {
        ans = cos(last);
    } else if (op == "ctg") {
        ans = cos(last) / sin(last);
    } else if (op == "tg") {
        ans = sin(last) / cos(last);
    } else if (op == "exp") {
        ans = pow(M_E, last);
    } else if (op == "^") {
        ans = pow(pre_last, last);
    }
}

pair<string, bool> is_func (const string& ex, int pos) {  //проверка на функцию
    string funcs[7] = {"sqrt", "sin", "cos", "ctg", "exp", "tg"};
    string func = ex.substr(pos, 4);
    if (func == funcs[0]) {
        pair<string, bool> new_pair = {funcs[0], true};
        return new_pair;
    } else {
        func = ex.substr(pos, 3);
        for (const string& i : funcs) {
            if (func == i) {
                pair<string, bool> new_pair = {i, true};
                return new_pair;
            }
        }
    }
    if ((ex.substr(pos, 2)) == funcs[5]) {
        pair<string, bool> new_pair = {funcs[5], true};
        return new_pair;
    }
    pair<string, bool> new_pair = {"", false};
    return new_pair;
}
bool is_num (const char& sym) { //проверка на число
    if (((sym >= 48) && (sym <= 57)) || (sym == '.') || (sym == ',')) {
        return true;
    }
    return false;
}

template <typename T>

class number { //класс число
public:
    number (T new_num) {
        num = new_num;
    }
    number() {
        num = 0;
    }
    void input_value (T value) {
        num = value;
    }
    T get_value () const {
        return num;
    }
private:
    T num;
};

class op { //класс операция
public:
    op (const string& new_operation) {
        operation = new_operation;
        if ((new_operation == "+") || (new_operation == "-")) {
            priority = 1;
        } else if ((new_operation == "*") || (new_operation == "/")) {
            priority = 2;
        } else if (new_operation == "^"){
            priority = 3;
        } else {
            priority = 0;
        }
    }
    op (const char& new_operation) {
        string new_op;
        new_op += new_operation;
        operation = new_op;
        if ((new_operation == '+') || (new_operation == '-')) {
            priority = 1;
        } else if ((new_operation == '*') || (new_operation == '/')) {
            priority = 2;
        } else if (new_operation == '^') {
            priority = 3;
        } else {
            priority = 0;
        }
    }
    string get_operation () const {
        return operation;
    }
    unsigned int get_priority () const {
        return priority;
    }
private:
    string operation;
    unsigned int priority;
};

void delete_nums (vector<number<float>>& nums, vector<op>& ops, int pos) { //удаляем числа,используемые в скобках
    vector<op> new_ops;
    for (int i = pos + 1; i < ops.size(); ++i) { // выделяем операции в скобках
        new_ops.push_back(ops[i]);
    }
    switch (new_ops.size()) {
        case 1:
            delete_last(nums, 2);  //удаляем последние 2 числа в nums
            break;
        case 2:
            delete_last(nums, 3);  //удаляем последние 3 числа в nums
            break;
        case 3:
            delete_last(nums, 4);  //удаляем последние 4 числа в nums
            break;
        default:
            throw runtime_error("!!!Look what in brackets!!!");
    }
}

int find_last_bracket(vector<op> ops) { //последняя открытая скобочка в векторе операций
    for (int i = ops.size() - 1; i >= 0; --i) {
        if (ops[i].get_operation() == "(") {
            return i;
        }
    }
    throw runtime_error("!!!Some troubles with expression : brackets !!!");
}

int find_last_bracket(const string& ex, int pos) { //последняя откр скобочка, принадлежащая данной закрытой в строке
    int count = 0;
    for (int i = pos - 1; i >= 0; --i) {
        if (ex[i] == ')') {
            ++count;
        }
        if (ex[i] == '(') {
            if (count == 0) {
                return i;
            } else {
                --count;
            }
        }
    }
    throw runtime_error("!!!Some troubles with expression : brackets !!!");
}

void catch_error (const string& expression) { //ловим ошибки
    char first = expression[0];
    if (((first > 122) || (first < 97)) && ((first < 40) || (first > 57)) && (first != 94) //если начинаем с операции
                    && ((first < 94) || (first > 122))) {
        if (first != '-') {
            string error = "!!!Something wrong with operations : ' ";
            error += first;
            error += " '!!!";
            throw runtime_error(error);
        }
    }
    char last = expression[expression.length() - 1];
    if (((last > 122) || (last < 97)) && ((last < 40) || (last > 57)) && (last != 94) //елси заканчиваем операцией
        && ((first < 94) || (first > 122))) {
        string error = "!!!Something wrong with operations : ' ";
        error += last;
        error += " '!!!";
        throw runtime_error(error);
    }
    for (const char& i : expression) { //если пробелы
        if (i == ' ') {
            throw runtime_error("!!!There are spaces in expression!!!");
        }
        if (((first > 122) || (first < 97)) && ((first < 40) || (first > 57)) && (first != 94)
                && ((first < 94) || (first > 122))) {
            if ((i < 40) || (i > 47)) {
                string error = "!!!There are strange symbols in expression : ' ";
                error += i;
                error += " '!!!";
                throw runtime_error(error);
            }
        }
    }
    int count_of_brackets = 0; //если кол-во скобочек не четно
    for (const char& i : expression) {
        if ((i == 40) || (i == 41)) {
            ++count_of_brackets;
        }
    }
    if ((count_of_brackets % 2) != 0) {
        throw runtime_error("!!!There are " + to_string(count_of_brackets) + " brackets here. Is it legit? No!!!");
    }
    bool flag = false;
    for (int i = 0; i < expression.length(); ++i) {
        if ((expression[i] >= 42) && (expression[i] <= 47) || (expression[i] == 94)) {
            if (flag) {
                throw runtime_error("!!!Multiple operations!!!");
            }
            flag = true;
        } else {
            flag = false;
        }
    }
}

float do_simple_calc (vector<number<float>>& nums, vector<op>& ops) {
    for (int i = ops.size() - 1; i >= 0; --i) {
        float new_num;
        make_op(ops[i].get_operation(), nums[nums.size() - 1].get_value(), nums[nums.size() - 2].get_value(), new_num);
        nums.pop_back();
        nums.pop_back();
        nums.emplace_back(new_num);
    }
    return nums[0].get_value();
}

float calculator (const string& ex) {
    vector<number<float>> nums;
    vector<op> ops;
    string num;
    bool flag_negative = false, flag_func = false;
    for (int i = 0; i < ex.length(); ++i) {
        if (is_num(ex[i])) {  //если число
            flag_func = false;
            num += ex[i];  //получаем число
            if (i == ex.length() - 1) {
                number<float> new_num;
                if (flag_negative) {
                    new_num.input_value(stof(num) * (-1));  //создаем число
                    flag_negative = false;
                } else {
                    new_num.input_value(stof(num));
                }
                nums.push_back(new_num);  //кидаем число в вектор
            }
        } else {
            if (!num.empty()) { // выполняем добавление, только если число есть
                flag_func = false;
                number<float> new_num;
                if (flag_negative) {
                    new_num.input_value(stof(num) * (-1));  //создаем число
                    flag_negative = false;
                } else {
                    new_num.input_value(stof(num));
                }
                nums.push_back(new_num);  //кидаем число в вектор
                num.clear(); //чистим
            }
            if (is_func(ex, i).second && (ex[i-1] != 'c')) { //если функция и проверка на ctg
                op new_func(is_func(ex, i).first);
                ops.push_back(new_func);
                flag_func = true;
            } else if (ex[i] == '(') { //если открытая скобочка
                flag_func = false;
                op new_op("(");
                ops.push_back(new_op);
            } else if (ex[i] == ')') { //если закрытая скобочка
                flag_func = false;
                int pos_last_bracket = find_last_bracket(ops);  //находим первую с конца откр скобку в векторе
                int pos_last_bracket_expression = find_last_bracket(ex, i); //<...> в строке
                float new_num = calculator(ex.substr(pos_last_bracket_expression + 1,
                                                     i - pos_last_bracket_expression - 1));  //считаем, что внутри
                if (is_func(ops[pos_last_bracket - 1].get_operation(),
                            0).second && (pos_last_bracket != 0)) {  //если скобки стояли перед функцией
                    make_op(ops[pos_last_bracket - 1].get_operation(), new_num, 0, new_num); //считаем
                    nums.pop_back();  //удаляем лишь 1 число из вектора
                    ops.erase(ops.begin() + pos_last_bracket - 1);
                } else {
                    delete_nums(nums, ops, pos_last_bracket); //удаляем используемые числа
                }
                int size = ops.size();
                if (pos_last_bracket == size) { //если операций внутри не было
                    ops.pop_back(); //просто удаляем открытую скобочку
                } else {
                    for (int j = pos_last_bracket; j < size; ++j) {
                        ops.pop_back(); //удаляем операции со скобками
                    }
                }
                nums.emplace_back(new_num);
            } else if ((ex[i] >= 42) && (ex[i] <= 47) || (ex[i] == 94)) {
                if (ex[i] == '-') { //если минус
                    if (i == 0) {  //если в начале
                        flag_negative = true; //делаем отрицательным
                        continue;
                    } else if ((ex[i - 1] == '+') || (ex[i - 1] == '/') || (ex[i - 1] == '*') || (ex[i - 1] == '(')) {
                        flag_negative = true; //аналогично, если после операций
                        continue;
                    } else if (ex[i - 1] == '-') { //если же предыдущая операция минус, то делаем положительным
                        flag_negative = false;
                        continue;
                    }
                }
                flag_func = false; //иначе просто операция
                op new_op(ex[i]); //добавление в контейнер операций
                ops.push_back(new_op);
                if ((ops[ops.size() - 2].get_priority() >= ops[ops.size() - 1].get_priority() &&
                     (ops.size() != 1)
                     && (ops[ops.size() - 2].get_operation() != "("))) {  //если приоретет предыдущей больше
                    float new_num;
                    make_op(ops[ops.size() - 2].get_operation(), nums[nums.size() - 1].get_value(),
                            nums[nums.size() - 2].get_value(), new_num); //делаем ее
                    delete_last(nums, 2);  //заменяем последние 2 числа новым числом
                    op tmp = ops[ops.size() - 1];
                    delete_last(ops, 2);  //удаляем предыдущую операцию
                    ops.push_back(tmp);
                    nums.emplace_back(new_num);
                }
            } else if ((ex[i] >= 97) && (ex[i] <= 122) && !flag_func) {  //ничего не остается, кроме букв
                float new_num;
                if (ex[i] == 'e') {
                    new_num = M_E;
                } else if (ex[i] == 'p') {
                    new_num = M_PI;
                } else {
                    cout << "Enter " << ex[i] << " = ";
                    cin >> new_num;
                }
                nums.emplace_back(new_num);
            }
        }
    }
    return do_simple_calc(nums, ops); //считаем простое оставшееся выражение
}

int main() {
    cout << "Hello, this is calculator!" << endl;
    string expression;
    cout << "Enter what do you want to count :";
    getline(cin, expression);
    while (true) {
        try {
            catch_error(expression); //проверка на ошибки
            float answer = calculator(expression); //сама функция калькулятора
            cout << "Answer: " << answer << endl;
            cout << "Do you want to exit? Type Y or N" << endl;
            char exit;
            cin >> exit;
            if (exit == 'Y') {
                return 0;
            }
            cout << "Enter what do you want to count :";
            cin.ignore();
            getline(cin, expression);
        } catch (runtime_error& ex) {
            cout << ex.what() << endl;
            break;
        }
    }
}
