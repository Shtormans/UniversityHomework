#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_set>

bool checkKeyword(const std::string& word) {
    static const std::unordered_set<std::string> keywords = {
        "if", "else", "for", "while", "function", "class", "include", "require", "return", "echo",
        "false", "true", "break", "continue", "switch", "case", "default", "try", "catch", "throw",
        "namespace", "use", "public", "private", "protected", "static", "final", "abstract", "interface",
        "extends", "implements", "new", "global", "const", "var", "define", "die", "exit", "include_once",
        "require_once", "yield", "yield from", "instanceof", "php", "as"
    };
    return keywords.count(word) > 0;
}

void analyze(const std::string& code) {
    enum class State { START, IN_IDENTIFIER, IN_NUMBER, IN_STRING, IN_CHAR, IN_OPERATOR, IN_COMMENT, IN_MULTILINE_COMMENT };

    State state = State::START;
    std::string lexeme;
    std::string comment;
    char stringDelimiter = '\0';
    char charDelimiter = '\0';

    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];

        switch (state) {
        case State::START:
            if (std::isalpha(c) || c == '_') {
                state = State::IN_IDENTIFIER;
                lexeme += c;
            }
            else if (std::isdigit(c)) {
                state = State::IN_NUMBER;
                lexeme += c;
            }
            else if (c == '\"' || c == '\'') {
                state = (c == '\"') ? State::IN_STRING : State::IN_CHAR;
                stringDelimiter = c;
                lexeme += c;
            }
            else if (c == '/') {
                if (i + 1 < code.size() && code[i + 1] == '/') {
                    state = State::IN_COMMENT;
                    ++i;
                }
                else if (i + 1 < code.size() && code[i + 1] == '*') {
                    state = State::IN_MULTILINE_COMMENT;
                    ++i;
                }
                else {
                    state = State::IN_OPERATOR;
                    lexeme += c;
                }
            }
            else if (std::isspace(c)) {

            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '!' || c == '&' || c == '|') {
                state = State::IN_OPERATOR;
                lexeme += c;
            }
            else if (c == ';' || c == ',' || c == '.' || c == ')' || c == '(' || c == '{' || c == '}') {
                std::cout << "Delimiter: " << c << std::endl;
            }
            break;

        case State::IN_IDENTIFIER:
            if (std::isalnum(c) || c == '_') {
                lexeme += c;
            }
            else {
                if (checkKeyword(lexeme)) {
                    std::cout << "Keyword: " << lexeme << std::endl;
                }
                else {
                    std::cout << "Identifier: " << lexeme << std::endl;
                }
                lexeme.clear();
                state = State::START;
                --i;
            }
            break;

        case State::IN_NUMBER:
            if (std::isdigit(c) || c == '.') {
                lexeme += c;
            }
            else {
                std::cout << "Number: " << lexeme << std::endl;
                lexeme.clear();
                state = State::START;
                --i;
            }
            break;

        case State::IN_STRING:
            lexeme += c;
            if (c == stringDelimiter && lexeme.back() != '\\') {
                std::cout << "String constant: " << lexeme << std::endl;
                lexeme.clear();
                state = State::START;
                stringDelimiter = '\0';
            }
            break;

        case State::IN_CHAR:
            lexeme += c;
            if (c == charDelimiter && lexeme.back() != '\\') {
                std::cout << "Character constant: " << lexeme << std::endl;
                lexeme.clear();
                state = State::START;
                charDelimiter = '\0';
            }
            break;

        case State::IN_OPERATOR:
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '!' || c == '&' || c == '|') {
                lexeme += c;
            }
            std::cout << "Operator: " << lexeme << std::endl;
            lexeme.clear();
            state = State::START;
            break;

        case State::IN_COMMENT:
            if (c == '\n') {
                std::cout << "Comment: " << comment << std::endl;
                comment.clear();
                state = State::START;
            }
            else {
                comment += c;
            }
            break;

        case State::IN_MULTILINE_COMMENT:
            comment += c;
            if (c == '*' && i + 1 < code.size() && code[i + 1] == '/') {
                comment += '/';
                ++i;
                std::cout << "Multiline Comment: " << comment << std::endl;
                comment.clear();
                state = State::START;
            }
            break;
        }
    }
}

int main() {
    std::ifstream file("example.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file" << std::endl;
        return 1;
    }

    std::string code;
    std::string line;
    while (std::getline(file, line)) {
        code += line + '\n';
    }

    file.close();

    analyze(code);

    return 0;
}



