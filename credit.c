#include <stdio.h>
#include <cs50.h>

int returnLength(long creditNo);
int findCompany(int digits, long cardNo, bool valid);
bool checkSum(long longNumber, int digits);

int main(void)
{
    long inputLong = get_long("Number: ");
    int ccLength = returnLength(inputLong);
    bool isValid = checkSum(inputLong,ccLength);
    int ccCompany = findCompany (ccLength, inputLong, isValid);
    switch (ccCompany)                                      //print cc company
    {
        case 0: printf("INVALID\n");
                break;
        case 1: printf("VISA\n");
                break;
        case 2: printf("American Express\n");
                break;
        case 3: printf("Mastercard\n");
                break;
    }
}

int returnLength(long creditNo)
{
    int count = 0;
    while (creditNo > 0)
    {
        creditNo = creditNo / 10;
        count++;                                                        //count + 1 everytime creditcard no. / 10
    }
    return count;
}

int findCompany(int digits, long cardNo, bool valid)                    //0: invalid, 1: VISA, 2: AMEX, 3: Mastercard
{
    int company = 0;
    if (valid == true)                                          //uses checksum validity
    {
        if (digits == 13 || digits == 15 || digits == 16 )       //filter out card length
        {
            switch (digits)                                         //I can't be bothered to make a power function in c so yeah
            {
                case 13:    cardNo = cardNo / 1000000000000;            //VISA      10 ^ 12
                            if (cardNo == 4)
                            {
                                company = 1;
                            }
                            break;
                case 15:    cardNo = cardNo / 10000000000000;           //AMEX      10 ^ 13
                            if (cardNo == 34 || cardNo == 37)
                            {
                                company = 2;
                            }
                            break;
                case 16:    cardNo = cardNo / 100000000000000;          //check Mastercard or VISA      10 ^ 14
                            if (cardNo > 50 && cardNo < 56)
                            {
                                company = 3;                            //Mastercard
                            }
                            else if (cardNo / 10 == 4)
                            {
                                company = 1;                            //VISA
                            }
                            break;
            }
        }
    }
    return company;
}

bool checkSum(long longNumber, int digits)
{
    bool validity = false;                          //false by default
    int sum_a = 0, sum_b = 0;                       //sum a is 2 * even digits, sum b is odd digits
    long tempLong_b = longNumber;
    long tempLong_a = longNumber / 10;              //discard last digit of longNumber first

    for (int i = 0; i < digits; i = i + 2)          //summation of odd digits
    {
        sum_b = sum_b + (tempLong_b % 10);
        tempLong_b = tempLong_b / 100;              //throw away last 2 digits
    }

    for (int j = 0; j < digits; j = j + 2)          //summation of even digits * 2
    {
        int tempInt = 2 * (tempLong_a % 10);
        sum_a = sum_a + (tempInt / 10) + (tempInt % 10);        //even if the tempInt < 10, tempInt/10 will return 0
        tempLong_a = tempLong_a / 100;              //throw away last 2 digits
    }

    if ((sum_a + sum_b) % 10 == 0)
    {
        validity = true;
    }

    /* for (int i = digits; i > 1; i = i - 2)                  //for loop that uses the digit of the cc
    {
        sum = sum + longNumber / 10 % (10 ^ digits);        // e.g. if long = 103467,
    }
    printf("%i\n", sum);
    if (sum % 10 == 0)
    {
        validity = true;
    } */

    return validity;
}

