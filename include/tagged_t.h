#pragma once

#include <concepts>
#include <cstddef>
#include <ostream>
#include <utility>

template <class T, class Tag> class tagged_t {
public:
  using value_type = T;
  using tag_type = Tag;

  explicit constexpr tagged_t(const T& value) : value_(value) {}
  explicit constexpr tagged_t(T&& value) : value_(std::move(value)) {}

  constexpr tagged_t()
    requires std::default_initializable<T>
  = default;

  tagged_t(const tagged_t&) = default;
  tagged_t(tagged_t&&) = default;
  tagged_t& operator=(const tagged_t&) = default;
  tagged_t& operator=(tagged_t&&) = default;
  ~tagged_t() = default;

  [[nodiscard]] constexpr const T& get() const noexcept { return value_; }
  constexpr T& get() noexcept { return value_; }

  [[nodiscard]] constexpr explicit operator const T&() const noexcept {
    return value_;
  }
  constexpr explicit operator T&() noexcept { return value_; }

  constexpr tagged_t& operator++() noexcept(noexcept(++std::declval<T&>())) {
    ++value_;
    return *this;
  }

  constexpr tagged_t
  operator++(int) noexcept(noexcept(tagged_t(std::declval<const T&>())) &&
                           noexcept(std::declval<T&>()++)) {
    tagged_t ret = *this;
    ++(*this);
    return ret;
  }

  constexpr tagged_t& operator--() noexcept(noexcept(--std::declval<T&>())) {
    --value_;
    return *this;
  }

  constexpr tagged_t
  operator--(int) noexcept(noexcept(tagged_t(std::declval<const T&>())) &&
                           noexcept(std::declval<T&>()--))

  {
    tagged_t ret = *this;
    --(*this);
    return ret;
  }

  friend constexpr bool
  operator==(const tagged_t& a,
             const tagged_t& b) noexcept(noexcept(a.value_ == b.value_)) {
    return a.value_ == b.value_;
  }

  friend constexpr auto operator<=>(
      const tagged_t& a,
      const tagged_t& b) noexcept(noexcept(a.value_ <=> b.value_)) = default;

private:
  T value_;
};

#define MAKE_OP(OP)                                                            \
  template <class T, class Tag>                                                \
    requires requires(const T& a, const T& b) { a OP b; }                      \
  constexpr auto operator OP(                                                  \
      const tagged_t<T, Tag>& lhs,                                             \
      const tagged_t<T, Tag>&                                                  \
          rhs) noexcept(noexcept(std::declval<T&>() OP std::declval<T&>())) {  \
    return tagged_t<T, Tag>{lhs.get() OP rhs.get()};                           \
  }

MAKE_OP(+);
MAKE_OP(-);
MAKE_OP(/);
MAKE_OP(*);
MAKE_OP(%);
MAKE_OP(|);
MAKE_OP(^);
MAKE_OP(&);
MAKE_OP(<<);
MAKE_OP(>>);

#undef MAKE_OP

#define MAKE_OP_ASSIGN(OP)                                                     \
  template <class T, class Tag>                                                \
    requires requires(T& a, const T& b) { a OP## = b; }                        \
  constexpr tagged_t<T, Tag>& operator OP##=(                                  \
      tagged_t<T, Tag>& lhs,                                                   \
      const tagged_t<T, Tag>& rhs) noexcept(noexcept(lhs.get()                 \
                                                         OP rhs.get())) {      \
    lhs.get() OP## = rhs.get();                                                \
    return lhs;                                                                \
  }

MAKE_OP_ASSIGN(+);
MAKE_OP_ASSIGN(-);
MAKE_OP_ASSIGN(/);
MAKE_OP_ASSIGN(*);
MAKE_OP_ASSIGN(%);
MAKE_OP_ASSIGN(|);
MAKE_OP_ASSIGN(^);
MAKE_OP_ASSIGN(&);
MAKE_OP_ASSIGN(<<);
MAKE_OP_ASSIGN(>>);

#undef MAKE_OP_ASSIGN

template <class T, class Tag>
  requires requires(const T& a) { +a; }
constexpr auto
operator+(const tagged_t<T, Tag>& v) noexcept(noexcept(+v.get())) {
  return tagged_t<T, Tag>{+v.get()};
}

template <class T, class Tag>
  requires requires(const T& a) { -a; }
constexpr auto
operator-(const tagged_t<T, Tag>& v) noexcept(noexcept(-v.get())) {
  return tagged_t<T, Tag>{-v.get()};
}

template <class T, class Tag>
  requires std::swappable<T>
constexpr void swap(tagged_t<T, Tag>& lhs, tagged_t<T, Tag>& rhs) {
  std::swap(lhs.get(), rhs.get());
}

template <class T, class Tag>
  requires requires(std::ostream& os, const T& val) { os << val; }
std::ostream& operator<<(std::ostream& os, const tagged_t<T, Tag>& val) {
  return os << val.get();
}

template <class T, class Tag>
  requires requires(std::istream& is, T& val) { is >> val; }
std::istream& operator>>(std::istream& is, tagged_t<T, Tag>& val) {
  return is >> val.get();
}

namespace std {
template <class T, class Tag> struct hash<tagged_t<T, Tag>> {
  size_t operator()(const tagged_t<T, Tag>& v) const
      noexcept(noexcept(std::hash<T>{}(v.get()))) {
    return std::hash<T>{}(v.get());
  }
};
} // namespace std

#define MAKE_TAGGED(name, type) using name = tagged_t<type, struct Tag_##name>;
