#include <bits/stdc++.h>

struct digit{
  uint8_t data;
  bool overflow = false;
  digit operator+(const digit rhs) const {
    digit temp;
    temp = ((data + rhs.data));
    
    if(temp.data >= 10){
      temp.overflow = true;
      temp.data -= 10;
    }
    else{
      temp.overflow = false;
    }
    if(overflow || rhs.overflow)
      temp.overflow = true;
    return temp;
  }
  digit operator=(const auto rhs){
    data = static_cast<uint8_t>(rhs);
    return *this;
  }
  bool operator!=(const digit rhs)const{
    return data != rhs.data;
  }
  bool operator<(const digit rhs) const{
    return data < rhs.data;
  }
  digit() : data(0) {}
  digit(auto a) : data(a) {} 
};

auto& operator<<(std::ostream& lhs, const digit rhs){
  lhs << static_cast<int>(rhs.data);
  return lhs;
}

template<std::size_t width>
class big_int : public std::array<digit, width> {};

template<std::size_t width>
big_int<width> operator+(const big_int<width>& lhs, const big_int<width>& rhs){
  big_int<width> ret{};
  uint8_t carry{};
  for(std::size_t i = width - 1; i < width; i--){
    auto sum = lhs[i] + rhs[i] + carry;
    ret[i] = sum;
    ret[i].overflow = false;
    if (sum.overflow) {
      carry = 1; 
    } 
    else {
      carry = 0; 
    }
  }
  return ret;
}
template<std::size_t width>
auto& operator<<(std::ostream& lhs, big_int<width>& rhs){
  bool leading_zero = true;
  for (auto& i: rhs){
    if (leading_zero & (i != 0)){ 
      leading_zero = false;
      lhs << i;
    }
    else if (!leading_zero) {
      lhs << i;
    }
  }
  if (leading_zero) {
    lhs << 0;
  }
  return lhs;
}

int main(){
  constexpr std::size_t max = 1'000'000;
  big_int<static_cast<std::size_t>(max * 0.21)> one{}, zero{};
  *one.rbegin() = 1;
  std::pair nextTwo{zero, one};

  for(std::size_t i = 0; i < max; i++){
    auto p = std::async([](std::size_t max, std::size_t i){
      if(i % (max / 100) == 0) [[unlikely]] {
        std::cout << i / (max / 100) << "% done\n"; 
      }
    }, max, i);
    auto next = nextTwo.first + nextTwo.second;
    nextTwo = std::pair{nextTwo.second, next};
  }
  std::cout << nextTwo.first << '\n';
  return 0;
}
