#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>

typedef long long int LL;

bool canSum(const LL &targetSum, const std::vector<LL> &array){
    
    if (targetSum == 0)
    {
        return true;
    }
    if (targetSum < 0)
    {
        return false;
    }    
    for (int i = 0; i < array.size(); i++)
    {
        if (canSum(targetSum - array[i], array))
        {
            return true;
        }   
    }
    return false;
}

std::vector<LL> howSum(const LL &targetSum, const std::vector<LL> &array){
    if (targetSum < 0)
    {
        return {-1};
    }
    for (int i = 0; i < array.size(); i++)
    {
        if (!(targetSum - array[i]))
        {
            return {array[i]};
        }
        std::vector<LL> result = howSum(targetSum - array[i], array);
        if(result[0] != -1){
            result.push_back(array[i]);
            return result;
        }         
    }
    return {-1}; 
}

std::vector<LL> bestSum(const LL &targetSum, const std::vector<LL> &array){
    if (targetSum < 0)
    {
        return {-1};
    }

    std::vector<LL> shortest = {-1};

    for (int i = 0; i < array.size(); i++)
    {
        if (!(targetSum - array[i]))
        {
            return {array[i]};
        }
        std::vector<LL> result = bestSum(targetSum - array[i], array);
        if(result[0] != -1){
            result.push_back(array[i]);
            if (shortest[0] == -1 || result.size() < shortest.size() )
            {
                shortest.pop_back();
                shortest = result;
            }          
        }         
    }
    return shortest; 
}

bool canSum_hashed(const LL &targetSum, const std::vector<LL> &array){

    static std::unordered_map<LL, bool> container;

    if (targetSum == 0)
    {
        return true;
    }
    if (targetSum < 0)
    {
        return false;
    }
    if (container.count(targetSum))
    {
        return container[targetSum];
    }

    for (int i = 0; i < array.size(); i++)
    {
        if (canSum_hashed(targetSum - array[i], array))
        {
            container[targetSum] = true;
            // return container[targetSum];
            return true;
        }   
    }
    container[targetSum] = false;
    // return container[targetSum];
    return false;
}

std::vector<LL> howSum_hashed(const LL &targetSum, const std::vector<LL> &array){
    static std::unordered_map<LL, std::vector<LL>> cache;

    if (targetSum < 0)
    {
        return {-1};
    }
    if (cache.count(targetSum))
    {
        return cache[targetSum];
    }
    for (int i = 0; i < array.size(); i++)
    {
        if (!(targetSum - array[i]))
        {
            return {array[i]};
        }
        std::vector<LL> result = howSum_hashed(targetSum - array[i], array);
        if(result[0] != -1){
            result.push_back(array[i]);
            cache[targetSum] = result;
            return cache[targetSum];
        }         
    }
    cache[targetSum] = {-1};
    return {-1}; 
}

std::vector<LL> bestSum_hashed(const LL &targetSum, const std::vector<LL> &array){

    static std::unordered_map<LL, std::vector<LL>> cache1;

    if (targetSum < 0)
    {
        return {-1};
    }
    if (cache1.count(targetSum))
    {
        return cache1[targetSum];
    }

    std::vector<LL> shortest = {-1};

    for (int i = 0; i < array.size(); i++)
    {
        if (!(targetSum - array[i]))
        {
            return {array[i]};
        }
        std::vector<LL> result = bestSum_hashed(targetSum - array[i], array);
        if(result[0] != -1){
            result.push_back(array[i]);
            if (shortest[0] == -1 || result.size() < shortest.size() )
            {
                shortest.pop_back();
                shortest = result;
            }          
        }         
    }
    cache1[targetSum] = shortest;
    return shortest; 
}

int main(){

    bool keep_going = true;

    while (keep_going)
    {
        LL t, n;

        std::cout << "Insert the targeted sum: \n";
        std::cin >> t;

        std::cout << "Insert the size of the array: \n";
        std::cin >> n;

        std::vector<LL> numbers(n);

        std::cout << "Insert the array of numbers: \n";

        for (int i = 0; i < n; i++)
        {
            std::cout << "Insert the number in the position: " << i + 1 << "\n";
            std::cin >> numbers[i];
        }
        
        auto start_hashed = std::chrono::steady_clock::now();

        std::cout << "Is it possible to sum (hashed): " << canSum_hashed(t, numbers) << std::endl;

        auto end_hashed = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_hashed - start_hashed).count() << " ms" << std::endl;

        auto start_howsum_hashed = std::chrono::steady_clock::now();

        std::cout << "The possible combination (hashed): \n";

        auto result_hashed = howSum_hashed(t, numbers);

        for (uint64_t i = 0; i < result_hashed.size(); i++)
        {
            std::cout << result_hashed[i] << " ";
        }
        
        std::cout << "\n";

        auto end_howsum_hashed = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_howsum_hashed - start_howsum_hashed).count() << " ms" << std::endl;

        auto start_bestsum_hashed = std::chrono::steady_clock::now();

        std::cout << "The Best combination (hashed): \n";

        auto result_best_hashed = bestSum_hashed(t, numbers);

        for (uint64_t i = 0; i < result_best_hashed.size(); i++)
        {
            std::cout << result_best_hashed[i] << " ";
        }
        
        std::cout << "\n";

        auto end_bestsum_hashed = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_bestsum_hashed - start_bestsum_hashed).count() << " ms" << std::endl;

        auto start = std::chrono::steady_clock::now();

        std::cout << "Is it possible to sum: " << canSum(t, numbers) << std::endl;

        auto end = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        auto start_howsum = std::chrono::steady_clock::now();

        std::cout << "The possible combination: \n";

        auto result = howSum(t, numbers);

        for (uint64_t i = 0; i < result.size(); i++)
        {
            std::cout << result[i] << " ";
        }
        
        std::cout << "\n";

        auto end_howsum = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_howsum - start_howsum).count() << " ms" << std::endl;

        auto start_bestsum = std::chrono::steady_clock::now();

        std::cout << "The Best combination: \n";

        auto result_best = bestSum(t, numbers);

        for (uint64_t i = 0; i < result_best.size(); i++)
        {
            std::cout << result_best[i] << " ";
        }
        
        std::cout << "\n";

        auto end_bestsum = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_bestsum - start_bestsum).count() << " ms" << std::endl;

        std::cout << "Do you want to do another time test? (1 or 0) " << std::endl;

        int loop;

        std::cin >>  loop;

        switch (loop)
        {
            case 0:
                keep_going = false;
                break;
            case 1:
                std::cout << "Here we go again " << std::endl;
                break;
            default:
                std::cout << "Invalid answer however i will consider as one :) " << std::endl;
                break;
        }
        
    }
}