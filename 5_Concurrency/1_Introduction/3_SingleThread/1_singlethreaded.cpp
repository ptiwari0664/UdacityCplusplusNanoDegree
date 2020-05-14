#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in thread\n"; 

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in thread\n"; 
}

int main()
{
    //Example:1
    std::cout << "Hello concurrent world from main! Thread id = " <<
     std::this_thread::get_id() << std::endl;

    //------------------------------------------------------------------------------
    //Example:2
    unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores 
                << " cores available" << std::endl;

    std::cout << "-------------------------------------\n";
    //------------------------------------------------------------------------------
    //Example:3
    // create thread
    std::thread t(threadFunction);
    // // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";
    // wait for thread to finish
    t.join();
    
    std::cout << "-------------------------------------\n";
    //------------------------------------------------------------------------------
    //Example:5
    // create thread
    std::thread t5(threadFunction);
    // wait for thread to finish
    t5.join();
    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in main\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in main\n";

    return 0;
}
