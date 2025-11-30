#include <utils/ModInt.h>
#include <utils/Prime.h>
#include <utils/Utils.h>

int main()
{
  timeit(
      []()
      {
        constexpr int N = 1e7;
        Prime<N> p;
        auto primes = p.all_primes();
        std::vector<ModInt<N>> sum(primes.size());
        for (int i = 1; i < primes.size(); i++)
        {
          sum[i] = sum[i - 1] + primes[i];
        }

        for (int i = 1; i < primes.size(); i++)
        {
          std::cout << sum[i] << std::endl;
        }
      });
}
