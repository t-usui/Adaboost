#ifndef ADABOOST_WEAK_CLASSIFIER_H_
#define ADABOOST_WEAK_CLASSIFIER_H_
#include "adaboost.hpp"

namespace adaboost {

class WeakClassifierOne : public Classifier<double> {
 public:
  int analyze(const std::vector<double>& i) const  {
//    if (i[0]>50 && i[0]<90) return 1;
    return -1;
  }
};
  
class WeakClassifierTwo : public Classifier<double> {
 public:
  int analyze(const std::vector<double>& i) const {
//    if (i[0]>80 && i[0]<130) return 1;
    return -1;
  }
};
  
class WeakClassifierThree : public Classifier<double> {
 public:
  int analyze(const std::vector<double>& i) const  {
//    if (i[0]>90 && i[0]<130) return 1;
    return -1;
  }
};
  
class WeakClassifierFour : public Classifier<double> {
 public:
  int analyze(const std::vector<double>& i) const {
//    if (i[0]>40 && i[0]<150) return 1;
    return -1;
  }
};

}

#endif	// ADABOOST_WEAK_CLASSIFIER_H_
