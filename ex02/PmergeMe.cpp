#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
double PmergeMe::getTimeUs(){
    struct timespec s;
    if (clock_gettime(CLOCK_MONOTONIC, &s) < 0)
        throw std::exception();
    return (((double)s.tv_sec * 1000000.0) + (double)s.tv_nsec / 1000.0);
}

void PrintSeq(std::vector<int > se){
    for (size_t i(0); i < se.size();i++){
        (i == 4) ? ((i == se.size()-1) ? (std::cout << se[i]) : (std::cout << "[...]")) : std::cout << se[i];
        if (i == 4) break;
        std::cout << " ";
    }
    std::cout << std::endl;
}

void PrintSeqForDq(std::deque<int > se){
    for (size_t i(0); i < se.size();i++){
        (i == 4) ? ((i == se.size()-1) ? (std::cout << se[i]) : (std::cout << "[...]")) : std::cout << se[i];
        if (i == 4) break;
        std::cout << " ";
    }
    std::cout << std::endl;
}

PmergeMe::PmergeMe(const char **args, size_t seqSize){
    double start = getTimeUs(); 
    TakeSequence(args, seqSize);
    std::cout << "Before:  ";
    PrintSeq(seq);
    seq = StartSorting(seq);
    double end = getTimeUs();
    std::cout << "After:   ";
    PrintSeq(seq);
    std::cout << "Time to process a range of " << seq.size() << " elements with std::vector :" << "  "  << end-start << " us"<< std::endl;
    
    start = getTimeUs(); 
    TakeDqSequence(args, seqSize);
    std::cout << "Before:  ";
    PrintSeqForDq(deque_seq);
    deque_seq = StartSortingForDq(deque_seq);
    end = getTimeUs();
    std::cout << "After:   ";
    PrintSeqForDq(deque_seq);
    std::cout << "Time to process a range of " << deque_seq.size() << " elements with std::deque :" << "  "  << end-start << " us"<< std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other){
    if (this != &other){
        this->seq = other.seq;
    }
}

PmergeMe&    PmergeMe::operator=(const PmergeMe& other){
    if (this != &other){
        seq = other.seq;
    }
    return *this;
}

PmergeMe::~PmergeMe(){}

void    PmergeMe::TakeSequence(const char **args, size_t seqSize){
    for (size_t i(0); i < seqSize;i++){
        seq.push_back(trim_StrToNumber(args[i]));
    }
}
void    PmergeMe::TakeDqSequence(const char **args, size_t seqSize){
    for (size_t i(0); i < seqSize;i++){
        deque_seq.push_back(trim_StrToNumber(args[i]));
    }
}

int     PmergeMe::trim_StrToNumber(const std::string& s) {
    std::stringstream ss(s);
    long long ret ;
    if (!(ss >> ret))
        throw NonNumberArgument();
    if (!(ret <= 2147483647 && ret >= 0))
        throw OutOfRnage();
    return ret;
}

std::vector<int>    PmergeMe::StartSorting(std::vector<int> Numlist) {

    std::vector<int > mainChain;
    std::vector<int > PendingChain;

    int LeftOver(Numlist.size() % 2 ? Numlist.back() : -1);

    (LeftOver != -1) ? Numlist.pop_back(): void();

    std::vector<std::pair<int, int > > p = makePairs(Numlist);

    if (Numlist.size() <= 1){
        if (LeftOver != -1){
            std::vector< int>::iterator Position = std::lower_bound(Numlist.begin(), Numlist.end(), LeftOver);
            Numlist.insert(Position, LeftOver);
        }
        return Numlist;
    }

    if (Numlist.size() == 2){
        if (Numlist[0] > Numlist[1])
            std::swap(Numlist[1] ,Numlist[0]);
        if (LeftOver != -1){
            std::vector< int>::iterator Position = std::lower_bound(Numlist.begin(), Numlist.end(), LeftOver);
            Numlist.insert(Position, LeftOver);
        }
        return Numlist;
    }

    for (std::vector<std::pair<int, int > >::iterator it = p.begin(); it != p.end();it++){
        mainChain.push_back(it->first);
        PendingChain.push_back(it->second);
    }
    mainChain = StartSorting(mainChain);
    std::vector<int > Indices =  GenerateIndices(GenerateJacobSthalSeq(PendingChain.size()), PendingChain.size());

    for(size_t j(0); j < Indices.size();j++){
        std::vector< int>::iterator Position = std::lower_bound(mainChain.begin(), mainChain.end(), PendingChain[Indices[j]]);
        mainChain.insert(Position, PendingChain[Indices[j]]);
    }
    if (LeftOver != -1){
        std::vector< int>::iterator Position = std::lower_bound(mainChain.begin(), mainChain.end(), LeftOver);
        mainChain.insert(Position, LeftOver);
    }

    return mainChain;
}

