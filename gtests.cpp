#include <gtest/gtest.h>
#include "complex.h"
#include "complexSet.h"

TEST(ComplexTest, DefaultConstructor){
    Complex c;
    EXPECT_TRUE(c == Complex(0, 0));
}

TEST(ComplexTest, Constructors){
    EXPECT_TRUE(Complex(3) == Complex(3, 0));
    EXPECT_TRUE(Complex(2, 4) == Complex(2, 4));
}

TEST(ComplexTest, CopyConstructor){
    Complex a(2, 4);
    Complex b(a);

    EXPECT_TRUE(a == b);
}

TEST(ComplexTest, Assignment){
    Complex a(2, 4);
    Complex b;

    b = a;

    EXPECT_TRUE(a == b);
}

TEST(ComplexTest, Equality){
    EXPECT_TRUE(Complex(2, 4) == Complex(2, 4));
    EXPECT_FALSE(Complex(2, 4) == Complex(2, 5));
}

TEST(ComplexTest, Ordering){
    EXPECT_TRUE(Complex(1, 5) < Complex(2, 0));
    EXPECT_TRUE(Complex(2, 3) < Complex(2, 4));
    EXPECT_TRUE(Complex(3, 0) > Complex(2, 100));
}

TEST(ComplexSetTest, DefaultConstructor){
    ComplexSet set;

    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.size(), 0);
}

TEST(ComplexSetTest, AddElements){
    ComplexSet set;

    EXPECT_TRUE(set.add(Complex(3, 0)));
    EXPECT_TRUE(set.add(Complex(1, 0)));
    EXPECT_TRUE(set.add(Complex(2, 0)));

    EXPECT_EQ(set.size(), 3);
}

TEST(ComplexSetTest, AddDuplicate){
    ComplexSet set;

    EXPECT_TRUE(set.add(Complex(1, 2)));
    EXPECT_FALSE(set.add(Complex(1, 2)));

    EXPECT_EQ(set.size(), 1);
}

TEST(ComplexSetTest, Contains){
    ComplexSet set;

    set.add(Complex(1, 0));
    set.add(Complex(2, 0));

    EXPECT_TRUE(set.contains(Complex(1, 0)));
    EXPECT_TRUE(set.contains(Complex(2, 0)));
    EXPECT_FALSE(set.contains(Complex(3, 0)));
}

TEST(ComplexSetTest, FunctionCallOperator){
    ComplexSet set;
    set.add(Complex(1, 2));

    EXPECT_TRUE(set(Complex(1, 2)));
    EXPECT_FALSE(set(Complex(3, 4)));
}

TEST(ComplexSetTest, Remove){
    ComplexSet set;
    set.add(Complex(1, 0));
    set.add(Complex(2, 0));

    EXPECT_TRUE(set.remove(Complex(1, 0)));
    EXPECT_FALSE(set.remove(Complex(1, 0)));

    EXPECT_EQ(set.size(), 1);
    EXPECT_FALSE(set.contains(Complex(1, 0)));
}

TEST(ComplexSetTest, AddAndRemoveOperators){
    ComplexSet set;

    set += Complex(1, 0);
    EXPECT_TRUE(set.contains(Complex(1, 0)));

    set -= Complex(1, 0);
    EXPECT_FALSE(set.contains(Complex(1, 0)));
}

TEST(ComplexSetTest, CopyConstructor){
    ComplexSet a;
    a.add(Complex(1, 0));
    a.add(Complex(2, 0));

    ComplexSet b(a);

    EXPECT_TRUE(a == b);

    b.add(Complex(3, 0));

    EXPECT_NE(a.size(), b.size());
}

TEST(ComplexSetTest, CopyAssignment){
    ComplexSet a;
    a.add(Complex(1, 0));

    ComplexSet b;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(ComplexSetTest, MoveConstructor){
    ComplexSet a;
    a.add(Complex(1, 0));
    a.add(Complex(2, 0));

    ComplexSet b(std::move(a));

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 2);
    EXPECT_TRUE(b.contains(Complex(1, 0)));
}

TEST(ComplexSetTest, MoveAssignment){
    ComplexSet a;
    a.add(Complex(1, 0));

    ComplexSet b;
    b = std::move(a);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 1);
    EXPECT_TRUE(b.contains(Complex(1, 0)));
}

TEST(ComplexSetTest, Union){
    ComplexSet a;
    a.add(Complex(1, 0));
    a.add(Complex(2, 0));
    a.add(Complex(3, 0));

    ComplexSet b;
    b.add(Complex(2, 0));
    b.add(Complex(3, 0));
    b.add(Complex(4, 0));

    ComplexSet result = a | b;

    ComplexSet expected;
    expected.add(Complex(1, 0));
    expected.add(Complex(2, 0));
    expected.add(Complex(3, 0));
    expected.add(Complex(4, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, Intersection){
    ComplexSet a;
    a.add(Complex(1, 0));
    a.add(Complex(2, 0));
    a.add(Complex(3, 0));

    ComplexSet b;
    b.add(Complex(2, 0));
    b.add(Complex(3, 0));
    b.add(Complex(4, 0));

    ComplexSet result = a & b;

    ComplexSet expected;
    expected.add(Complex(2, 0));
    expected.add(Complex(3, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, Difference){
    ComplexSet a;
    a.add(Complex(1, 0));
    a.add(Complex(2, 0));
    a.add(Complex(3, 0));

    ComplexSet b;
    b.add(Complex(2, 0));
    b.add(Complex(3, 0));
    b.add(Complex(4, 0));

    ComplexSet result = a - b;

    ComplexSet expected;
    expected.add(Complex(1, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, EqualityAndInequality){
    ComplexSet a;
    a.add(Complex(1, 0));

    ComplexSet b;
    b.add(Complex(1, 0));

    ComplexSet c;
    c.add(Complex(2, 0));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(ComplexSetTest, OperationsWithEmptySet){
    ComplexSet a;
    a.add(Complex(1, 0));

    ComplexSet empty;

    EXPECT_TRUE((a | empty) == a);
    EXPECT_TRUE((a & empty).empty());
    EXPECT_TRUE((a - empty) == a);
    EXPECT_TRUE((empty - a).empty());
}
