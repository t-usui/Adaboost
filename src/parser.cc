#include "parser.h"

namespace adaboost {

Parser::Parser() {

}

Parser::~Parser() {

}

unsigned int Parser::CountDataNum(const char *file_name) {
  FILE *fp;
  int data_row_num;
  char c;

  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: could not open '%s'\n", file_name);
    exit(EXIT_FAILURE);
  }

  data_row_num = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n') data_row_num++;
  }
  return data_row_num;
}

void Parser::ExtractDataAndLabel(const char *file_name,
                                 const unsigned int feature_num,
                                 const unsigned int dimension_num,
                                 Classifier<double>::Data &data,
                                 Labels &labels) {
  FILE *fp;
  char buf[4096];    // Dangerous
  std::string line;
  int label;
  std::vector<int> index;
  std::vector<int>::iterator index_iter;
  std::vector<double> value;
  int value_iter;

  fp = fopen(file_name, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: could not open '%s'\n", file_name);
    exit(EXIT_FAILURE);
  }

  printf("Extracting data and labels...\n");

  data.reserve(feature_num);
  for (int fi = 0; fi < feature_num; fi++) {
    data[fi].reserve(dimension_num);

    if (fgets(buf, sizeof(buf), fp) == NULL) {
      fprintf(stderr, "Error: fgets");
      exit(EXIT_FAILURE);
    }

    line = std::string(buf);
    this->ParseLine(line, label, index, value);
    labels.push_back(label);

    value_iter = 0;
    for (int di = 0; di < dimension_num; di++) {
      index_iter = find(index.begin(), index.end(), di);
      if (index_iter != index.end()){
          data[fi][di] = value[value_iter];
          value_iter++;
      } else {
          data[fi][di] = 0;
      }
    }

    memset(buf, 0x00, sizeof(buf));
    index.clear();
    value.clear();
  }
  printf("Done.\n");
}

void Parser::ParseLine(std::string line, int &label, std::vector<int> &index, std::vector<double> &value) {
  std::vector<std::string> space_split_result;
  std::vector<std::string> colon_split_result;

  this->TrimNewLine(line);
  #ifdef DEBUG
    std::cout << line << std::endl;
  #endif
  // split "0 1:2 3:4 5:6" into { "0", "1:2", "3:4", "5:6" }
  boost::algorithm::split(space_split_result, line, boost::is_any_of(" "));
  try {
    label = boost::lexical_cast<int>(space_split_result[0]);
    for (int i = 1; i < (int)space_split_result.size(); i++){
      // split "1:2" into { "1", "2" }
      // std::cout << space_split_result[i] << std::endl;
      boost::algorithm::split(colon_split_result, space_split_result[i],
                              boost::is_any_of(":"));
      index.push_back(boost::lexical_cast<int>(colon_split_result[0]));
      value.push_back(boost::lexical_cast<double>(colon_split_result[1]));
    }
  } catch (boost::bad_lexical_cast) {
    fprintf(stderr, "Error: lexical_cast\n");
    exit(EXIT_FAILURE);
  }
}

// *delimiter's default value is "\n\r" in the prototype declaration
void Parser::TrimNewLine(std::string &line, const char *delimiter) {
  std::string::size_type pos;

  pos = line.find_first_of(delimiter);
  if (pos != std::string::npos) {
    line = line.replace(pos, 1, "");
  }
}

}  // namespace adaboost
