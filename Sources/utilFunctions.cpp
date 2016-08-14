#include "utilFunctions.hpp"

// General toString Template
template <typename T> string toString (T t) {
	stringstream s;
	s << t;
	return s.str();
	}

// Boolean Overload toString Template
template <> string toString <bool> (bool t) {
	return (t ? "Enabled" : "Disabled");
	}

// Pointer Template Overloads
template <> string toString <char const> (char const *t) {
	string s (t);
	return s;
	}

template <> string toString <char> (char *t) {
	string s (t);
	return s;
	}

template <> string toString <int> (int *t) {
	stringstream s;
	s << *t;
	return s.str();
	}

template <> string toString <float> (float *t) {
	stringstream s;
	s << *t;
	return s.str();
	}

template string toString (int);
template string toString (unsigned);
template string toString (float);
template string toString (double);
template string toString (string);

string toLowerCase (string s) {
	for (auto &i : s) i = tolower (i);
	return s;
	}

string toUpperCase (string s) {
	for (auto &i : s) i = toupper (i);
	return s;
	}

string toTitleCase (string s) {
	stringstream st;
	for (unsigned i = 0; i < s.size(); i++)
		i == 0 ?
		st << (char) toupper (s[i])
		   : i > 0 && s[i - 1] == ' ' ?
		   st << (char) toupper (s[i])
		   : st << (char) tolower (s[i]);
	return st.str();
	}

string splitCamelCase (string s) {
	stringstream st;
	for (auto i : s) if ( (char) i > 65 && (char) i < 90) st << " " << i;
		else st << i;
	return st.str();
	}

string trimStringLength (string s, unsigned maxLength) {
	if (s.length() < maxLength)
		return s;
	stringstream st;
	for (unsigned i = 0; i < maxLength; i++)
		st << s[i];
	return st.str();
	}

string padStringSpaces (string s, int length) {
	for (int i = s.length(); i < length; i++)
		s += " ";
	return s;
	}

bool fileExists (string filename) {
	ifstream file (filename);
	return file.good();
	}

double mod (double x) {
	return (x < 0 ? -x : x);
	}

void lineWrapText (sf::Text &text, int maxXPos) {
	string str = text.getString().toAnsiString();
	for (unsigned i = 0; i < str.size(); i++) {
		if (text.findCharacterPos (i).x > maxXPos)
			str.replace (str.find_last_of (" ", i), 1, "\n"), text.setString (str);
		}
	}


