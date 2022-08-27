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
        std::cout << "Case one: " << canSum_hashed(t, numbers) << std::endl;

        auto end_hashed = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_hashed - start_hashed).count() << " ms" << std::endl;

        auto start = std::chrono::steady_clock::now();

        std::cout << "Case two: " << canSum(t, numbers) << std::endl;

        auto end = std::chrono::steady_clock::now();

        std::cout << "Elapsed time was: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

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