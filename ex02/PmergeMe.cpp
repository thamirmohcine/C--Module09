#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const char **args, size_t seqSize){
    TakeSequence(args, seqSize);
    seq = StartSorting(seq);

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

    if (Numlist.size() <= 1)
        return Numlist;

    if (Numlist.size() == 2){
        if (Numlist[0] > Numlist[1])
            std::swap(Numlist[1] ,Numlist[0]);
        return Numlist;
    }

    for (std::vector<std::pair<int, int > >::iterator it = p.begin(); it != p.end();it++){
        mainChain.push_back(it->first);
        PendingChain.push_back(it->second);
    }

    mainChain = StartSorting(mainChain);
    for (std::vector<std::pair<int, int > >::iterator it(p.begin()); it != p.end();it++){
        if (mainChain[0] == it->first){
            mainChain.insert(mainChain.begin(), it->second);
            PendingChain.erase(std::find(PendingChain.begin(), PendingChain.end(), it->second));
            break;
        }
    }

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

std::vector<int> PmergeMe::GenerateIndices(std::vector<int> JkSeq, size_t n) {
    std::vector<int> ret;
    for (size_t i = 2; i < JkSeq.size(); ++i) {
        
        int J_current = JkSeq[i];
        
        int J_previous = JkSeq[i - 1];
        
        int End_Index_1_Based = std::min(J_current - 1, (int)n);

        int Start_Index_1_Based = J_previous;
        
        for (int index_1_based = End_Index_1_Based; index_1_based >= Start_Index_1_Based; --index_1_based) {
            ret.push_back(index_1_based - 1); 
        }

        if (End_Index_1_Based == (int)n) {
            break;
        }
    }
    
    int last_index = 0;
    if (!ret.empty()) {
        last_index = ret.back() + 1;
    }
    
    for (int i = (int)n - 1; i >= last_index; i--) {
        bool already_added = false; 
        for(int index : ret) {
            if (index == i) {
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