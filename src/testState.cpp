#include "State.hpp"
#include "gtest/gtest.h"
#include <assert.h>

// The fixture for testing class ScalarState
class ScalarStateTest : public virtual ::testing::Test {
 protected:
  ScalarStateTest() {
    testState1_.setRandom(1);
    testState2_.setRandom(2);
  }
  virtual ~ScalarStateTest() {
  }
  LWF::ScalarState testState1_;
  LWF::ScalarState testState2_;
  LWF::ScalarState::mtDifVec difVec_;
};

// Test constructors
TEST_F(ScalarStateTest, constructor) {
  LWF::ScalarState testState1;
}

// Test setIdentity and Identity
TEST_F(ScalarStateTest, setIdentity) {
  testState1_.setIdentity();
  ASSERT_EQ(testState1_.s_,0.0);
  ASSERT_EQ(LWF::ScalarState::Identity().s_,0.0);
}

// Test plus and minus
TEST_F(ScalarStateTest, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  ASSERT_EQ(difVec_(0),testState2_.s_-testState1_.s_);
  LWF::ScalarState testState3;
  testState1_.boxPlus(difVec_,testState3);
  ASSERT_NEAR(testState2_.s_,testState3.s_,1e-6);
}

// Test getValue, getId
TEST_F(ScalarStateTest, accessors) {
  ASSERT_TRUE(testState1_.getValue<0>() == testState1_.s_);
  ASSERT_TRUE(testState1_.getId<0>() == 0);
}

// Test operator=
TEST_F(ScalarStateTest, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_NEAR(testState2_.s_,testState1_.s_,1e-6);
}

// Test createDefaultNames
TEST_F(ScalarStateTest, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
}

// The fixture for testing class VectorState
class VectorStateTest : public virtual ::testing::Test {
 protected:
  VectorStateTest() {
    testState1_.setRandom(1);
    testState2_.setRandom(2);
  }
  virtual ~VectorStateTest() {
  }
  static const unsigned int N_ = 4;
  LWF::VectorState<N_> testState1_;
  LWF::VectorState<N_> testState2_;
  LWF::VectorState<N_>::mtDifVec difVec_;
};

// Test constructors
TEST_F(VectorStateTest, constructor) {
  LWF::VectorState<N_> testState1;
}

// Test setIdentity and Identity
TEST_F(VectorStateTest, setIdentity) {
  testState1_.setIdentity();
  ASSERT_EQ(testState1_.v_.norm(),0.0);
  ASSERT_EQ(LWF::VectorState<N_>::Identity().v_.norm(),0.0);
}

// Test plus and minus
TEST_F(VectorStateTest, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  ASSERT_NEAR((difVec_-(testState2_.v_-testState1_.v_)).norm(),0.0,1e-6);
  LWF::VectorState<N_> testState3;
  testState1_.boxPlus(difVec_,testState3);
  ASSERT_NEAR((testState2_.v_-testState3.v_).norm(),0.0,1e-6);
}

// Test getValue, getId
TEST_F(VectorStateTest, accessors) {
  ASSERT_TRUE(testState1_.getValue<0>() == testState1_.v_);
  ASSERT_TRUE(testState1_.getId<0>() == 0);
}

// Test operator=
TEST_F(VectorStateTest, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_NEAR((testState2_.v_-testState1_.v_).norm(),0.0,1e-6);
}

// Test createDefaultNames
TEST_F(VectorStateTest, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
}

// The fixture for testing class VectorState
class QuaternionStateTest : public virtual ::testing::Test {
 protected:
  QuaternionStateTest() {
    testState1_.setRandom(1);
    testState2_.setRandom(2);
  }
  virtual ~QuaternionStateTest() {
  }
  LWF::QuaternionState testState1_;
  LWF::QuaternionState testState2_;
  LWF::QuaternionState::mtDifVec difVec_;
};

// Test constructors
TEST_F(QuaternionStateTest, constructor) {
  LWF::QuaternionState testState1;
}

// Test setIdentity and Identity
TEST_F(QuaternionStateTest, setIdentity) {
  testState1_.setIdentity();
  ASSERT_TRUE(testState1_.q_.isNear(rot::RotationQuaternionPD(),1e-6));
  ASSERT_TRUE(LWF::QuaternionState::Identity().q_.isNear(rot::RotationQuaternionPD(),1e-6));
}

// Test plus and minus
TEST_F(QuaternionStateTest, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  ASSERT_NEAR((difVec_-testState2_.q_.boxMinus(testState1_.q_)).norm(),0.0,1e-6);
  LWF::QuaternionState testState3;
  testState1_.boxPlus(difVec_,testState3);
  ASSERT_TRUE(testState2_.q_.isNear(testState3.q_,1e-6));
}

// Test getValue, getId
TEST_F(QuaternionStateTest, accessors) {
  ASSERT_TRUE(testState1_.getValue<0>().isNear(testState1_.q_,1e-6));
  ASSERT_TRUE(testState1_.getId<0>() == 0);
}

// Test operator=
TEST_F(QuaternionStateTest, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_TRUE(testState2_.q_.isNear(testState1_.q_,1e-6));
}

// Test createDefaultNames
TEST_F(QuaternionStateTest, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
}

// The fixture for testing class VectorState
class NormalVectorStateTest : public virtual ::testing::Test {
 protected:
  NormalVectorStateTest() {
    testState1_.setRandom(1);
    testState2_.setRandom(2);
  }
  virtual ~NormalVectorStateTest() {
  }
  LWF::NormalVectorState testState1_;
  LWF::NormalVectorState testState2_;
  LWF::NormalVectorState::mtDifVec difVec_;
};

// Test constructors
TEST_F(NormalVectorStateTest, constructor) {
  LWF::NormalVectorState testState1;
}

// Test setIdentity and Identity
TEST_F(NormalVectorStateTest, setIdentity) {
  testState1_.setIdentity();
  ASSERT_TRUE(testState1_.n_ == Eigen::Vector3d(1,0,0));
  ASSERT_TRUE(LWF::NormalVectorState::Identity().n_ == Eigen::Vector3d(1,0,0));
}

// Test plus and minus
TEST_F(NormalVectorStateTest, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  LWF::NormalVectorState testState3;
  testState1_.boxPlus(difVec_,testState3);
  ASSERT_NEAR((testState2_.n_-testState3.n_).norm(),0.0,1e-6);
}

// Test getValue, getId
TEST_F(NormalVectorStateTest, accessors) {
  ASSERT_TRUE(testState1_.getValue<0>() == testState1_.n_);
  ASSERT_TRUE(testState1_.getId<0>() == 0);
}

// Test operator=
TEST_F(NormalVectorStateTest, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_TRUE(testState2_.n_ == testState1_.n_);
}

