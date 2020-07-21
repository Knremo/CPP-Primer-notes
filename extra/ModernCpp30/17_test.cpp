#include <iterator>

using namespace std;

template <typename I, typename F>
class filter_view
{
public:
    class iterator
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef typename iterator_traits<I>::value_type value_type;
        typedef typename iterator_traits<I>::pointer pointer;
        typedef typename iterator_traits<I>::reference reference;
        typedef forward_iterator_tag iterator_category;

        iterator(I current, I end, F cond)
            : current_(current), end_(end), cond_(cond)
        {
            if (current_ != end_ && !cond_(*current_))
            {
                ++*this;
            }
        }
        iterator &operator++()
        {
            while (current_ != end_)
            {
                ++current_;
                if (cond_(*current_))
                {
                    break;
                }
            }
            return *this;
        }
        iterator operator++(int)
        {
            auto temp = *this;
            ++*this;
            return temp;
        }
        reference operator*() const
        {
            return *current_;
        }
        pointer operator->() const
        {
            return &*current_;
        }

        bool operator==(const iterator &rhs)
        {
            return current_ == rhs.current_;
        }
        bool operator!=(const iterator &rhs)
        {
            return !operator==(rhs);
        }

    private:
        I current_;
        I end_;
        F cond_;
    };
    filter_view(I begin, I end, F cond)
        : begin_(begin), end_(end), cond_(cond)
    {
    }
    iterator begin() const
    {
        return iterator(begin_, end_, cond_);
    }
    iterator end() const
    {
        return iterator(end_, end_, cond_);
    }

private:
    I begin_;
    I end_;
    F cond_;
};