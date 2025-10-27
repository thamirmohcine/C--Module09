#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const std::string &InputFile){
    ValidateInputFile(InputFile);
    ReadData();
    StartProcess(InputFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    if (this != &other){
        *this = other;
    }
}


BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if (this != &other){
        this->data = other.data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void    BitcoinExchange::ValidateInputFile(const std::string &InputFile){
    if (InputFile.empty())
        throw NonValidInputFile();
    size_t i = 0;
    while (i < InputFile.size()-1) i++;
    if (InputFile[i--] != 't' || InputFile[i--] != 'x' || InputFile[i--] != 't' || InputFile[i] != '.')
        throw NonValidInputFile();
}

void    BitcoinExchange::trimData(std::string &s){
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
        s =  "";
    else
        s = s.substr(start, end-start+1);
}
void BitcoinExchange::ValidateDate(std::string& date){
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        throw InvalidDate();
    for (size_t i(0);i < date.size();i++){
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            throw InvalidDate();
    }
    std::replace(date.begin(), date.end(), '-', ' ');
    std::stringstream ss(date);
    int year = 0;
    int month = 0;
    int day = 0;
    ss >>  year >> month >> day ;
    int Max_d_m[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        Max_d_m[2] = 29;
    if ((year > 9999 || year < 1000 || month < 1 || month > 12 || day < 1 || day > Max_d_m[month])){
        throw InvalidDate();
    }
}

void BitcoinExchange::ValidatePrice(std::string& price){
    int floatingPoint = 0;
    for (size_t i(0); i < price.size(); i++){
        if (price[i] == '.'){
            if (floatingPoint)
                throw InvalidPrice();
            floatingPoint++;
            continue;
        }
        if (!std::isdigit(price[i]))
            throw InvalidPrice();
    }
}

void BitcoinExchange::ValidateValue(std::string &Value){
    int floatingPoint = 0;
    for (size_t i(0); i < Value.size(); i++){
        if (Value[i] == '.'){
            if (i == 0 || i == Value.size()-1 || floatingPoint)
                throw InvalidValue();
            floatingPoint++;
            continue;
        }
        if (!std::isdigit(Value[i]))
            throw InvalidValue();
    }
    std::stringstream s(Value);
    double v;
    if (!(s >> v))
        throw InvalidValue();
    if (v < 0)
        throw NegativeValue();
    if (v > 1000)
        throw TooLargeValue();
}

void    BitcoinExchange::ReadData(){
    std::ifstream datafile;
    datafile.open("data.csv", std::ios_base::in);
    if (!datafile.is_open())
        throw CantOpenFile();
    std::string line;
    std::getline(datafile, line);
    if (line != "date,exchange_rate")
        throw InvalidHeader();
    while (std::getline(datafile, line)){
        if (line.empty())
            continue;
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            throw InvalidHeader();
        std::string date = line.substr(0, pos);
        std::string price = line.substr(pos+1);
        trimData(date);
        trimData(price);
        ValidateDate(date);
        ValidatePrice(price);
        double i = 0;
        std::stringstream s(price);
        if (!(s >> i)) {
            throw std::invalid_argument("Invalid number format");
            if (i < 0)
                throw InvalidPrice();
        }
        data.insert(std::make_pair(date, i));
    }
    datafile.close();
    if (data.empty())
        throw NoDataAvaliable();
}

void    BitcoinExchange::PrintData(std::string &date, std::string &Value){
    std::stringstream s(Value);
    double v ;
    s >> v;
    std::string output;
    double FinalV = -1;
    std::map<std::string, double>::iterator it = data.upper_bound(date);
    output = date + " => " + Value + " = " ;
    if (it == data.begin())
        output = "Error: no earlier date available for " + date;
    else{
        if (it->first == date);
        else    it--;
        FinalV = (v * it->second);      
    }
    std::cout << output;
    if (FinalV != -1)
        std::cout << FinalV;
    std::cout << std::endl;
}

void    BitcoinExchange::StartProcess(const std::string &InputFile){
    std::ifstream Ifile;
    Ifile.open(InputFile.c_str(), std::ios_base::in);
    if (!Ifile.is_open())
        throw CantOpenFile();
    std::string line;
    while (std::getline(Ifile, line)){
        if (line.empty() || line == "date | value")
            continue;
        size_t pos = line.find('|');
        if (pos == std::string::npos){
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        std::string Value = line.substr(pos+1);
        try{
            trimData(date);
            trimData(Value);
            ValidateDate(date);
            ValidateValue(Value);
            PrintData(date, Value);
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
            continue;
        }
    }
}