#include  <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

//Creamos funciones
//Primero una función booleana para verificar si un caracter es operador
bool esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//Luego una función para obtener la precedencia(Reglas de ordenamiento) de los operadores
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convierte expresión infija a postfija (notación polaca inversa)
string infijaAPostfija(const string &expr) {
    stack<char> pila;
    string salida = "";

    for (char c: expr) {
        if (isspace(c)) continue;

        if (isalnum(c)) {
            salida += c;
            salida += ' ';
        } else if (c == '(') {
            pila.push(c);
        } else if (c == ')') {
            while (!pila.empty() && pila.top() != '(') {
                salida += pila.top();
                salida += ' ';
                pila.pop();
            }
            if (!pila.empty()) pila.pop();
        } else if (esOperador(c)) {
            while (!pila.empty() && precedencia(pila.top()) >= precedencia(c)) {
                salida += pila.top();
                salida += ' ';
                pila.pop();
            }
            pila.push(c);
        }
    }

    while (!pila.empty()) {
        salida += pila.top();
        salida += ' ';
        pila.pop();
    }

    return salida;
}

// Genera código intermedio a partir de la expresión postfija
void generarCodigoTresDirecciones(const string &postfija) {
    stack<string> pila;
    int temp = 1;

    for (size_t i = 0; i < postfija.size(); i++) {
        char c = postfija[i];
        if (isspace(c)) continue;

        if (isalnum(c)) {
            string op(1, c);
            pila.push(op);
        } else if (esOperador(c)) {
            string op2 = pila.top();
            pila.pop();
            string op1 = pila.top();
            pila.pop();

            string tempVar = "t" + to_string(temp++);
            cout << tempVar << " = " << op1 << " " << c << " " << op2 << endl;

            pila.push(tempVar);
        }
    }

    cout << "Resultado final en: " << pila.top() << endl;
}

int main() {
    string expresion;
    cout << "Ingresa una expresion: ";
    getline(cin, expresion);

    //Llamamos la función para convertir la expresión a postfija(es decir, lo operadores van después de los operandos)
    string postfija = infijaAPostfija(expresion);
    cout << "Expresion postfija: " << postfija << endl;

    //Una vez convertida la expresión a postifja, -> generamos el codigo intermedio.
    cout << "\nCodigo intermedio de tres direcciones:\n";
    generarCodigoTresDirecciones(postfija);

    return 0;
}
