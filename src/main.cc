#include "main.hpp"

using namespace adaboost;

int main(){
  const unsigned int kDimensionNum = 10;
  const char *train_file_name = "train.txt";
  const char *test_file_name = "test.txt";
//  FILE* fp_train;
  Classifier<double>::Data train_data;
  Labels labels;
  Classifier<double>::Data test_data;
  unsigned int train_feature_num;
  unsigned int test_feature_num;

//  fp_train = fopen(train_file_name, "r");
//  if (fp_train == NULL) {
//    fprintf(stderr, "Error: could not open '%s'\n", train_file_name);
//    exit(EXIT_FAILURE);
//  }

  Parser parser;
  train_feature_num = parser.CountDataNum(train_file_name);
  parser.ExtractDataAndLabel(train_file_name, train_feature_num, kDimensionNum,
                             train_data, labels);

  // SIMULATE A TRAINER
  printf("Training ... \n");

  // retreive data and labels from the data file
//  for (unsigned int i=0; i < number_features; i++){
    
//    for (unsigned int j=0; j < number_features; j++){
//      data[i].push_back(j);
//    }
    // ground-truth classifier (TRAINER)
    
//    (i>70&&i<130) ? 
//      labels.push_back(1) :  // good
//      labels.push_back(-1);  // bad
//  }

  for (int fi = 0; fi < train_feature_num; fi++) {
    printf("%d ", labels[fi]);
    for (int di = 0; di < kDimensionNum; di++) {
      printf("%f ", train_data[fi][di]);
    }
    printf("\n");
  }

  printf("Done ... \n");
  printf("WeakClassifier ... \n");

  //
  // Create the pool of classifiers
  //
  Classifier<double>::CollectionClassifiers classifiers;
  classifiers.push_back(new WeakClassifierOne());
  classifiers.push_back(new WeakClassifierTwo());
  classifiers.push_back(new WeakClassifierThree());
  classifiers.push_back(new WeakClassifierFour());

  //
  // Ada boosting
  //
  ADA<double> ada;
  printf("Boosting ... \n");
  printf("Done \n");
  ClassificationResults weights = ada.ada_boost(classifiers, train_data, labels, 10);

  unsigned int classifiers_size = classifiers.size();
  for (unsigned int i = 0; i < classifiers_size; i++){
    std::cout << " w=" << weights[i];
  }
  std::cout << std::endl;
  
  // Start the strong classifier
  StrongClassifier<double> sc(weights, &classifiers, labels);

  parser.CountDataNum(test_file_name);
  parser.ExtractDataAndLabel(test_file_name, test_feature_num, kDimensionNum,
                             test_data, labels);

//  for (unsigned int i=0; i < number_features; i++){
//    test_data.clear();
//    for (unsigned int j=0; j < 3; j++){
//      test_data.push_back(j);
//    }
//    std::cout << " " << i << "," << sc.analyze(test_data);
//  }
  sc.analyze(test_data[0]);

  sc.performance();

}
