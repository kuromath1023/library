struct Eratosthenes {
    vector<bool> isPrime;
    vector<int> minfactor;

    Eratosthenes(int n) : isPrime(n + 1, true), minfactor(n + 1, -1) {
        isPrime[0] = isPrime[1] = false;
        minfactor[1] = 1;

        for (int i = 2; i <= n; i++) {
            if (!isPrime[i]) continue;
            minfactor[i] = i;
            if (1LL * i * i > n) continue;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
                if (minfactor[j] == -1) minfactor[j] = i;
            }
        }
    }

    vector<int> prime_table() {
        vector<int> Primes;
        for (int i = 2; i < int(isPrime.size()); i++) {
            if (isPrime[i]) Primes.push_back(i);
        }
        return Primes;
    }

    vector<pair<int, int>> factorize(int n) {
        vector<pair<int, int>> F;
        while (n > 1) {
            int p = minfactor[n];
            int ex = 0;
            while (n % p == 0) {
                n /= p;
                ex++;
            }
            F.emplace_back(p, ex);
        }
        return F;
    }
};