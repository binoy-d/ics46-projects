#include "gtest/gtest.h"
#include "proj0.hpp"
#include <map>
#include <string>

namespace{

TEST(VerifySolution, First){
    std::string s1 = "POT";
    std::string s2 = "PAN";
    std::string s3 = "BIB";

    std::map<char, unsigned> solution = { {'A', 7}, {'B', 5}, 
        {'I', 0}, {'N', 4}, {'O', 3}, {'P', 2}, {'T', 1}
    };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
}

TEST(VerifySolution, Second){

    std::string s1 = "CAT";
    std::string s2 = "DOG";
    std::string s3 = "PIG";

    std::map<char, unsigned> solution = { {'A', 5}, {'C', 2}, {'D', 1}, {'G', 6}, {'I', 9}, {'O', 4}, {'P', 3}, {'T', 0} };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
} // end test two

TEST(VerifySolution, Third){

    std::string s1 = "CAT";
    std::string s2 = "DOG";
    std::string s3 = "PII";

    std::map<char, unsigned> solution = { {'A', 5}, {'C', 2}, {'D', 1}, {'G', 6}, {'I', 9}, {'O', 4}, {'P', 3}, {'T', 0} };

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
}


TEST(VerifySolution, Fourth){

    std::string s1 = "CAT";
    std::string s2 = "DOG";
    std::string s3 = "PIG";

    std::map<char, unsigned> solution = { {'A', 5}, {'C', 8}, {'D', 1}, {'G', 7}, {'I', 9}, {'O', 4}, {'P', 3}, {'T', 0} };

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
}


TEST(VerifySolution, ShortInput){

    std::string s1 = "BC";
    std::string s2 = "DEF";
    std::string s3 = "EBA";

    std::map<char, unsigned> solution = { {'A', 0}, {'B', 2}, {'C', 3}, {'F', 7}, {'D', 8}, {'E', 9}};

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );

    solution = { {'A', 1}, {'B', 2}, {'C', 3}, {'F', 7}, {'D', 8}, {'E', 9}};

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
}

TEST(VerifySolution, LongResult){

    std::string s1 = "CC";
    std::string s2 = "CC";
    std::string s3 = "ACB";

    std::map<char, unsigned> solution = { {'A', 1}, {'B', 8}, {'C', 9}};

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );


    solution = { {'A', 2}, {'B', 8}, {'C', 9}};
    

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
}


TEST(VerifySolution, SingleDigitDoubleResult){

    std::string s1 = "A";
    std::string s2 = "B";
    std::string s3 = "CD";

    std::map<char, unsigned> solution = { {'A', 7}, {'B', 8}, {'C', 1}, {'D', 5}};

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );

    solution = { {'A', 7}, {'B', 8}, {'C', 0}, {'D', 5}};
    

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
}

TEST(VerifySolution, EmptyStrings){

    std::string s1 = "";
    std::string s2 = "B";
    std::string s3 = "B";

    std::map<char, unsigned> solution = {{'B', 8}};

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );

    s1 = "B";
    s2 = "";
    s3 = "B";
    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );

    s1 = "";
    s2 = "";
    s3 = "";
    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );

    s1 = "";
    s2 = "";
    s3 = "B";
    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );


    s1 = "B";
    s2 = "";
    s3 = "";
    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
    
}




} // end namespace
TEST(VerifySolution, LongerAdditionAndEdges){

    std::map<char, unsigned> solution = { {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'L', 9}, {'M', 0} };

    EXPECT_TRUE( verifySolution( "ABCD", "DCBA", "EEEE", solution ) );
    EXPECT_TRUE( verifySolution( "EFAHL", "DEHB", "FMGGA", solution ) );
    EXPECT_FALSE( verifySolution( "EFAHL", "DFHB", "FMGGA", solution ) );
    EXPECT_TRUE( verifySolution( "EFAHL", "M", "EFAHL", solution ) );
    EXPECT_FALSE( verifySolution( "EFAHL", "M", "FFAHL", solution ) );
    EXPECT_FALSE( verifySolution( "DMC", "MB", "E", solution ) );
    EXPECT_FALSE( verifySolution( "DC", "", "MM", solution ) );
    EXPECT_TRUE( verifySolution( "DC", "", "DC", solution ) );
    EXPECT_TRUE( verifySolution( "M", "", "MMM", solution ) );
    EXPECT_TRUE( verifySolution( "MD", "DMM", "MDMD", solution ) );

    EXPECT_TRUE( verifySolution( "FLDBM", "DBMFL", "AAADHL", solution ) );
    EXPECT_TRUE( verifySolution( "FLDBM", "DBMFL", "MAAADHL", solution ) );
    EXPECT_TRUE( verifySolution( "FLDBM", "DBMFL", "MMMMMAAADHL", solution ) );
    EXPECT_FALSE( verifySolution( "FLDBM", "DBMFL", "DMMMMAAADHL", solution ) );
    EXPECT_FALSE( verifySolution( "FLDBM", "DBMFL", "LAADHL", solution ) );
    EXPECT_FALSE( verifySolution( "FLDBM", "DBMFL", "MAADHL", solution ) );
    EXPECT_FALSE( verifySolution( "FLDBM", "EBMFL", "MAADHL", solution ) );


    //big boi time
    EXPECT_TRUE( verifySolution( "ABCDEFGHLMABCDEFGHLM", "ABCDEFDEFHHHLLLMABCD", "BDFLACBDELMACDDFLABD", solution ) );
    EXPECT_FALSE( verifySolution( "BBCDEFGHLMABCDEFGHLM", "ABCDEFDEFHHHLLLMABCD", "BDFLACBDELMACDDFLABD", solution ) );
    EXPECT_FALSE( verifySolution( "BBCDEFGMMDEFGHLM", "ABCDEFDEFHHHLLLMABCD", "BDFLACBDELMACDDFLABD", solution ) );
}