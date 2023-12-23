//#include <stdint.h>
//#include <stdexcept>
//
//#include "my_types.h"
//
//
//// --- IMPLEMENTATION OF BigInteger CLASS ---
//
//
////BigInteger::BigInteger(): n(0) {};
//
//
//BigInteger::BigInteger(int64_t n) : n(n) {};
//
//BigInteger::BigInteger(const std::string& str) {
//	const auto str_len = str.length();
//
//	if (str_len == 0) {
//		throw std::invalid_argument("Invalid string value, must be numeric!");
//	}
//
//	this->n = BigInteger::to_big_integer(str);
//};
//
//BigInteger::BigInteger(const BigInteger& other) {
//	this->n = other.n;
//};
//
//BigInteger& BigInteger::operator=(const BigInteger& rhs) {
//	this->n = rhs.n;
//	return *this;
//};
//
//const BigInteger& BigInteger::operator+() const {
//	return *this;
//};
//
//BigInteger BigInteger::operator-() const {
//	BigInteger copy = *this;
//
//	copy.n = -copy.n;
//	return copy;
//};
//
//// binary arithmetics operators
//BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
//	this->n += rhs.n;
//	return *this;
//};
//
//BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
//	this->n -= rhs.n;
//	return *this;
//};
//
////BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
////	auto multiplier = this->n;
////	auto accumulated_value = 0;
////
////	if (multiplier == 0) {
////		this->n = 0;
////	}
////	else {
////		auto additional_value = 1;
////
////		while (abs(multiplier) > 0) {
////			auto last_digit = multiplier % 10;
////
////			auto multiplier_2 = rhs.n;
////			auto overflow = 0;
////			auto cur = 1;
////
////			while (abs(multiplier_2) > 0) {
////				auto cur_digit_2 = multiplier_2 % 10;
////
////				accumulated_value += (last_digit * cur_digit_2 * cur * additional_value);
////
////				multiplier_2 /= 10;
////				cur *= 10;
////			}
////
////			accumulated_value += overflow * cur;
////
////			multiplier /= 10;
////			additional_value *= 10;
////		}
////	}
////
////	this->n = accumulated_value;
////	return *this;
////};
//
//BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
//
//	return *this;
//};
//
//BigInteger& BigInteger::operator%=(const BigInteger& rhs) {
//	return *this;
//};
//
//bool BigInteger::is_big_integer(const std::string& str) {
//	auto str_len = str.length();
//
//	if (str_len == 0) {
//		return false;
//	}
//
//	for (size_t i = 0; i < str_len; i++) {
//		auto cur_char = str.at(i);
//
//		if (!std::isdigit(cur_char) and !(i == 0 and (cur_char == '-' or cur_char == '+'))) {
//			return false;
//			//throw std::invalid_argument("Invalid string value, must be numeric!");
//		}
//
//	}
//
//	return true;
//};
//
//int64_t BigInteger::to_big_integer(const std::string& str) {
//	
//	if (!BigInteger::is_big_integer(str)) {
//		throw std::invalid_argument("Invalid string value, must be numeric!");
//	}
//	
//	auto str_len = str.length();
//
//	switch (*str.begin()) {
//	case '-':
//		return -std::stoll(str.substr(1, str_len));
//	case '+':
//		return std::stoll(str.substr(1, str_len));
//	default:
//		return std::stoll(str.substr(0, str_len));
//	}
//};
//
//
//int64_t BigInteger::get_value() const{
//	return this->n;
//}
//
//
//
//
//// --- IMPLEMENTATION Of BigRational CLASS ---
//
//BigRational::BigRational() : n(0) {};
//
//BigRational::BigRational(int64_t a, int64_t b) : n(a/b) {};
//
//BigRational::BigRational(const std::string& a, const std::string& b) {
//	if (!BigInteger::is_big_integer(a) or !BigInteger::is_big_integer(b)) {
//		throw std::invalid_argument("Invalid string value, must be numeric!");
//	}
//
//	this->n = BigInteger::to_big_integer(a) / BigInteger::to_big_integer(b);
//};
//
//BigRational::BigRational(const BigRational& other) {
//	this->n = other.n;
//};
//
//BigRational& BigRational::operator=(const BigRational& rhs) {
//	this->n = rhs.n;
//	return *this;
//};
//
//const BigRational& BigRational::operator+() const {
//	return *this;
//};
//
//BigRational BigRational::operator-() const {
//	BigRational copy = *this;
//	copy.n = -copy.n;
//
//	return copy;
//};
//
//// binary arithmetics operators
//BigRational& BigRational::operator+=(const BigRational& rhs) {
//	BigRational copy = *this;
//
//	copy.n += rhs.n;
//	return copy;
//};
//
//BigRational& BigRational::operator-=(const BigRational& rhs) {
//	BigRational copy = *this;
//
//	copy.n -= rhs.n;
//	return copy;
//};
//
//BigRational& BigRational::operator*=(const BigRational& rhs) {
//	BigRational copy = *this;
//
//	auto multiplier = copy.n;
//
//
//
//
//	return copy;
//};
//
//BigRational& BigRational::operator/=(const BigRational& rhs) {
//	return *this;
//};
//
//double BigRational::get_value() const {
//	return this->n;
//};