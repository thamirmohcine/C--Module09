#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(std::string &InputFile){
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


// std::map<std::string, double> const &BitcoinExchange::getData() const{
//     return data;
// }

void    BitcoinExchange::trimData(std::string &s){
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
        s =  "";
    else
        s = s.substr(start, end-start+1);
}
bool BitcoinExchange::ValidateDate(std::string& date){
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        throw InvalidDate();
    for (size_t i(0);i < date.size();i++){
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            throw InvalidDate();
    }
}

bool BitcoinExchange::ValidatePrice(std::string& price){
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

void ValidateValue(std::string &Value){
    
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
        (ValidateDate(date) && !ValidatePrice(price));
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

void    BitcoinExchange::StratProcess(std::string& InputFile){
    std::ifstream Ifile;
    Ifile.open(InputFile, std::ios_base::in);
    if (!Ifile.is_open())
        throw CantOpenFile();
    std::string line;
    while (std::getline(Ifile, line)){
        if (line.empty() || line == "date | value")
            continue;
        size_t pos = line.find('|');
        if (pos == std::string::npos){
            std::cout << "Error: bad input => <" << line << ">" << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        std::string Value = line.substr(pos+1);
        (ValidateDate && ValidateValue());


    }
}