// Test createDefaultNames
TEST_F(NormalVectorStateTest, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
}

// Test getTwoNormals
TEST_F(NormalVectorStateTest, getTwoNormals) {
  Eigen::Vector3d m0;
  Eigen::Vector3d m1;
  testState1_.getTwoNormals(m0,m1);
  ASSERT_NEAR(m0.dot(testState1_.n_),0.0,1e-6);
  ASSERT_NEAR(m1.dot(testState1_.n_),0.0,1e-6);
}

// Test derivative of boxplus
TEST_F(NormalVectorStateTest, derivative) {
  const double d  = 1e-6;
  Eigen::Vector3d m0;
  Eigen::Vector3d m1;
  testState1_.getTwoNormals(m0,m1);
  difVec_.setZero();
  difVec_(0) = d;
  testState1_.boxPlus(difVec_,testState2_);
  ASSERT_NEAR(((testState2_.n_-testState1_.n_)/d-(-m1)).norm(),0.0,1e-6);
  difVec_.setZero();
  difVec_(1) = d;
  testState1_.boxPlus(difVec_,testState2_);
  ASSERT_NEAR(((testState2_.n_-testState1_.n_)/d-m0).norm(),0.0,1e-6);
}

class Auxillary{
 public:
  Auxillary(){
    x_ = 1.0;
  };
  ~Auxillary(){};
  double x_;
};

// The fixture for testing class StateSVQ
class StateTesting : public virtual ::testing::Test {
 protected:
  enum StateNames{
    s0, s1, s2, s3,
    v0, v1, v2,
    q0, q1
  };
  StateTesting() {
    assert(V_>=Q_-1);
    testScalar1_[0] = 4.5;
    testScalar2_[0] = -17.34;
    for(int i=1;i<S_;i++){
      testScalar1_[i] = testScalar1_[i-1] + i*i*46.2;
      testScalar2_[i] = testScalar2_[i-1] - i*i*0.01;
    }
    testVector1_[0] << 2.1, -0.2, -1.9;
    testVector2_[0] << -10.6, 0.2, -105.2;
    for(int i=1;i<V_;i++){
      testVector1_[i] = testVector1_[i-1] + Eigen::Vector3d(0.3,10.9,2.3);
      testVector2_[i] = testVector2_[i-1] + Eigen::Vector3d(-1.5,12,1785.23);
    }
    testQuat1_[0] = rot::RotationQuaternionPD(4.0/sqrt(30.0),3.0/sqrt(30.0),1.0/sqrt(30.0),2.0/sqrt(30.0));
    testQuat2_[0] = rot::RotationQuaternionPD(0.0,0.36,0.48,0.8);
    for(int i=1;i<Q_;i++){
      testQuat1_[i] = testQuat1_[i-1].boxPlus(testVector1_[i-1]);
      testQuat2_[i] = testQuat2_[i-1].boxPlus(testVector2_[i-1]);
    }
    for(int i=0;i<S_;i++){
      testState1_.getState<0>().array_[i].s_ = testScalar1_[i];
    }
    for(int i=0;i<V_;i++){
      testState1_.getState<1>().array_[i].v_ = testVector1_[i];
    }
    for(int i=0;i<Q_;i++){
      testState1_.getState<2>().array_[i].q_ = testQuat1_[i];
    }
    for(int i=0;i<S_;i++){
      testState2_.getState<0>().array_[i].s_ = testScalar2_[i];
    }
    for(int i=0;i<V_;i++){
      testState2_.getState<1>().array_[i].v_ = testVector2_[i];
    }
    for(int i=0;i<Q_;i++){
      testState2_.getState<2>().array_[i].q_ = testQuat2_[i];
    }
    testState1_.aux().x_ = 2.3;
    testState2_.aux().x_ = 3.2;
  }
  virtual ~StateTesting() {
  }
  static const unsigned int S_ = 4;
  static const unsigned int V_ = 3;
  static const unsigned int Q_ = 2;
  typedef LWF::AugmentedState<LWF::ComposedState<LWF::StateArray<LWF::ScalarState,S_>,LWF::StateArray<LWF::VectorState<3>,V_>,LWF::StateArray<LWF::QuaternionState,Q_>>,Auxillary> StateSVQAugmented;
  StateSVQAugmented testState1_;
  StateSVQAugmented testState2_;
  StateSVQAugmented::mtDifVec difVec_;
  double testScalar1_[S_];
  double testScalar2_[S_];
  Eigen::Vector3d testVector1_[V_];
  Eigen::Vector3d testVector2_[V_];
  rot::RotationQuaternionPD testQuat1_[Q_];
  rot::RotationQuaternionPD testQuat2_[Q_];
};

// Test constructors
TEST_F(StateTesting, constructors) {
  StateSVQAugmented testState1;
  ASSERT_EQ(testState1.aux().x_,1.0);
  StateSVQAugmented testState2(testState2_);
  testState2.boxMinus(testState2_,difVec_);
  ASSERT_NEAR(difVec_.norm(),0.0,1e-6);
  ASSERT_EQ(testState2.aux().x_,3.2);
}

// Test setIdentity and Identity
TEST_F(StateTesting, setIdentity) {
  testState1_.setIdentity();
  for(int i=0;i<S_;i++){
    ASSERT_EQ(testState1_.getState<0>().array_[i].s_,0.0);
  }
  for(int i=0;i<V_;i++){
    ASSERT_EQ(testState1_.getState<1>().array_[i].v_(0),0.0);
    ASSERT_EQ(testState1_.getState<1>().array_[i].v_(1),0.0);
    ASSERT_EQ(testState1_.getState<1>().array_[i].v_(2),0.0);
  }
  for(int i=0;i<Q_;i++){
    ASSERT_EQ(testState1_.getState<2>().array_[i].q_.w(),1.0);
    ASSERT_EQ(testState1_.getState<2>().array_[i].q_.x(),0.0);
    ASSERT_EQ(testState1_.getState<2>().array_[i].q_.y(),0.0);
    ASSERT_EQ(testState1_.getState<2>().array_[i].q_.z(),0.0);
  }
  for(int i=0;i<S_;i++){
    ASSERT_EQ(StateSVQAugmented::Identity().getState<0>().array_[i].s_,0.0);
  }
  for(int i=0;i<V_;i++){
    ASSERT_EQ(StateSVQAugmented::Identity().getState<1>().array_[i].v_(0),0.0);
    ASSERT_EQ(StateSVQAugmented::Identity().getState<1>().array_[i].v_(1),0.0);
    ASSERT_EQ(StateSVQAugmented::Identity().getState<1>().array_[i].v_(2),0.0);
  }
  for(int i=0;i<Q_;i++){
    ASSERT_EQ(StateSVQAugmented::Identity().getState<2>().array_[i].q_.w(),1.0);
    ASSERT_EQ(StateSVQAugmented::Identity().getState<2>().array_[i].q_.x(),0.0);
    ASSERT_EQ(StateSVQAugmented::Identity().getState<2>().array_[i].q_.y(),0.0);
    ASSERT_EQ(StateSVQAugmented::Identity().getState<2>().array_[i].q_.z(),0.0);
  }
}

