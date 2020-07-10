template <bool>
struct compile_time_error;
template <>
struct compile_time_error<true> {};

#define STATIC_ASSERT(Expr, Msg) \
  { \
    (void)ERROR_##Msg;\
  }

int main()
{
    const int a = 1;
    STATIC_ASSERT(a == 2, WTF);

    return 0;
}