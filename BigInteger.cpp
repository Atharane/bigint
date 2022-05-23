#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#define DEBUG 1

class BigInteger
{

    /*
    Array 'arr_number' is used to store the digits of the actual number.
    the max value that each elements in the array can store is 10^19 -1 = 999999999999999999 or the biggest 18 digit number,
    because the max value of lon long int is 9223372036854775807 i.e 19 digits.
    During arithmetic on two 18 digit numbers, the result will be well within LLONG_MAX(max value of long long int)

    thus a number 1234888888888888888888999999999999999999 is stored as
    digits[2] = 999999999999999999  // last 18 digits
    digits[1] = 888888888888888888 // next-last 18 digits
    digits[0] = 1234 // reamaining digits

    1234 - 888888888888888888 - 999999999999999999

    len(arr_number) = 10
    thus the max value it can store is 10 ^ (18 * 10 + 1) - 1 or (10*18) times 9
    basically 10 elements holding 999999999999999999 each.

    The result is returned as a string formed by joining the elements of the array 'arr_number'
    arr_number = {0, 0, 0, 0, 0, 0, 0, 1234, 888888888888888888, 999999999999999999}
    result = "1234888888888888888888999999999999999999"
    */

    // actual number = number.join('')
    long long int arr_number[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int len_number = 0;

public:
    BigInteger(string s = "0")
    {
        if (s == "0") // skip if number is 0
            return;

        size_t len = s.length();
        size_t sz_arr_num = sizeof(arr_number) / sizeof(arr_number[0]);
        len_number = len; // setting the data member to length(s)

        if (len > sz_arr_num * 18)
        {
            cout << "Number too large to store !" << endl;
            return;
        }

        int idx = sz_arr_num - int((len - 1) / 18) - 1; // index of the array arr_number to be filled
        /* len: 18 maps to idx: (sz_arr_num - 1)
           len: 19 maps to idx: (sz_arr_num - 2)
           ...
           len: 180 maps to idx: 0 */

        int next = len % 18; // number of digits to store in arr_number[idx]
        if (next == 0)
            next = 18;

        int lower = 0;

        for (int i = idx; i < sz_arr_num; i++)

        {
            // Syntax: string substr (size_t pos, size_t len);
            // pos: Position of the first character to be copied. len: Length of the sub-string

            arr_number[i] = stoll(s.substr(lower, next));

            lower = lower + next; // update the lower index for the next iteration
            
            next = 18; // after the first remaining digits are stored, the default 'next' is 18
        }
    }

    // overload the + operator     
    BigInteger operator + (BigInteger const &obj) {
        BigInteger result;

        int carry = 0;

        int sz_arr_num = sizeof(arr_number) / sizeof(arr_number[0]);

        for (int i = sz_arr_num-1; i <= 0; i++){

            result.arr_number[i] = arr_number[i] + obj.arr_number[i] + carry;

            if (result.arr_number[i] >= 1000000000000000000){
                carry = 1;
                result.arr_number[i] = result.arr_number[i] - 1000000000000000000;
            }
        }

        if(carry){
            cout << "Overflow detected" << endl;
        }
        cout << "Result: " << result.getNumber() << endl;

        return result;

    }

    string getNumber()
    {
        string result = "";

        for (int i = 0; i < 10; i++)
        {
            cout << arr_number[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < 10; i++)
        {
            if (arr_number[i] == 0) // skip if zero
                continue;

            result = result + to_string(arr_number[i]);
        }
        return result;
    }
};

int main()
{
    BigInteger a("1234888888888888888888999999999999999999");

    BigInteger b("111111111111111111");

    return 0;
}