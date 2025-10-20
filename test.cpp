std::vector<int>    PmergeMe::sortVec(std::vector<int> ints) {
    
    std::vector<int>                    mChain;
    std::vector<int>                    pChain;
    std::vector<std::pair<int, int> >    pairs = makePairs(ints);
    
    if (ints.size() < 2) return ints;
    if (ints.size() == 2) {
        if (*ints.begin() > *(++ints.begin()))
            std::swap(ints[0], ints[1]);
        return ints;
    }

    int    widowed(ints.size() % 2 ? ints.back() : -1);

    for (size_t index(0); index < pairs.size(); index++) {

        if (pairs[index].first > pairs[index].second) {
            mChain.push_back(pairs[index].first);
            pChain.push_back(pairs[index].second);
            std::swap(pairs[index].first, pairs[index].second);
        } else {
            pChain.push_back(pairs[index].first);
            mChain.push_back(pairs[index].second);
        }
    }

    mChain    =    sortVec(mChain);

    for (std::vector<std::pair<int, int> >::iterator elm = pairs.begin(); elm != pairs.end(); ++elm) {

        if (mChain[0] == elm->second)  {
            mChain.insert(mChain.begin(), elm->first);
            std::vector<int>::iterator    element = std::find(pChain.begin(), pChain.end(), elm->first);
            if (element != pChain.end())
                pChain.erase(element);
            break ;
        }
    }

    std::vector<int>    insertOrder = jacobing(pChain.size());
    
    for (size_t i = 0; i < insertOrder.size(); ++i) {
        size_t    index = insertOrder[i];
        std::vector<int>::iterator insertPoint = std::lower_bound(mChain.begin(), mChain.end(), pChain[index]);
        mChain.insert(insertPoint, pChain[index]);
    }

    if (widowed != -1)  {
        std::vector<int>::iterator insertPoint = std::lower_bound(mChain.begin(), mChain.end(), widowed);
        mChain.insert(insertPoint, widowed);
    }
    return mChain;
}