#ifndef ADABOOST_PARSER_H_
#define ADABOOST_PARSER_H_

#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "adaboost.hpp"

namespace adaboost {

class Parser {
 public:
  Parser();
  ~Parser();
  unsigned int CountDataNum(const char *file_name);
  void ExtractDataAndLabel(const char *file_name,
                           const unsigned int feature_num,
                           const unsigned int dimension_num,
                           Classifier<double>::Data &data,
                           Labels &labels);
  void ParseLine(std::string line, int &label, std::vector<int> &index,
                         std::vector<double> &value);
  void TrimNewLine(std::string &line, const char *delimiter = "\r\n");
};

}  // namespace adaboost

#endif  // ADABOOST_PARSER_H_
