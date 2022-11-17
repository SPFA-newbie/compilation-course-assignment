#pragma once
#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include<vector>
#include<fstream>

#include"lexic_list.h"

std::vector<Lexic*> lexicalAnalyzer(std::ifstream& fin);

#endif