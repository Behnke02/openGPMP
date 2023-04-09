/*
 * Driver for showing how to use the core basic and elementary
 * functionalities of the Number Theory module
 *
 */
#include <chrono>
#include <cmath>
#include <iostream>
#include <openMTPK/nt/primes.hpp>
#include <openMTPK/threadpool.hpp>
#include <vector>

int main() {
    std::cout << "BASIC NUMBER THEORY OPERATIONS\n" << std::endl;
    // declare primality class object
    mtpk::Primality p;

    std::cout << "<--------- IS IT PRIME? --------->\n";
    int a = 9;
    // check if an integer is prime or not
    bool is_it = p.is_prime(a);

    std::cout << a << " is prime? : ";
    is_it ? std::cout << "true\n" : std::cout << "false\n" << std::endl;

    int b = 2;
    bool is_it2 = p.is_prime(b);

    std::cout << b << " is prime? : ";
    is_it2 ? std::cout << "true\n" : std::cout << "false\n" << std::endl;
    std::cout << "\n";

    std::cout << "<--------- MILLER-RABIN METHOD --------->\n";
    int min_num = 1;
    // display the prime numbers smaller than a given value
    int max_num = 100;
    // number of iterations
    int iters = 4;
    /*
     * calculate the solution, the method doesn't return a value,
     * prints the values
     */
    p.miller_rabin(iters, min_num, max_num);
    p.miller_rabin(iters, 25, 50);
    p.miller_rabin(iters, 30, 3000);

    std::cout << "\n";

    std::cout << "<--------- CARMICHAEL NUMBERS --------->\n";
    int cm_test = 500;
    bool carm_num = p.carmichael_num(cm_test);

    int cm_test1 = 561;
    bool carm_num1 = p.carmichael_num(cm_test1);

    int cm_test2 = 1105;
    bool carm_num2 = p.carmichael_num(cm_test2);

    std::cout << cm_test << " is a carmichael number : ";
    carm_num ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << cm_test1 << " is a carmichael number : ";
    carm_num1 ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << cm_test2 << " is a carmichael number : ";
    carm_num2 ? std::cout << "true\n" : std::cout << "false\n";

    std::cout << "\n";
    /*
     * Power Modulo function
     */
    int pow_a = 3;
    int pow_b = 2;
    int pow_c = 2;
    // returns (a^b) % c
    int pow_res = p.mod_pow(pow_a, pow_b, pow_c);
    printf("%d ^ %d %% %d = %d\n", pow_a, pow_b, pow_c, pow_res);

    int pow_d = 5;
    int pow_e = 2;
    int pow_f = 7;

    int pow_res_1 = p.mod_pow(pow_d, pow_e, pow_f);
    printf("%d ^ %d %% %d = %d\n", pow_d, pow_e, pow_f, pow_res_1);

    int pow_g = 8;
    int pow_h = 9;
    int pow_i = 3;

    int pow_res_2 = p.mod_pow(pow_g, pow_h, pow_i);
    printf("%d ^ %d %% %d = %d\n", pow_g, pow_h, pow_i, pow_res_2);

    bool cmp = p.miller_rabin_prime(5, 4);
    std::cout << "miller_rabin_prime: " << cmp << "\n";
    std::cout << "\n";
    /*
     * Jacobian
     */

    /*
     * Solovay-Strassen Primality Test
     */
    int ss_0 = 15;
    if (p.solovoy_strassen(ss_0, 50))
        printf("%d is prime\n", ss_0);
    else
        printf("%d is composite\n", ss_0);

    std::cout << "\n";

    std::cout << "<--------- USING THREADPOOL --------->\n";

    // vector if 64 bit integers
    std::vector<int64_t> nums = {
        9223372036854775803,   9223372036854775807,   9223372036854775303,
        4567890123456789LL,    5678901234567890LL,    6789012345678901LL,
        7890123456789012LL,    8901234567890123LL,    9999999967LL,
        12345678901234567LL,   987654321987654321LL,  2147483647LL,
        9223372036854775783LL, 1311768467463790320LL, 7237005577332262210LL,
        3037000499LL,          2305843009213693951LL, 2305843009213693967LL,
        2305843009213693971LL, 2305843009213693973LL, 2305843009213693977LL,
        2305843009213693989LL};

    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();

    std::cout << "vector size " << size(nums) << std::endl;
    // declares a threadpool with 4 threads
    ThreadPool *pool = new ThreadPool(4);

    std::vector<std::future<bool>> miller_results;
    mtpk::Primality prim;
    for (auto n : nums) {
        miller_results.emplace_back(pool->enqueue(
            [&prim, n]() { return prim.miller_rabin_prime(n, 100); }));
    }

    // Print the results
    std::cout << "Results:\n";
    std::cout << "Miller-Rabin" << std::endl;
    for (size_t i = 0; i < miller_results.size(); i++) {
        bool is_prime = miller_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }

    // delete the threadpool object, freeing its resources
    delete pool;
    // create a new threadpool object with 4 threads
    ThreadPool *new_pool = new ThreadPool(4);

    std::vector<std::future<bool>> AKS_results;

    for (auto n : nums) {
        AKS_results.emplace_back(
            new_pool->enqueue([&prim, n]() { return prim.AKS(n); }));
    }

    std::cout << "\nAKS" << std::endl;
    for (size_t i = 0; i < AKS_results.size(); i++) {
        bool is_prime = AKS_results[i].get();
        std::cout << nums[i] << " is " << (is_prime ? "prime" : "composite")
                  << "\n";
    }

    delete new_pool;

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
