class Solution {
  public:

  string numberToWords(int num) {
      // base case
    if (num == 0)
      return "Zero";
      
    string result;
    std::vector < int > listOfChunks = toChunks(num);

    //filling from the back
    int back;
    if (!listOfChunks.empty()) {
      back = listOfChunks.back();
      if (back != 0)
        result = chunkToString(back);
      listOfChunks.pop_back();
    }
    if (!listOfChunks.empty()) {
      back = listOfChunks.back();
      if (back != 0)
        result = chunkToString(back) + " Thousand " + result;
      listOfChunks.pop_back();
    }
    if (!listOfChunks.empty()) {
      back = listOfChunks.back();
      if (back != 0)
        result = chunkToString(back) + " Million " + result;
      listOfChunks.pop_back();
    }
    if (!listOfChunks.empty()) {
      back = listOfChunks.back();
      result = chunkToString(back) + " Billion " + result;
      listOfChunks.pop_back();
    }

    return trim(result);
  }
  // helper trim
  // trim from start
  static inline std::string & ltrim(std::string & s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
      std::not1(std::ptr_fun < int, int > (std::isspace))));
    return s;
  }

  // trim from end
  static inline std::string & rtrim(std::string & s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
      std::not1(std::ptr_fun < int, int > (std::isspace))).base(), s.end());
    return s;
  }

  // trim from both ends
  static inline std::string & trim(std::string & s) {
    return ltrim(rtrim(s));
  }
  // helper function to print each chunk value
  // variant: num must be between 0-999
  string chunkToString(int num) {
    string result = "";
    // break into three numbers
    //get the hundreds
    int hundreds = num / 100;
    if (hundreds > 0)
      result = result + numberToString(hundreds) + " Hundred ";
    std::cout << "hundreds" << result;
    // last two digits
    int second = (num) % 100;
    // logic for the second digit

    if (second >= 0 && second <= 19) {
      result = result + numberToString(second);
      return trim(result);
    } else {
      // we need to include the twenty... thrity
      // 20-29
      std::cout << "second" << second;
      if (second > 19 && second <= 29) {
        result = result + "Twenty " + numberToString(second % 10);
        return trim(result);

      }
      if (second > 29 && second <= 39) {
        result = result + "Thirty " + numberToString(second % 10);
        return trim(result);
      }
      if (second > 39 && second <= 49) {
        result = result + "Forty " + numberToString(second % 10);
        return trim(result);
      }
      if (second > 49 && second <= 59) {
        result = result + "Fifty " + numberToString(second % 10);
        return trim(result);
      }

      if (second > 59 && second <= 69) {
        result = result + "Sixty " + numberToString(second % 10);
        return trim(result);

      }
      if (second > 69 && second <= 79) {
        result = result + "Seventy " + numberToString(second % 10);
        return trim(result);

      }
      if (second > 79 && second <= 89) {
        result = result + "Eighty " + numberToString(second % 10);
        return trim(result);

      }
      if (second > 89 && second <= 99) {

        result = (result + "Ninety " + numberToString(second % 10));
        return trim(result);

      }

    }

    return "error";
  }

  // helper function breaks the value into int of 3 digits
  std::vector < int > toChunks(int value) {
    // breaks a number into chunks of three values
    std::vector < int > result;
    int chunk;
    while (value != 0) {
      chunk = value % 1000;
      value = value / 1000;
      std::cout << "value added" << chunk << std::endl;
      result.insert(result.begin(), chunk);
    }
    return result;
  }
  // trim string

  // helper function to return the string o 1-12;
  string numberToString(int n) {
    switch (n) {
    case (0):
      return "";
      break;
    case (1):
      return "One";
      break;
    case (2):
      return "Two";
      break;
    case (3):
      return "Three";
      break;
    case (4):
      return "Four";
      break;
    case (5):
      return "Five";
      break;
    case (6):
      return "Six";
      break;
    case (7):
      return "Seven";
      break;
    case (8):
      return "Eight";
      break;
    case (9):
      return "Nine";
      break;
    case (10):
      return "Ten";
      break;
    case (11):
      return "Eleven";
      break;
    case (12):
      return "Twelve";
      break;
    case (13):
      return "Thirteen";
      break;
    case (14):
      return "Fourteen";
      break;

    case (15):
      return "Fifteen";
      break;
    case (16):
      return "Sixteen";
      break;
    case (17):
      return "Seventeen";
      break;
    case (18):
      return "Eighteen";
      break;
    case (19):
      return "Nineteen";
      break;
    default:
      return "Error";
      break;

    }

  }
};