std::deque<int>    PmergeMe::StartSortingForDq(std::deque<int> Numlist) {

    std::deque<int > mainChain;
    std::deque<int > PendingChain;

    int LeftOver(Numlist.size() % 2 ? Numlist.back() : -1);

    (LeftOver != -1) ? Numlist.pop_back(): void();

    std::deque<std::pair<int, int > > p = makePairsForDq(Numlist);

    if (Numlist.size() <= 1){
        if (LeftOver != -1){
            std::deque< int>::iterator Position = std::lower_bound(Numlist.begin(), Numlist.end(), LeftOver);
            Numlist.insert(Position, LeftOver);
        }
        return Numlist;
    }

    if (Numlist.size() == 2){
        if (Numlist[0] > Numlist[1])
            std::swap(Numlist[1] ,Numlist[0]);
        if (LeftOver != -1){
            std::deque< int>::iterator Position = std::lower_bound(Numlist.begin(), Numlist.end(), LeftOver);
            Numlist.insert(Position, LeftOver);
        }
        return Numlist;
    }

    for (std::deque<std::pair<int, int > >::iterator it = p.begin(); it != p.end();it++){
        mainChain.push_back(it->first);
        PendingChain.push_back(it->second);
    }
    mainChain = StartSortingForDq(mainChain);
    std::deque<int > Indices =  GenerateIndicesForDq(GenerateJacobSthalSeqForDq(PendingChain.size()), PendingChain.size());

    for(size_t j(0); j < Indices.size();j++){
        std::deque< int>::iterator Position = std::lower_bound(mainChain.begin(), mainChain.end(), PendingChain[Indices[j]]);
        mainChain.insert(Position, PendingChain[Indices[j]]);
    }
    if (LeftOver != -1){
        std::deque< int>::iterator Position = std::lower_bound(mainChain.begin(), mainChain.end(), LeftOver);
        mainChain.insert(Position, LeftOver);
    }

    return mainChain;
}

std::vector<std::pair<int , int> > PmergeMe::makePairs(std::vector<int> Numlist){
    std::vector<std::pair<int , int> > p;
    for (size_t i(0); i < Numlist.size();i += 2){
        if (Numlist[i] > Numlist[i+1])
            p.push_back(std::make_pair(Numlist[i], Numlist[i+1]));
        else
            p.push_back(std::make_pair(Numlist[i+1], Numlist[i]));
    }
    return p;
}

std::deque<std::pair<int , int> > PmergeMe::makePairsForDq(std::deque<int> Numlist){
    std::deque<std::pair<int , int> > p;
    for (size_t i(0); i < Numlist.size();i += 2){
        if (Numlist[i] > Numlist[i+1])
            p.push_back(std::make_pair(Numlist[i], Numlist[i+1]));
        else
            p.push_back(std::make_pair(Numlist[i+1], Numlist[i]));
    }
    return p;
}


std::vector<int> PmergeMe::GenerateJacobSthalSeq(size_t PendingChainSize) {
    std::vector<int> ret;
    ret.push_back(1);
    ret.push_back(1); 

    int j = 2;
    while (true){
        long long next_j = (long long)ret[j-1] + (2LL * ret[j-2]);
        if (next_j > INT_MAX) next_j = INT_MAX; 

        if (static_cast<size_t>(next_j) > PendingChainSize)
            break;
        
        ret.push_back(static_cast<int>(next_j));
        j++;
    }
    return ret;
}

std::deque<int> PmergeMe::GenerateJacobSthalSeqForDq(size_t PendingChainSize) {
    std::deque<int> ret;
    ret.push_back(1);
    ret.push_back(1); 

    int j = 2;
    while (true){
        long long next_j = (long long)ret[j-1] + (2LL * ret[j-2]);
        if (next_j > INT_MAX) next_j = INT_MAX; 

        if (static_cast<size_t>(next_j) > PendingChainSize)
            break;
        
        ret.push_back(static_cast<int>(next_j));
        j++;
    }
    return ret;
}

std::vector<int> PmergeMe::GenerateIndices(std::vector<int> JkSeq, size_t n) {
    std::vector<int> ret;
    for (size_t i = 2; i < JkSeq.size(); ++i) {
        
        int J_c = JkSeq[i];
        
        int J_p = JkSeq[i - 1];
        
        int End_I = std::min(J_c - 1, (int)n);

        int Start_I = J_p;
        
        for (int i = End_I; i >= Start_I; --i) {
            ret.push_back(i - 1); 
        }

        if (End_I == (int)n) {
            break;
        }
    }
    
    int complete_ = 0;
    if (!ret.empty()) {
        complete_ = ret.back() + 1;
    }
    
    for (int i = (int)n - 1; i >= complete_; i--) {
        bool already_added = false; 

        for (std::vector<int>::iterator it =  ret.begin(); it != ret.end(); it++){
            if (*it == i) {
                already_added = true;
                break;
            }
        }
        if (!already_added) {
            ret.push_back(i);
        }
    }    
    return ret;
}

std::deque<int> PmergeMe::GenerateIndicesForDq(std::deque<int> JkSeq, size_t n) {
    std::deque<int> ret;
    for (size_t i = 2; i < JkSeq.size(); ++i) {
        
        int J_c = JkSeq[i];
        
        int J_p = JkSeq[i - 1];
        
        int End_I = std::min(J_c - 1, (int)n);

        int Start_I = J_p;
        
        for (int i = End_I; i >= Start_I; --i) {
            ret.push_back(i - 1); 
        }

        if (End_I == (int)n) {
            break;
        }
    }
    
    int complete_ = 0;
    if (!ret.empty()) {
        complete_ = ret.back() + 1;
    }
    
    for (int i = (int)n - 1; i >= complete_; i--) {
        bool already_added = false; 

        for (std::deque<int>::iterator it =  ret.begin(); it != ret.end(); it++){
            if (*it == i) {
                already_added = true;
                break;
            }
        }
        if (!already_added) {
            ret.push_back(i);
        }
    }    
    return ret;
}