#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::cout << "Hány elemet rendezzünk le (K)? ";
    int K;
    std::cin >> K;

    std::cout << "Press 'Ctrl-D' after input of files.\n";
    std::istream_iterator<int> Read{std::cin}, EOS;
    std::vector<int> V{Read, EOS};

    auto Delimiter = std::stable_partition(
        V.begin(), std::next(V.begin(), K),
        [](const int I) -> bool { return I % 2 == 0; });

    std::ostream_iterator<int> Print{std::cout, ", "};
    std::cout << "Párosok:\n\t";
    std::copy(V.begin(), Delimiter, Print);
    std::cout << "\nPáratlanok:\n\t";
    std::copy(Delimiter, std::next(V.begin(), K), Print);
}
