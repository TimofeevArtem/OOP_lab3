#include <gtest/gtest.h>
#include "complex.h"
#include "complexSet.h"

TEST(ComplexTest, DefaultConstructor){
    Complex c;
    EXPECT_TRUE(c == complex(0, 0));
}

TEST(ComplexTest, Constructors){
    EXPECT_TRUE(complex(3) == complex(3, 0));
    EXPECT_TRUE(complex(2, 4) == complex(2, 4));
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
    EXPECT_TRUE(complex(2, 4) == complex(2, 4));
    EXPECT_FALSE(complex(2, 4) == complex(2, 5));
}

TEST(ComplexTest, Ordering){
    EXPECT_TRUE(complex(1, 5) < complex(2, 0));
    EXPECT_TRUE(complex(2, 3) < complex(2, 4));
    EXPECT_TRUE(complex(3, 0) > complex(2, 100));
}

TEST(ComplexSetTest, DefaultConstructor){
    ComplexSet set;

    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.size(), 0);
}

TEST(ComplexSetTest, AddElements){
    ComplexSet set;

    EXPECT_TRUE(set.add(complex(3, 0)));
    EXPECT_TRUE(set.add(complex(1, 0)));
    EXPECT_TRUE(set.add(complex(2, 0)));

    EXPECT_EQ(set.size(), 3);
}

TEST(ComplexSetTest, AddDuplicate){
    ComplexSet set;

    EXPECT_TRUE(set.add(complex(1, 2)));
    EXPECT_FALSE(set.add(complex(1, 2)));

    EXPECT_EQ(set.size(), 1);
}

TEST(ComplexSetTest, Contains){
    ComplexSet set;

    set.add(complex(1, 0));
    set.add(complex(2, 0));

    EXPECT_TRUE(set.contains(complex(1, 0)));
    EXPECT_TRUE(set.contains(complex(2, 0)));
    EXPECT_FALSE(set.contains(complex(3, 0)));
}

TEST(ComplexSetTest, FunctionCallOperator){
    ComplexSet set;
    set.add(complex(1, 2));

    EXPECT_TRUE(set(complex(1, 2)));
    EXPECT_FALSE(set(complex(3, 4)));
}

TEST(ComplexSetTest, Remove){
    ComplexSet set;
    set.add(complex(1, 0));
    set.add(complex(2, 0));

    EXPECT_TRUE(set.remove(complex(1, 0)));
    EXPECT_FALSE(set.remove(complex(1, 0)));

    EXPECT_EQ(set.size(), 1);
    EXPECT_FALSE(set.contains(complex(1, 0)));
}

TEST(ComplexSetTest, AddAndRemoveOperators){
    ComplexSet set;

    set += complex(1, 0);
    EXPECT_TRUE(set.contains(complex(1, 0)));

    set -= complex(1, 0);
    EXPECT_FALSE(set.contains(complex(1, 0)));
}

TEST(ComplexSetTest, CopyConstructor){
    ComplexSet a;
    a.add(complex(1, 0));
    a.add(complex(2, 0));

    ComplexSet b(a);

    EXPECT_TRUE(a == b);

    b.add(complex(3, 0));

    EXPECT_NE(a.size(), b.size());
}

TEST(ComplexSetTest, CopyAssignment){
    ComplexSet a;
    a.add(complex(1, 0));

    ComplexSet b;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(ComplexSetTest, MoveConstructor){
    ComplexSet a;
    a.add(complex(1, 0));
    a.add(complex(2, 0));

    ComplexSet b(std::move(a));

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 2);
    EXPECT_TRUE(b.contains(complex(1, 0)));
}

TEST(ComplexSetTest, MoveAssignment){
    ComplexSet a;
    a.add(complex(1, 0));

    ComplexSet b;
    b = std::move(a);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(b.size(), 1);
    EXPECT_TRUE(b.contains(complex(1, 0)));
}

TEST(ComplexSetTest, Union){
    ComplexSet a;
    a.add(complex(1, 0));
    a.add(complex(2, 0));
    a.add(complex(3, 0));

    ComplexSet b;
    b.add(complex(2, 0));
    b.add(complex(3, 0));
    b.add(complex(4, 0));

    ComplexSet result = a | b;

    ComplexSet expected;
    expected.add(complex(1, 0));
    expected.add(complex(2, 0));
    expected.add(complex(3, 0));
    expected.add(complex(4, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, Intersection){
    ComplexSet a;
    a.add(complex(1, 0));
    a.add(complex(2, 0));
    a.add(complex(3, 0));

    ComplexSet b;
    b.add(complex(2, 0));
    b.add(complex(3, 0));
    b.add(complex(4, 0));

    ComplexSet result = a & b;

    ComplexSet expected;
    expected.add(complex(2, 0));
    expected.add(complex(3, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, Difference){
    ComplexSet a;
    a.add(complex(1, 0));
    a.add(complex(2, 0));
    a.add(complex(3, 0));

    ComplexSet b;
    b.add(complex(2, 0));
    b.add(complex(3, 0));
    b.add(complex(4, 0));

    ComplexSet result = a - b;

    ComplexSet expected;
    expected.add(complex(1, 0));

    EXPECT_TRUE(result == expected);
}

TEST(ComplexSetTest, EqualityAndInequality){
    ComplexSet a;
    a.add(complex(1, 0));

    ComplexSet b;
    b.add(complex(1, 0));

    ComplexSet c;
    c.add(complex(2, 0));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
}

TEST(ComplexSetTest, OperationsWithEmptySet){
    ComplexSet a;
    a.add(complex(1, 0));

    ComplexSet empty;

    EXPECT_TRUE((a | empty) == a);
    EXPECT_TRUE((a & empty).empty());
    EXPECT_TRUE((a - empty) == a);
    EXPECT_TRUE((empty - a).empty());
}
