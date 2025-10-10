#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <exception>

class BitcoinExchange{
    private:
        std::map<std::string, double> data;
        void ReadData();
        bool ValidateDate(std::string& s);
        bool ValidatePrice(std::string& s);
        void ValidateValue(std::string &Value);
    public:
        BitcoinExchange(std::string &InputFile);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void    StratProcess(std::string &InputFile);
        void    trimData(std::string &s);
        // const std::map<std::string, double> &getData() const;
        
        class CantOpenFile: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("could not open file.");
                }
        };
        class InvalidFileFormat: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Invalid File Format");
                }
        };
        class InvalidDate: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Invalid Date Expected : 'YYYY-MM-DD'");
                }
        };
        class InvalidPrice: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Invalid Date Expected  a Valide Number");
                }
        };
        class InvalidHeader: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Invalid Header Expected : date,exchange_rate");
                }
        };
        class NoDataAvaliable: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("No Data Loaded");
                }
        };
};

#endif