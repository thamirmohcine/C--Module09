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
        void ValidateDate(std::string& s);
        void ValidatePrice(std::string& s);
        void ValidateValue(std::string &Value);
        void StartProcess(const std::string &InputFile);
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string &InputFile);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void    ValidateInputFile(const std::string &InputFile);
        void    StratProcess(const std::string &InputFile);
        void    trimData(std::string &s);
        void    PrintData(std::string &date, std::string &Value);
        class CantOpenFile: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: could not open file.");
                }
        };
        class NonValidInputFile: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: the file should file.txt.");
                }
        };
        class InvalidFileFormat: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: Invalid File Format");
                }
        };
        class InvalidDate: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: Invalid Date Expected : 'YYYY-MM-DD'");
                }
        };
        class InvalidPrice: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: Invalid Date Expected  a Valide Number");
                }
        };
        class InvalidHeader: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: Invalid Header Expected : date,exchange_rate");
                }
        };
        class NoDataAvaliable: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: No Data Loaded");
                }
        };
        class NegativeValue: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: not a positive number.");
                }
        };
        class TooLargeValue: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: too large a number.");
                }
        };
        class InvalidValue: public std::exception{
            public:
                virtual const char *what() const throw(){
                    return ("Error: too large a number.");
                }
        };
};

#endif