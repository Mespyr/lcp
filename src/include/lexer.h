#ifndef _LCP_LEXER_H_
#define _LCP_LEXER_H_

#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <assert.h>
#include "token.h"
#include "error.h"
#include "file.h"

bool is_number(std::string n);
long unsigned int find_next_token_start_col(long unsigned int column_number, std::string line);
long unsigned int find_token_end_col(long unsigned int column_number, std::string line);
long unsigned int find_string_end_col(long unsigned int column_number, std::string line);
std::vector<Token> tokenize_line(std::string line, std::string file_location, long unsigned int line_number);
std::vector<Token> tokenize_file(std::string file_location);

#endif
