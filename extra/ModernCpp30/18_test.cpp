#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

template <
    template <typename, typename>
    class OutContainer = vector,
    typename F, class R
    >
auto fmap(F&& f, R&& inputs)
{
    typedef decay_t<decltype(f(*inputs.begin()))> result_type;
    OutContainer<result_type, allocator<result_type>> result;
    for (auto&& item:inputs) {
        result.push_back(f(item));
    }
    return result;
}

template <typename F>
auto compose(F f)
{
    return [f](auto&&... x) {
        return f(forward<decltype(x)>(x)...);
    };
}
template <typename F, typename... Args>
auto compose(F f, Args... other)
{
    return [f, other...](auto&&... x) {
        return f(compose(other...)(forward<decltype(x)>(x)...));
    };
}
auto square_list = [](auto&& container) {
    return fmap([](int x) { return x*x; }, container);
};

auto sum_list = [](auto&& container) {
    return accumulate(container.begin(), container.end(), 0);
};

auto squared_sum = compose(sum_list, square_list);

int main()
{
    vector<int> v{1, 2, 3, 4, 5};
    cout << squared_sum(v) << endl;
}