// Test plus and minus
TEST_F(StateTesting, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  unsigned int index=0;
  for(int i=0;i<S_;i++){
    ASSERT_EQ(difVec_(index),testScalar2_[i]-testScalar1_[i]);
    index ++;
  }
  for(int i=0;i<V_;i++){
    ASSERT_EQ(difVec_(index),testVector2_[i](0)-testVector1_[i](0));
    index ++;
    ASSERT_EQ(difVec_(index),testVector2_[i](1)-testVector1_[i](1));
    index ++;
    ASSERT_EQ(difVec_(index),testVector2_[i](2)-testVector1_[i](2));
    index ++;
  }
  for(int i=0;i<Q_;i++){
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(0));
    index ++;
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(1));
    index ++;
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(2));
    index ++;
  }
  testState1_.boxPlus(difVec_,testState2_);
  for(int i=0;i<S_;i++){
    ASSERT_NEAR(testState2_.getState<0>().array_[i].s_,testScalar2_[i],1e-6);
  }
  for(int i=0;i<V_;i++){
    ASSERT_NEAR((testState2_.getState<1>().array_[i].v_-testVector2_[i]).norm(),0.0,1e-6);
  }
  for(int i=0;i<Q_;i++){
    ASSERT_TRUE(testState2_.getState<2>().array_[i].q_.isNear(testQuat2_[i],1e-6));
  }
  ASSERT_EQ(testState2_.aux().x_,testState1_.aux().x_);
}

// Test getValue, getId, and auxillary accessor
TEST_F(StateTesting, accessors) {
  ASSERT_TRUE(testState1_.getValue<s0>() == testScalar1_[0]);
  ASSERT_TRUE(testState1_.getValue<s1>() == testScalar1_[1]);
  ASSERT_TRUE(testState1_.getValue<s2>() == testScalar1_[2]);
  ASSERT_TRUE(testState1_.getValue<s3>() == testScalar1_[3]);
  ASSERT_NEAR((testState1_.getValue<v0>()-testVector1_[0]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState1_.getValue<v1>()-testVector1_[1]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState1_.getValue<v2>()-testVector1_[2]).norm(),0.0,1e-6);
  ASSERT_TRUE(testState1_.getValue<q0>().isNear(testQuat1_[0],1e-6));
  ASSERT_TRUE(testState1_.getValue<q1>().isNear(testQuat1_[1],1e-6));

  ASSERT_TRUE(testState1_.getId<s0>() == 0);
  ASSERT_TRUE(testState1_.getId<s1>() == 1);
  ASSERT_TRUE(testState1_.getId<s2>() == 2);
  ASSERT_TRUE(testState1_.getId<s3>() == 3);
  ASSERT_TRUE(testState1_.getId<v0>() == 4);
  ASSERT_TRUE(testState1_.getId<v1>() == 7);
  ASSERT_TRUE(testState1_.getId<v2>() == 10);
  ASSERT_TRUE(testState1_.getId<q0>() == 13);
  ASSERT_TRUE(testState1_.getId<q1>() == 16);

  ASSERT_EQ(testState1_.aux().x_,2.3);
}

// Test operator=
TEST_F(StateTesting, operatorEQ) {
  testState2_ = testState1_;
  for(int i=0;i<S_;i++){
    ASSERT_NEAR(testState2_.getState<0>().array_[i].s_,testScalar1_[i],1e-6);
  }
  for(int i=0;i<V_;i++){
    ASSERT_NEAR((testState2_.getState<1>().array_[i].v_-testVector1_[i]).norm(),0.0,1e-6);
  }
  for(int i=0;i<Q_;i++){
    ASSERT_TRUE(testState2_.getState<2>().array_[i].q_.isNear(testQuat1_[i],1e-6));
  }
  ASSERT_EQ(testState2_.aux().x_,testState1_.aux().x_);
}

// Test createDefaultNames
TEST_F(StateTesting, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
  ASSERT_TRUE(testState1_.getState<0>().name_ == "test_0");
  ASSERT_TRUE(testState1_.getState<1>().name_ == "test_1");
  ASSERT_TRUE(testState1_.getState<2>().name_ == "test_2");
  ASSERT_TRUE(testState1_.getState<0>().getState<0>().name_ == "test_0_0");
  ASSERT_TRUE(testState1_.getState<0>().getState<1>().name_ == "test_0_1");
  ASSERT_TRUE(testState1_.getState<0>().getState<2>().name_ == "test_0_2");
  ASSERT_TRUE(testState1_.getState<0>().getState<3>().name_ == "test_0_3");
  ASSERT_TRUE(testState1_.getState<1>().getState<0>().name_ == "test_1_0");
  ASSERT_TRUE(testState1_.getState<1>().getState<1>().name_ == "test_1_1");
  ASSERT_TRUE(testState1_.getState<1>().getState<2>().name_ == "test_1_2");
  ASSERT_TRUE(testState1_.getState<2>().getState<0>().name_ == "test_2_0");
  ASSERT_TRUE(testState1_.getState<2>().getState<1>().name_ == "test_2_1");
}

// Test ZeroArray
TEST_F(StateTesting, ZeroArray) {
  LWF::StateArray<LWF::ScalarState,0> testState1;
}

// Test Constness
TEST_F(StateTesting, Constness) {
  const StateSVQAugmented testState1(testState1_);
  std::cout << testState1.getValue<q1>() << std::endl;
}

