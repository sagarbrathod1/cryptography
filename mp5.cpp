#include <fstream>
#include <iostream>

using namespace std;

// function to check to see if a character in the array already exists or not
bool checkIfExists(char table[][5], int numberOfElements, char elem) {
  int row = 0, column = 0;
  for (int i = 0; i < numberOfElements; ++i) {
    if (table[row][column] == elem) {
      return true;
    }

    column += 1;

    if (column == 5) {     // moves to next row after 5th column has been processed 
      row += 1;
      column = 0;
    }
  }
  return false;
}

// function to fill up the array
void populate2dArray(char result[][5], string keyword) {
  int row = 0, column = 0;
  int numberOfElements = 0;

  for (int i = 0; i < keyword.size(); ++i) {
    if (checkIfExists(result, numberOfElements, keyword[i])) {
      continue;
    }
    char upper = toupper(keyword[i]);
    result[row][column] = upper;

    column += 1;    // goes to next column
    numberOfElements += 1;

    if (column == 5) {     // once the 5th column has been reached, moves to next row, first column of that row
      row += 1;
      column = 0;
    }
  }
  
  // this portion of code fills up the remainder of the array with the remainder of the alphabet
  char c = 'A';
  while (numberOfElements != 25) {
    if (checkIfExists(result, numberOfElements, c)) {
      c += 1;
      continue;
    }
    result[row][column] = c;
    c += 1;

    column += 1;
    numberOfElements += 1;

    if (column == 5) {
      row += 1;
      column = 0;
    }
  }
}

// function to decrypt lines in file
void decrypt(char table[][5], string input) {
  string result;     

  for (int i = 0; i < input.size(); ++i) {
    bool found = false;
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 5; ++k) {
        if (table[j][k] == input[i]) {    // compares array to keyword
          result += tolower(table[k][j]);     // reverses values of row and column values and changes char from upper case to lower case
          found = true;     // restart the loop
        }
      }
    }
    if (!found) {
      result += input[i];
    }
  }

  cout << input << endl;     // prints original line from file (upper case)
  cout << "decrypts to:" << endl;    
  cout << result << endl;     // prints decrypted result (lower case)
}

void encrypt(char table[][5], string input) {
  string result;     

  for (int i = 0; i < input.size(); ++i) {
    bool found = false;
    char upper = toupper(input[i]);    
    for (int j = 0; j < 5; ++j) {
      for (int k = 0; k < 5; ++k) {
        if (table[j][k] == upper) {     // compares char to keyword array
          result += table[k][j];     // reverses row and column values to encrypt the char
          found = true;     // restarts the loop
        }
      }
    }
    if (!found) {
      result += input[i];
    }
  }

  cout << input << endl;     // prints the original line from file (lower case)
  cout << "encrypts to:" << endl;
  cout << result << endl;     // prints the encrypted result (upper case)
}

// prints keyword 5x5 two-dimensional array
void print2dArray(char table[][5]) {
  cout << "0 1 2 3 4" << endl;

  cout << "---------------------" << endl;
  for (int i = 0; i < 5; ++i) {     // for loop to fill the array with the keyword
    cout << i << "|" << table[i][0] << "|" << table[i][1] << "|" << table[i][2]
         << "|" << table[i][3] << "|" << table[i][4] << "|" << endl;
    cout << "---------------------" << endl;
  }
}

int main(void) {
  ifstream file("mp5input.txt");     // opens text file

  if (!file.is_open()) {
    cout << "Cannot open file!" << endl;   
    return 1;
  }

  string keyword;     
  getline(file, keyword);     // reads first line/string from file

  cout << "keyword is " << keyword << endl;     

  char table[5][5];    

  populate2dArray(table, keyword);     // calls function to fill up 5x5 array with keyword

  print2dArray(table);     // prints array

  string input;    
  while (getline(file, input)) {     // loop keeps going as long as there are lines in the file to process
    cout << "****************************************" << endl;
    if (input[0] == 'D') {     
      decrypt(table, input.substr(2, input.size()));     // calls decrypt function to decrypt line
    } else {
      encrypt(table, input.substr(2, input.size()));     // or else it will call the encrypt function to encrypt line
    }
  }

  cout << "****************************************" << endl;

  return 0;
}