// The fixture for testing class StateSVQ
class StateTesting2 : public virtual ::testing::Test {
 protected:
  enum StateNames{
    s0, s1, s2, s3,
    v0, v1, v2,
    q0, q1
  };
  StateTesting2() {
    assert(V_>=Q_-1);
    testScalar1_[0] = 4.5;
    testScalar2_[0] = -17.34;
    for(int i=1;i<S_;i++){
      testScalar1_[i] = testScalar1_[i-1] + i*i*46.2;
      testScalar2_[i] = testScalar2_[i-1] - i*i*0.01;
    }
    testVector1_[0] << 2.1, -0.2, -1.9;
    testVector2_[0] << -10.6, 0.2, -105.2;
    for(int i=1;i<V_;i++){
      testVector1_[i] = testVector1_[i-1] + Eigen::Vector3d(0.3,10.9,2.3);
      testVector2_[i] = testVector2_[i-1] + Eigen::Vector3d(-1.5,12,1785.23);
    }
    testQuat1_[0] = rot::RotationQuaternionPD(4.0/sqrt(30.0),3.0/sqrt(30.0),1.0/sqrt(30.0),2.0/sqrt(30.0));
    testQuat2_[0] = rot::RotationQuaternionPD(0.0,0.36,0.48,0.8);
    for(int i=1;i<Q_;i++){
      testQuat1_[i] = testQuat1_[i-1].boxPlus(testVector1_[i-1]);
      testQuat2_[i] = testQuat2_[i-1].boxPlus(testVector2_[i-1]);
    }
    testState1_.s<0>() = testScalar1_[0];
    testState1_.s<1>() = testScalar1_[1];
    testState1_.s<2>() = testScalar1_[2];
    testState1_.s<3>() = testScalar1_[3];
    testState1_.v<0>() = testVector1_[0];
    testState1_.v<1>() = testVector1_[1];
    testState1_.v<2>() = testVector1_[2];
    testState1_.q<0>() = testQuat1_[0];
    testState1_.q<1>() = testQuat1_[1];
    testState2_.s<0>() = testScalar2_[0];
    testState2_.s<1>() = testScalar2_[1];
    testState2_.s<2>() = testScalar2_[2];
    testState2_.s<3>() = testScalar2_[3];
    testState2_.v<0>() = testVector2_[0];
    testState2_.v<1>() = testVector2_[1];
    testState2_.v<2>() = testVector2_[2];
    testState2_.q<0>() = testQuat2_[0];
    testState2_.q<1>() = testQuat2_[1];
    testState1_.aux().x_ = 2.3;
    testState2_.aux().x_ = 3.2;
  }
  virtual ~StateTesting2() {
  }
  static const unsigned int S_ = 4;
  static const unsigned int V_ = 3;
  static const unsigned int Q_ = 2;
  typedef LWF::AugmentedState<LWF::StateSVQ2<S_,V_,Q_>,Auxillary> StateSVQAugmented;
  StateSVQAugmented testState1_;
  StateSVQAugmented testState2_;
  StateSVQAugmented::mtDifVec difVec_;
  double testScalar1_[S_];
  double testScalar2_[S_];
  Eigen::Vector3d testVector1_[V_];
  Eigen::Vector3d testVector2_[V_];
  rot::RotationQuaternionPD testQuat1_[Q_];
  rot::RotationQuaternionPD testQuat2_[Q_];
};

// Test constructors
TEST_F(StateTesting2, constructors) {
  StateSVQAugmented testState1;
  ASSERT_EQ(testState1.aux().x_,1.0);
  StateSVQAugmented testState2(testState2_);
  testState2.boxMinus(testState2_,difVec_);
  ASSERT_NEAR(difVec_.norm(),0.0,1e-6);
  ASSERT_EQ(testState2.aux().x_,3.2);
}

// Test setIdentity and Identity
TEST_F(StateTesting2, setIdentity) {
  testState1_.setIdentity();
  ASSERT_EQ(testState1_.s<0>(),0.0);
  ASSERT_EQ(testState1_.s<1>(),0.0);
  ASSERT_EQ(testState1_.s<2>(),0.0);
  ASSERT_EQ(testState1_.s<3>(),0.0);
  ASSERT_EQ(testState1_.v<0>().norm(),0.0);
  ASSERT_EQ(testState1_.v<1>().norm(),0.0);
  ASSERT_EQ(testState1_.v<2>().norm(),0.0);
  ASSERT_EQ(testState1_.q<0>().boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(testState1_.q<1>().boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().s<0>(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().s<1>(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().s<2>(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().s<3>(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().v<0>().norm(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().v<1>().norm(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().v<2>().norm(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().q<0>().boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(StateSVQAugmented::Identity().q<1>().boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
}

// Test plus and minus
TEST_F(StateTesting2, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  unsigned int index=0;
  for(int i=0;i<S_;i++){
    ASSERT_EQ(difVec_(index),testScalar2_[i]-testScalar1_[i]);
    index ++;
  }
  for(int i=0;i<V_;i++){
    ASSERT_EQ(difVec_(index),testVector2_[i](0)-testVector1_[i](0));
    index ++;
    ASSERT_EQ(difVec_(index),testVector2_[i](1)-testVector1_[i](1));
    index ++;
    ASSERT_EQ(difVec_(index),testVector2_[i](2)-testVector1_[i](2));
    index ++;
  }
  for(int i=0;i<Q_;i++){
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(0));
    index ++;
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(1));
    index ++;
    ASSERT_EQ(difVec_(index),testQuat2_[i].boxMinus(testQuat1_[i])(2));
    index ++;
  }
  testState1_.boxPlus(difVec_,testState2_);
  ASSERT_NEAR(testState2_.s<0>(),testScalar2_[0],1e-6);
  ASSERT_NEAR(testState2_.s<1>(),testScalar2_[1],1e-6);
  ASSERT_NEAR(testState2_.s<2>(),testScalar2_[2],1e-6);
  ASSERT_NEAR(testState2_.s<3>(),testScalar2_[3],1e-6);
  ASSERT_NEAR((testState2_.v<0>()-testVector2_[0]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState2_.v<1>()-testVector2_[1]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState2_.v<2>()-testVector2_[2]).norm(),0.0,1e-6);
  ASSERT_TRUE(testState2_.q<0>().isNear(testQuat2_[0],1e-6));
  ASSERT_TRUE(testState2_.q<1>().isNear(testQuat2_[1],1e-6));
  ASSERT_EQ(testState2_.aux().x_,testState1_.aux().x_);
}

// Test getValue, getId, and auxillary accessor
TEST_F(StateTesting2, accessors) {
  ASSERT_TRUE(testState1_.getValue<s0>() == testScalar1_[0]);
  ASSERT_TRUE(testState1_.getValue<s1>() == testScalar1_[1]);
  ASSERT_TRUE(testState1_.getValue<s2>() == testScalar1_[2]);
  ASSERT_TRUE(testState1_.getValue<s3>() == testScalar1_[3]);
  ASSERT_NEAR((testState1_.getValue<v0>()-testVector1_[0]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState1_.getValue<v1>()-testVector1_[1]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState1_.getValue<v2>()-testVector1_[2]).norm(),0.0,1e-6);
  ASSERT_TRUE(testState1_.getValue<q0>().isNear(testQuat1_[0],1e-6));
  ASSERT_TRUE(testState1_.getValue<q1>().isNear(testQuat1_[1],1e-6));

  ASSERT_TRUE(testState1_.getId<s0>() == 0);
  ASSERT_TRUE(testState1_.getId<s1>() == 1);
  ASSERT_TRUE(testState1_.getId<s2>() == 2);
  ASSERT_TRUE(testState1_.getId<s3>() == 3);
  ASSERT_TRUE(testState1_.getId<v0>() == 4);
  ASSERT_TRUE(testState1_.getId<v1>() == 7);
  ASSERT_TRUE(testState1_.getId<v2>() == 10);
  ASSERT_TRUE(testState1_.getId<q0>() == 13);
  ASSERT_TRUE(testState1_.getId<q1>() == 16);

  ASSERT_EQ(testState1_.aux().x_,2.3);
}

// Test operator=
TEST_F(StateTesting2, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_TRUE(testState2_.getValue<s0>() == testScalar1_[0]);
  ASSERT_TRUE(testState2_.getValue<s1>() == testScalar1_[1]);
  ASSERT_TRUE(testState2_.getValue<s2>() == testScalar1_[2]);
  ASSERT_TRUE(testState2_.getValue<s3>() == testScalar1_[3]);
  ASSERT_NEAR((testState2_.getValue<v0>()-testVector1_[0]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState2_.getValue<v1>()-testVector1_[1]).norm(),0.0,1e-6);
  ASSERT_NEAR((testState2_.getValue<v2>()-testVector1_[2]).norm(),0.0,1e-6);
  ASSERT_TRUE(testState2_.getValue<q0>().isNear(testQuat1_[0],1e-6));
  ASSERT_TRUE(testState2_.getValue<q1>().isNear(testQuat1_[1],1e-6));
  ASSERT_EQ(testState2_.aux().x_,testState1_.aux().x_);
}

// Test createDefaultNames
TEST_F(StateTesting2, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.name_ == "test");
  ASSERT_TRUE(std::get<s0>(testState1_.mStates_).name_ == "test_0");
  ASSERT_TRUE(std::get<s1>(testState1_.mStates_).name_ == "test_1");
  ASSERT_TRUE(std::get<s2>(testState1_.mStates_).name_ == "test_2");
  ASSERT_TRUE(std::get<s3>(testState1_.mStates_).name_ == "test_3");
  ASSERT_TRUE(std::get<v0>(testState1_.mStates_).name_ == "test_4");
  ASSERT_TRUE(std::get<v1>(testState1_.mStates_).name_ == "test_5");
  ASSERT_TRUE(std::get<v2>(testState1_.mStates_).name_ == "test_6");
  ASSERT_TRUE(std::get<q0>(testState1_.mStates_).name_ == "test_7");
  ASSERT_TRUE(std::get<q1>(testState1_.mStates_).name_ == "test_8");

//  TODO
  LWF::ArrayElement<LWF::ScalarElement,4> test;
  test.get(0) = 4.3;
  test.get(1) = 1.3;
  test.get(2) = 2.3;
  test.get(3) = 3.3;
  test.print();

  LWF::State<LWF::TH_multiple_elements<LWF::ScalarElement,0>,LWF::TH_multiple_elements<LWF::QuaternionState,3>,LWF::ScalarElement> test2;
//  std::get<0>(test2.tuple) = 5;
//  std::get<1>(test2.tuple) = 5.2;
//  std::get<2>(test2.tuple) = 3;
  std::cout << test2.D_ << std::endl;
}

// Test ZeroArray
TEST_F(StateTesting2, ZeroArray) {
  LWF::StateArray<LWF::ScalarState,0> testState1;
}

// Test Constness
TEST_F(StateTesting2, Constness) {
  const StateSVQAugmented testState1(testState1_);
  std::cout << testState1.getValue<q1>() << std::endl;
}











// The fixture for testing class ScalarState
class ScalarElementTest : public virtual ::testing::Test {
 protected:
  ScalarElementTest() {
    unsigned int s = 1;
    testElement1_.setRandom(s);
    testElement2_.setRandom(s);
  }
  virtual ~ScalarElementTest() {
  }
  LWF::ScalarElement testElement1_;
  LWF::ScalarElement testElement2_;
  LWF::ScalarElement::mtDifVec difVec_;
};

// Test constructors
TEST_F(ScalarElementTest, constructor) {
  LWF::ScalarElement testElement1;
}

// Test setIdentity and Identity
TEST_F(ScalarElementTest, setIdentity) {
  testElement1_.setIdentity();
  ASSERT_EQ(testElement1_.s_,0.0);
  ASSERT_EQ(LWF::ScalarElement::Identity().s_,0.0);
}

// Test plus and minus
TEST_F(ScalarElementTest, plusAndMinus) {
  testElement2_.boxMinus(testElement1_,difVec_);
  ASSERT_EQ(difVec_(0),testElement2_.s_-testElement1_.s_);
  LWF::ScalarElement testElement3;
  testElement1_.boxPlus(difVec_,testElement3);
  ASSERT_NEAR(testElement2_.s_,testElement3.s_,1e-6);
}

// Test getValue
TEST_F(ScalarElementTest, accessors) {
  ASSERT_TRUE(testElement1_.get() == testElement1_.s_);
}

// Test operator=
TEST_F(ScalarElementTest, operatorEQ) {
  testElement2_ = testElement1_;
  ASSERT_NEAR(testElement2_.s_,testElement1_.s_,1e-6);
}

// The fixture for testing class VectorState
class VectorElementTest : public virtual ::testing::Test {
 protected:
  VectorElementTest() {
    unsigned int s = 1;
    testElement1_.setRandom(s);
    testElement2_.setRandom(s);
  }
  virtual ~VectorElementTest() {
  }
  static const unsigned int N_ = 4;
  LWF::VectorElement<N_> testElement1_;
  LWF::VectorElement<N_> testElement2_;
  LWF::VectorElement<N_>::mtDifVec difVec_;
};

// Test constructors
TEST_F(VectorElementTest, constructor) {
  LWF::VectorElement<N_> testElement1;
}

// Test setIdentity and Identity
TEST_F(VectorElementTest, setIdentity) {
  testElement1_.setIdentity();
  ASSERT_EQ(testElement1_.v_.norm(),0.0);
  ASSERT_EQ(LWF::VectorElement<N_>::Identity().v_.norm(),0.0);
}

// Test plus and minus
TEST_F(VectorElementTest, plusAndMinus) {
  testElement2_.boxMinus(testElement1_,difVec_);
  ASSERT_NEAR((difVec_-(testElement2_.v_-testElement1_.v_)).norm(),0.0,1e-6);
  LWF::VectorElement<N_> testElement3;
  testElement1_.boxPlus(difVec_,testElement3);
  ASSERT_NEAR((testElement2_.v_-testElement3.v_).norm(),0.0,1e-6);
}

// Test getValue, getId
TEST_F(VectorElementTest, accessors) {
  ASSERT_TRUE(testElement1_.get() == testElement1_.v_);
}

// Test operator=
TEST_F(VectorElementTest, operatorEQ) {
  testElement2_ = testElement1_;
  ASSERT_NEAR((testElement2_.v_-testElement1_.v_).norm(),0.0,1e-6);
}

// The fixture for testing class QuaternionElementTest
class QuaternionElementTest : public virtual ::testing::Test {
 protected:
  QuaternionElementTest() {
    unsigned int s = 1;
    testElement1_.setRandom(s);
    testElement2_.setRandom(s);
  }
  virtual ~QuaternionElementTest() {
  }
  LWF::QuaternionElement testElement1_;
  LWF::QuaternionElement testElement2_;
  LWF::QuaternionElement::mtDifVec difVec_;
};

// Test constructors
TEST_F(QuaternionElementTest, constructor) {
  LWF::QuaternionElement testElement1;
}

// Test setIdentity and Identity
TEST_F(QuaternionElementTest, setIdentity) {
  testElement1_.setIdentity();
  ASSERT_TRUE(testElement1_.q_.isNear(rot::RotationQuaternionPD(),1e-6));
  ASSERT_TRUE(LWF::QuaternionElement::Identity().q_.isNear(rot::RotationQuaternionPD(),1e-6));
}

// Test plus and minus
TEST_F(QuaternionElementTest, plusAndMinus) {
  testElement2_.boxMinus(testElement1_,difVec_);
  ASSERT_NEAR((difVec_-testElement2_.q_.boxMinus(testElement1_.q_)).norm(),0.0,1e-6);
  LWF::QuaternionElement testElement3;
  testElement1_.boxPlus(difVec_,testElement3);
  ASSERT_TRUE(testElement2_.q_.isNear(testElement3.q_,1e-6));
}

// Test getValue, getId
TEST_F(QuaternionElementTest, accessors) {
  ASSERT_TRUE(testElement1_.get().isNear(testElement1_.q_,1e-6));
}

// Test operator=
TEST_F(QuaternionElementTest, operatorEQ) {
  testElement2_ = testElement1_;
  ASSERT_TRUE(testElement2_.q_.isNear(testElement1_.q_,1e-6));
}

// Test LMat
TEST_F(QuaternionElementTest, LMat) {
  double d = 0.00001;
  LWF::QuaternionElement att;
  LWF::VectorElement<3> vec;
  vec.v_ = Eigen::Vector3d(0.4,-0.2,1.7);
  Eigen::Matrix3d J;
  LWF::QuaternionElement attDisturbed;
  LWF::VectorElement<3> vecDisturbed;
  Eigen::Matrix3d I;
  I.setIdentity();
  Eigen::Vector3d dif;
  I = d*I;
  att.q_ = att.q_.exponentialMap(vec.v_);
  for(unsigned int i=0;i<3;i++){
    vec.boxPlus(I.col(i),vecDisturbed);
    attDisturbed.q_ = attDisturbed.q_.exponentialMap(vecDisturbed.v_);
    attDisturbed.boxMinus(att,dif);
    J.col(i) = dif*1/d;
  }
  ASSERT_NEAR((J-LWF::Lmat(vec.v_)).norm(),0.0,1e-5);
}

// The fixture for testing class NormalVectorElementTest
class NormalVectorElementTest : public virtual ::testing::Test {
 protected:
  NormalVectorElementTest() {
    unsigned int s = 1;
    testElement1_.setRandom(s);
    testElement2_.setRandom(s);
  }
  virtual ~NormalVectorElementTest() {
  }
  LWF::NormalVectorElement testElement1_;
  LWF::NormalVectorElement testElement2_;
  LWF::NormalVectorElement::mtDifVec difVec_;
};

// Test constructors
TEST_F(NormalVectorElementTest, constructor) {
  LWF::NormalVectorElement testElement1;
}

// Test setIdentity and Identity
TEST_F(NormalVectorElementTest, setIdentity) {
  testElement1_.setIdentity();
  ASSERT_TRUE(testElement1_.n_ == Eigen::Vector3d(1,0,0));
  ASSERT_TRUE(LWF::NormalVectorElement::Identity().n_ == Eigen::Vector3d(1,0,0));
}

// Test plus and minus
TEST_F(NormalVectorElementTest, plusAndMinus) {
  testElement2_.boxMinus(testElement1_,difVec_);
  LWF::NormalVectorElement testElement3;
  testElement1_.boxPlus(difVec_,testElement3);
  ASSERT_NEAR((testElement2_.n_-testElement3.n_).norm(),0.0,1e-6);
}

// Test getValue, getId
TEST_F(NormalVectorElementTest, accessors) {
  ASSERT_TRUE(testElement1_.get() == testElement1_.n_);
}

// Test operator=
TEST_F(NormalVectorElementTest, operatorEQ) {
  testElement2_ = testElement1_;
  ASSERT_TRUE(testElement2_.n_ == testElement1_.n_);
}

// Test getTwoNormals
TEST_F(NormalVectorElementTest, getTwoNormals) {
  Eigen::Vector3d m0;
  Eigen::Vector3d m1;
  testElement1_.getTwoNormals(m0,m1);
  ASSERT_NEAR(m0.dot(testElement1_.n_),0.0,1e-6);
  ASSERT_NEAR(m1.dot(testElement1_.n_),0.0,1e-6);
}

// Test derivative of boxplus
TEST_F(NormalVectorElementTest, derivative) {
  const double d  = 1e-6;
  Eigen::Vector3d m0;
  Eigen::Vector3d m1;
  testElement1_.getTwoNormals(m0,m1);
  difVec_.setZero();
  difVec_(0) = d;
  testElement1_.boxPlus(difVec_,testElement2_);
  ASSERT_NEAR(((testElement2_.n_-testElement1_.n_)/d-(-m1)).norm(),0.0,1e-6);
  difVec_.setZero();
  difVec_(1) = d;
  testElement1_.boxPlus(difVec_,testElement2_);
  ASSERT_NEAR(((testElement2_.n_-testElement1_.n_)/d-m0).norm(),0.0,1e-6);
}

// The fixture for testing class ArrayElementTest
class ArrayElementTest : public virtual ::testing::Test {
 protected:
  ArrayElementTest() {
    unsigned int s = 1;
    testElement1_.setRandom(s);
    testElement2_.setRandom(s);
  }
  virtual ~ArrayElementTest() {
  }
  static const unsigned int N_ = 5;
  LWF::ArrayElement<LWF::QuaternionElement,N_> testElement1_;
  LWF::ArrayElement<LWF::QuaternionElement,N_> testElement2_;
  LWF::ArrayElement<LWF::QuaternionElement,N_>::mtDifVec difVec_;
};

// Test constructors
TEST_F(ArrayElementTest, constructor) {
  LWF::ArrayElement<LWF::QuaternionElement,N_> testElement1;
}

// Test setIdentity and Identity
TEST_F(ArrayElementTest, setIdentity) {
  testElement1_.setIdentity();
  for(unsigned int i=0;i<N_;i++){
    ASSERT_TRUE(testElement1_.array_[i].q_.isNear(rot::RotationQuaternionPD(),1e-6));
    ASSERT_TRUE((LWF::ArrayElement<LWF::QuaternionElement,N_>::Identity().array_[i].q_.isNear(rot::RotationQuaternionPD(),1e-6)));
  }
}

// Test plus and minus
TEST_F(ArrayElementTest, plusAndMinus) {
  testElement2_.boxMinus(testElement1_,difVec_);
  for(unsigned int i=0;i<N_;i++){
    ASSERT_NEAR((difVec_.block<3,1>(i*3,0)-testElement2_.array_[i].q_.boxMinus(testElement1_.array_[i].q_)).norm(),0.0,1e-6);
  }
  LWF::ArrayElement<LWF::QuaternionElement,N_> testElement3;
  testElement1_.boxPlus(difVec_,testElement3);
  for(unsigned int i=0;i<N_;i++){
    ASSERT_TRUE(testElement2_.array_[i].q_.isNear(testElement3.array_[i].q_,1e-6));
  }
}

// Test getValue, getId
TEST_F(ArrayElementTest, accessors) {
  for(unsigned int i=0;i<N_;i++){
    ASSERT_TRUE(testElement1_.get(i).isNear(testElement1_.array_[i].q_,1e-6));
  }
}

// Test operator=
TEST_F(ArrayElementTest, operatorEQ) {
  testElement2_ = testElement1_;
  for(unsigned int i=0;i<N_;i++){
    ASSERT_TRUE(testElement2_.array_[i].q_.isNear(testElement1_.array_[i].q_,1e-6));
  }
}

class AuxillaryElement: public LWF::AuxiliaryBase<AuxillaryElement>{
 public:
  AuxillaryElement(){
    x_ = 1.0;
  };
  ~AuxillaryElement(){};
  double x_;
};

// The fixture for testing class StateSVQ
class StateTesting3 : public virtual ::testing::Test { // TODO rename
 protected:
  static const unsigned int _sca = 0;
  static const unsigned int _vec0 = _sca+1;
  static const unsigned int _vec1 = _vec0+1;
  static const unsigned int _vec2 = _vec1+1;
  static const unsigned int _vec3 = _vec2+1;
  static const unsigned int _qua0 = _vec3+1;
  static const unsigned int _qua1 = _qua0+1;
  static const unsigned int _aux = _qua1+1;
  StateTesting3() {
    testScalar1_ = 4.5;
    testScalar2_ = -17.34;
    testVector1_[0] << 2.1, -0.2, -1.9;
    testVector2_[0] << -10.6, 0.2, -105.2;
    for(int i=1;i<4;i++){
      testVector1_[i] = testVector1_[i-1] + Eigen::Vector3d(0.3,10.9,2.3);
      testVector2_[i] = testVector2_[i-1] + Eigen::Vector3d(-1.5,12,1785.23);
    }
    testQuat1_[0] = rot::RotationQuaternionPD(4.0/sqrt(30.0),3.0/sqrt(30.0),1.0/sqrt(30.0),2.0/sqrt(30.0));
    testQuat2_[0] = rot::RotationQuaternionPD(0.0,0.36,0.48,0.8);
    for(int i=1;i<4;i++){
      testQuat1_[i] = testQuat1_[i-1].boxPlus(testVector1_[i-1]);
      testQuat2_[i] = testQuat2_[i-1].boxPlus(testVector2_[i-1]);
    }
    testState1_.get<_sca>() = testScalar1_;
    testState1_.get<_vec0>() = testVector1_[0];
    testState1_.get<_vec1>() = testVector1_[1];
    testState1_.get<_vec2>() = testVector1_[2];
    testState1_.get<_vec3>() = testVector1_[3];
    testState1_.get<_qua0>(0) = testQuat1_[0];
    testState1_.get<_qua0>(1) = testQuat1_[1];
    testState1_.get<_qua1>(0) = testQuat1_[2];
    testState1_.get<_qua1>(1) = testQuat1_[3];
    testState1_.get<_aux>().x_ = 2.3;
    testState2_.get<_sca>() = testScalar2_;
    testState2_.get<_vec0>() = testVector2_[0];
    testState2_.get<_vec1>() = testVector2_[1];
    testState2_.get<_vec2>() = testVector2_[2];
    testState2_.get<_vec3>() = testVector2_[3];
    testState2_.get<_qua0>(0) = testQuat2_[0];
    testState2_.get<_qua0>(1) = testQuat2_[1];
    testState2_.get<_qua1>(0) = testQuat2_[2];
    testState2_.get<_qua1>(1) = testQuat2_[3];
    testState2_.get<_aux>().x_ = 3.2;
  }
  virtual ~StateTesting3() {
  }
  typedef LWF::State<
      LWF::ScalarElement,
      LWF::TH_multiple_elements<LWF::VectorElement<3>,4>,
      LWF::TH_multiple_elements<LWF::ArrayElement<LWF::QuaternionElement,2>,2>,
      AuxillaryElement> mtState;
  mtState testState1_;
  mtState testState2_;
  mtState::mtDifVec difVec_;
  double testScalar1_;
  double testScalar2_;
  Eigen::Vector3d testVector1_[4];
  Eigen::Vector3d testVector2_[4];
  rot::RotationQuaternionPD testQuat1_[4];
  rot::RotationQuaternionPD testQuat2_[4];
};

// Test constructors
TEST_F(StateTesting3, constructors) {
  mtState testState1;
  ASSERT_EQ(testState1.get<_aux>().x_,1.0);
  mtState testState2(testState2_);
  testState2.boxMinus(testState2_,difVec_);
  ASSERT_NEAR(difVec_.norm(),0.0,1e-6);
  ASSERT_EQ(testState2.get<_aux>().x_,3.2);
}

// Test setIdentity and Identity
TEST_F(StateTesting3, setIdentity) {
  testState1_.setIdentity();
  ASSERT_EQ(testState1_.get<_sca>(),0);
  ASSERT_EQ(testState1_.get<_vec0>().norm(),0);
  ASSERT_EQ(testState1_.get<_vec1>().norm(),0);
  ASSERT_EQ(testState1_.get<_vec2>().norm(),0);
  ASSERT_EQ(testState1_.get<_vec3>().norm(),0);
  ASSERT_EQ(testState1_.get<_qua0>(0).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(testState1_.get<_qua0>(1).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(testState1_.get<_qua1>(0).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(testState1_.get<_qua1>(1).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(testState1_.get<_aux>().x_,2.3);
  ASSERT_EQ(mtState::Identity().get<_sca>(),0);
  ASSERT_EQ(mtState::Identity().get<_vec0>().norm(),0);
  ASSERT_EQ(mtState::Identity().get<_vec1>().norm(),0);
  ASSERT_EQ(mtState::Identity().get<_vec2>().norm(),0);
  ASSERT_EQ(mtState::Identity().get<_vec3>().norm(),0);
  ASSERT_EQ(mtState::Identity().get<_qua0>(0).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(mtState::Identity().get<_qua0>(1).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(mtState::Identity().get<_qua1>(0).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(mtState::Identity().get<_qua1>(1).boxMinus(rot::RotationQuaternionPD()).norm(),0.0);
  ASSERT_EQ(mtState::Identity().get<_aux>().x_,1.0);
}

// Test plus and minus
TEST_F(StateTesting3, plusAndMinus) {
  testState2_.boxMinus(testState1_,difVec_);
  unsigned int index=0;
  ASSERT_EQ(difVec_(index),testScalar2_-testScalar1_);
  index ++;
  for(int i=0;i<4;i++){
    ASSERT_EQ((difVec_.block<3,1>(index,0)-(testVector2_[i]-testVector1_[i])).norm(),0);
    index = index + 3;
  }
  for(int i=0;i<4;i++){
    ASSERT_EQ((difVec_.block<3,1>(index,0)-testQuat2_[i].boxMinus(testQuat1_[i])).norm(),0);
    index = index + 3;
  }
  testState1_.boxPlus(difVec_,testState2_);
  ASSERT_NEAR(testState2_.get<_sca>(),testScalar2_,1e-10);
  ASSERT_NEAR((testState2_.get<_vec0>()-testVector2_[0]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec1>()-testVector2_[1]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec2>()-testVector2_[2]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec3>()-testVector2_[3]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua0>(0).boxMinus(testQuat2_[0]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua0>(1).boxMinus(testQuat2_[1]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua1>(0).boxMinus(testQuat2_[2]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua1>(1).boxMinus(testQuat2_[3]).norm(),0,1e-10);
  ASSERT_EQ(testState2_.get<_aux>().x_,testState1_.get<_aux>().x_);
}

// Test getValue, getId
TEST_F(StateTesting3, accessors) {
  ASSERT_NEAR(testState1_.get<_sca>(),testScalar1_,1e-10);
  ASSERT_NEAR((testState1_.get<_vec0>()-testVector1_[0]).norm(),0,1e-10);
  ASSERT_NEAR((testState1_.get<_vec1>()-testVector1_[1]).norm(),0,1e-10);
  ASSERT_NEAR((testState1_.get<_vec2>()-testVector1_[2]).norm(),0,1e-10);
  ASSERT_NEAR((testState1_.get<_vec3>()-testVector1_[3]).norm(),0,1e-10);
  ASSERT_NEAR(testState1_.get<_qua0>(0).boxMinus(testQuat1_[0]).norm(),0,1e-10);
  ASSERT_NEAR(testState1_.get<_qua0>(1).boxMinus(testQuat1_[1]).norm(),0,1e-10);
  ASSERT_NEAR(testState1_.get<_qua1>(0).boxMinus(testQuat1_[2]).norm(),0,1e-10);
  ASSERT_NEAR(testState1_.get<_qua1>(1).boxMinus(testQuat1_[3]).norm(),0,1e-10);
  ASSERT_EQ(testState1_.get<_aux>().x_,2.3);

  ASSERT_TRUE(testState1_.getId<_sca>() == 0);
  ASSERT_TRUE(testState1_.getId<_vec0>() == 1);
  ASSERT_TRUE(testState1_.getId<_vec1>() == 4);
  ASSERT_TRUE(testState1_.getId<_vec2>() == 7);
  ASSERT_TRUE(testState1_.getId<_vec3>() == 10);
  ASSERT_TRUE(testState1_.getId<_qua0>() == 13);
  ASSERT_TRUE(testState1_.getId<_qua1>() == 19);
  ASSERT_TRUE(testState1_.getId<_aux>() == 25);
}

// Test operator=
TEST_F(StateTesting3, operatorEQ) {
  testState2_ = testState1_;
  ASSERT_NEAR(testState2_.get<_sca>(),testScalar1_,1e-10);
  ASSERT_NEAR((testState2_.get<_vec0>()-testVector1_[0]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec1>()-testVector1_[1]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec2>()-testVector1_[2]).norm(),0,1e-10);
  ASSERT_NEAR((testState2_.get<_vec3>()-testVector1_[3]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua0>(0).boxMinus(testQuat1_[0]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua0>(1).boxMinus(testQuat1_[1]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua1>(0).boxMinus(testQuat1_[2]).norm(),0,1e-10);
  ASSERT_NEAR(testState2_.get<_qua1>(1).boxMinus(testQuat1_[3]).norm(),0,1e-10);
  ASSERT_EQ(testState2_.get<_aux>().x_,2.3);
}

// Test createDefaultNames
TEST_F(StateTesting3, naming) {
  testState1_.createDefaultNames("test");
  ASSERT_TRUE(testState1_.getName<_sca>() == "test_0");
  ASSERT_TRUE(testState1_.getName<_vec0>() == "test_1");
  ASSERT_TRUE(testState1_.getName<_vec1>() == "test_2");
  ASSERT_TRUE(testState1_.getName<_vec2>() == "test_3");
  ASSERT_TRUE(testState1_.getName<_vec3>() == "test_4");
  ASSERT_TRUE(testState1_.getName<_qua0>() == "test_5");
  ASSERT_TRUE(testState1_.getName<_qua1>() == "test_6");
  ASSERT_TRUE(testState1_.getName<_aux>() == "test_7");
}

// Test ZeroArray
TEST_F(StateTesting3, ZeroArray) {
  LWF::State<LWF::TH_multiple_elements<LWF::ScalarElement,0>,LWF::QuaternionElement> testState1;
  ASSERT_EQ(std::tuple_size<decltype(testState1.mElements_)>::value,1);
}

// Test Constness
TEST_F(StateTesting3, Constness) {
  const mtState testState1(testState1_);
  ASSERT_NEAR(testState1.get<_qua0>(0).boxMinus(testQuat1_[0]).norm(),0,1e-10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
