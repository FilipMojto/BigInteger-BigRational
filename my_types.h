#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <compare>
#include <sstream>
#include <stdint.h>


#define SUPPORT_IFSTREAM 1
#define SUPPORT_ISQRT 1
#define SUPPORT_EVAL 0 // special bonus

class BigInteger {

public:

	// constructors
	BigInteger() : n(0) {};

	BigInteger(int64_t n) : n(n) {};

	BigInteger(const std::string& str) {
		const auto str_len = str.length();

		if (str_len == 0) {
			throw std::invalid_argument("Invalid string value, must be numeric!");
		}

		this->n = BigInteger::to_big_integer(str);
	};

	BigInteger(const BigInteger& other) {
		this->n = other.n;
	};

	BigInteger& operator=(const BigInteger& rhs) {
		this->n = rhs.n;
		return *this;
	};

	const BigInteger& operator+() const {
		return *this;
	};

	BigInteger operator-() const {
		BigInteger copy = *this;

		copy.n = -copy.n;
		return copy;
	};


	// binary arithmetics operators
	BigInteger& operator+=(const BigInteger& rhs) {
		this->n += rhs.n;
		return *this;
	};

	BigInteger& operator-=(const BigInteger& rhs) {
		this->n -= rhs.n;
		return *this;
	};

	//// binary arithmetics operators

	BigInteger& operator*=(const BigInteger& rhs) {
		auto multiplier = this->n;
		auto accumulated_value = 0;

		if (multiplier == 0) {
			this->n = 0;
		}
		else {
			auto additional_value = 1;

			while (abs(multiplier) > 0) {
				auto last_digit = multiplier % 10;

				auto multiplier_2 = rhs.n;
				auto overflow = 0;
				auto cur = 1;

				while (abs(multiplier_2) > 0) {
					auto cur_digit_2 = multiplier_2 % 10;

					accumulated_value += (last_digit * cur_digit_2 * cur * additional_value);

					multiplier_2 /= 10;
					cur *= 10;
				}

				accumulated_value += overflow * cur;

				multiplier /= 10;
				additional_value *= 10;
			}
		}

		this->n = accumulated_value;
		return *this;
	};

	BigInteger& operator/=(const BigInteger& rhs) {
		if (rhs.get_value() == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}
		else if (this->get_value() == 0) {
			this->n = 0;
			return *this;
		}
		else if (rhs.get_value() == 1) {
			return *this;
		}

		auto dividend = this->get_value();
		auto divisor = rhs.get_value();

		// Handle the sign_type of the result
		int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

		// Convert both dividend and divisor to positive values
		dividend = std::abs(dividend);
		divisor = std::abs(divisor);

		// Initialize variables for the algorithm
		int quotient = 0;
		int remainder = 0;

		// Iterate through each digit of the dividend
		for (int i = 31; i >= 0; --i) {
			remainder <<= 1; // Left shift remainder by 1 bit, double its value
			remainder |= (dividend >> i) & 1; // Set the least significant bit of remainder, only if the least significat bit of divident is set

			// if remainder is equal or greater than divisor, we substract the divisor from it and set the corresponding bit of quotient
			if (remainder >= divisor) {
				remainder -= divisor;
				quotient |= (1 << i); // Set the corresponding bit in quotient
			}
		}

		this->n = sign * quotient;
		return *this;
		//return BigInteger(sign_type * quotient);
	};

	BigInteger& operator%=(const BigInteger& rhs) {
		if (rhs.get_value() == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}
		else if (this->get_value() == 0) {
			this->n = 0;
			return *this;
		}
		else if (rhs.get_value() == 1) {
			return *this;
		}

		auto dividend = this->get_value();
		auto divisor = rhs.get_value();

		// Handle the sign_type of the result
		int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

		// Convert both dividend and divisor to positive values
		dividend = std::abs(dividend);
		divisor = std::abs(divisor);

		// Initialize variables for the algorithm
		int quotient = 0;
		int remainder = 0;

		// Iterate through each digit of the dividend
		for (int i = 31; i >= 0; --i) {
			remainder <<= 1; // Left shift remainder by 1 bit, double its value
			remainder |= (dividend >> i) & 1; // Set the least significant bit of remainder, only if the least significat bit of divident is set

			// if remainder is equal or greater than divisor, we substract the divisor from it and set the corresponding bit of quotient
			if (remainder >= divisor) {
				remainder -= divisor;
				quotient |= (1 << i); // Set the corresponding bit in quotient
			}
		}

		this->n = sign * remainder;
		return *this;
	};

	double sqrt() const {

		if (this->n < 0) {
			throw std::runtime_error("Cannot calculate square root for negative numbers!");
		}
		else if (this->n > std::numeric_limits<double>::max()) {
			throw std::runtime_error("Calculated number is greater than possible maximum!");
		}


		return std::sqrt(this->n);
	};

#if SUPPORT_ISQRT == 1

	// we are maintaining the accuracy by casting the result to integer
	BigInteger isqrt() const {
		return BigInteger(static_cast<int>(std::floor(this->sqrt())));
	};
#endif

	// static methods
	static bool is_big_integer(const std::string& str) {
		auto str_len = str.length();
		
		if (str_len == 0) {
			return false;
		}
		
		for (size_t i = 0; i < str_len; i++) {
			auto cur_char = str.at(i);
		
			if (!std::isdigit(cur_char) and !(i == 0 and (cur_char == '-' or cur_char == '+'))) {
				return false;
				//throw std::invalid_argument("Invalid string value, must be numeric!");
			}
		
		}
		
		return true;
	}
	static int64_t to_big_integer(const std::string& str) {
		if (!BigInteger::is_big_integer(str)) {
			throw std::invalid_argument("Invalid string value, must be numeric!");
		}
				
		auto str_len = str.length();
			
		switch (*str.begin()) {
		case '-':
			return -std::stoll(str.substr(1, str_len));
		case '+':
			return std::stoll(str.substr(1, str_len));
		default:
			return std::stoll(str.substr(0, str_len));
		}
	}

	// user interface methods
	int64_t get_value() const {
		return this->n;
	}

	// private class segment
private:
	int64_t n = 0;
};

inline BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
	return BigInteger(lhs.get_value() + rhs.get_value());
};

inline BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
	return BigInteger(lhs.get_value() - rhs.get_value());
};

inline BigInteger operator*(BigInteger lhs, const BigInteger& rhs) {
	
	if (lhs.get_value() == 0 or rhs.get_value() == 0) {
		return BigInteger(0);
	}

	// Convert the numbers to vectors of digits
	std::vector<int> digits1, digits2;

	auto lhs_copy = lhs.get_value();
	auto rhs_copy = rhs.get_value();


	while (abs(lhs_copy) > 0) {
		digits1.push_back(lhs_copy % 10);
		lhs_copy /= 10;
	}

	while (abs(rhs_copy) > 0) {
		digits2.push_back(rhs_copy % 10);
		rhs_copy /= 10;
	}

	// Initialize the result vector with zeros
	std::vector<int64_t> result(digits1.size() + digits2.size(), 0);

	// Perform long multiplication
	for (size_t i = 0; i < digits1.size(); ++i) {
		for (size_t j = 0; j < digits2.size(); ++j) {
			result[i + j] += static_cast<int64_t>(digits1[i]) * digits2[j];
			if (result[i + j] >= 10) {
				result[i + j + 1] += result[i + j] / 10;
				result[i + j] %= 10;
			}
		}
	}

	// Convert the result vector back to a single number
	int64_t finalResult = 0;
	int64_t multiplier = 1;

	for (size_t i = 0; i < result.size(); ++i) {
		finalResult += result[i] * multiplier;
		multiplier *= 10;
	}

	return BigInteger(finalResult);
};


inline BigInteger operator/(BigInteger lhs, const BigInteger& rhs) {
	
	if (rhs.get_value() == 0) {
		throw std::runtime_error("Division by zero is not defined!");
	}
	else if (lhs.get_value() == 0) {
		return BigInteger(0);
	}
	else if (rhs.get_value() == 1) {
		return BigInteger(lhs.get_value());
	}
	
	auto dividend = lhs.get_value();
	auto divisor = rhs.get_value();

	// Handle the sign_type of the result
	int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

	// Convert both dividend and divisor to positive values
	dividend = std::abs(dividend);
	divisor = std::abs(divisor);

	// Initialize variables for the algorithm
	int quotient = 0;
	int remainder = 0;

	// Iterate through each digit of the dividend
	for (int i = 31; i >= 0; --i) {
		remainder <<= 1; // Left shift remainder by 1 bit, double its value
		remainder |= (dividend >> i) & 1; // Set the least significant bit of remainder, only if the least significat bit of divident is set

		// if remainder is equal or greater than divisor, we substract the divisor from it and set the corresponding bit of quotient
		if (remainder >= divisor) {
			remainder -= divisor;
			quotient |= (1 << i); // Set the corresponding bit in quotient
		}
	}

	return BigInteger(sign * quotient);
};



inline BigInteger operator%(BigInteger lhs, const BigInteger& rhs) {

	if (rhs.get_value() == 0) {
		throw std::runtime_error("Division by zero is not defined!");
	}
	else if (lhs.get_value() == 0) {
		return BigInteger(0);
	}
	else if (rhs.get_value() == 1) {
		return BigInteger(lhs.get_value());
	}

	auto dividend = lhs.get_value();
	auto divisor = rhs.get_value();

	// Handle the sign_type of the result
	int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

	// Convert both dividend and divisor to positive values
	dividend = std::abs(dividend);
	divisor = std::abs(divisor);

	// Initialize variables for the algorithm
	int quotient = 0;
	int remainder = 0;

	// Iterate through each digit of the dividend
	for (int i = 31; i >= 0; --i) {
		remainder <<= 1; // Left shift remainder by 1 bit, double its value
		remainder |= (dividend >> i) & 1; // Set the least significant bit of remainder, only if the least significat bit of divident is set

		// if remainder is equal or greater than divisor, we substract the divisor from it and set the corresponding bit of quotient
		if (remainder >= divisor) {
			remainder -= divisor;
			quotient |= (1 << i); // Set the corresponding bit in quotient
		}
	}

	return BigInteger(sign * remainder);
}

std::strong_ordering operator<=>(const BigInteger& lhs, const BigInteger& rhs) {
	if (lhs.get_value() < rhs.get_value()) {
		return std::strong_ordering::less;
	}
	else if (lhs.get_value() > rhs.get_value()) {
		return std::strong_ordering::greater;
	}

	else {
		return std::strong_ordering::equal;
	}

};

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
	return (lhs <=> rhs) == 0;
}


inline std::ostream& operator<<(std::ostream& lhs, const BigInteger& rhs) {
	lhs << rhs.get_value();

	return lhs;
};

#if SUPPORT_IFSTREAM == 1
	
	inline std::istream& operator>>(std::istream& lhs, BigInteger& rhs) {
		
		// firstly, we need to read the first character from the stream in order to process it
		char cur_char = lhs.peek();
		//lhs.get(cur_char);
		
		// variables for sign (+, -) management
		auto sign_type = true;
		auto read_next = false;

		// we are processing the first character here, if it is sign_type (+, -) we set read_next to true
		// and sign_type to false

		switch (cur_char) {
		case '+':
			read_next = true;
			break;
		case '-':
			read_next = true;
			sign_type = false;
			break;
		default:
			break;
		}

	// variables for effective input stream processing, the stringstream is used for
	// efficient string-from-stream building
	std::ostringstream oss;
	bool failbit_ = true;

		
		// here we loop processing individual characters
		while (true) {

			// this statement ensures that potential initial signs are skipped
			if (read_next) {
				lhs.get(cur_char);
				cur_char = lhs.peek();
				read_next = false;
			}

			// firstly, we need to check whether eof() bit wasnt set, in that case we leave the loop
			if (lhs.eof()) {
				break;
			}

			// once a valid digit is found, failbit is set to false and a valid character is
			// inserted into the string stream
			if (std::isdigit(cur_char)) {
				failbit_ = false;
				oss << cur_char;
				lhs.get(cur_char);
				cur_char = lhs.peek();
			}
			else if (oss.str() == "" and cur_char == ' '){
				lhs.get(cur_char);
				cur_char = lhs.peek();
			}
			else {
				break;
			}
		}
		

		// here we set failbit of the stream according to the flag variable
		if (failbit_) {
			lhs.setstate(std::ios::failbit); // Set the failbit
		}
		// here we clear all potential flags set on the stream previously and initialize rhs parameter
		// with the content of stringstream, also using a negative sign if needed
		else {
			lhs.clear();
			rhs = (sign_type) ? BigInteger(std::stoll(oss.str())) : -BigInteger(std::stoll(oss.str()));
		}

		return lhs;

	};
#endif




// ########## BigRational Class Implementation ##########


class BigRational {

public:
	// constructors
	BigRational() : n(0) {};

	BigRational(int64_t a, int64_t b) : n(a / static_cast<double>(b)), numerator(a), denominator(b) {

		if (b == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}

		if (this->denominator < 0) {
			this->numerator = -this->numerator;
			this->denominator = -this->denominator;
		}

		this->normalize_fraction();
	};

	BigRational(const std::string& a, const std::string& b) {
		if (!BigInteger::is_big_integer(a) or !BigInteger::is_big_integer(b)) {
			throw std::invalid_argument("Invalid string value, must be numeric!");
		}

		this->numerator = BigInteger::to_big_integer(a);
		this->denominator = BigInteger::to_big_integer(b);

		if (this->denominator == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}

		if (this->denominator < 0) {
			this->numerator = -this->numerator;
			this->denominator = -this->denominator;
		}

		this->normalize_fraction();
		this->n = this->numerator.get_value() / static_cast<double>(this->denominator.get_value());
	};

	// copying

	BigRational(const BigRational& other) {
		this->numerator = other.get_numerator();
		this->denominator = other.get_denominator();

		this->n = other.n;
	};


	BigRational& operator=(const BigRational& rhs) {
		this->numerator = rhs.get_numerator();
		this->denominator = rhs.get_denominator();
		this->n = rhs.n;
		return *this;
	};

	// unary operators
	const BigRational& operator+() const {
		return *this;
	};

	BigRational operator-() const {
		BigRational copy = *this;
		copy.n = -copy.n;

		copy.numerator = -copy.numerator;

		return copy;
	};

	// binary arithmetics operators
	BigRational& operator+=(const BigRational& rhs) {

		auto denominator = this->get_denominator() * rhs.get_denominator();
		auto numerator = (denominator / this->get_denominator()) * this->get_numerator() + (denominator / rhs.get_denominator()) * rhs.get_numerator();

		this->set_value(numerator, denominator);

		return *this;
	};

	BigRational& operator-=(const BigRational& rhs) {
		auto denominator = this->get_denominator() * rhs.get_denominator();
		auto numerator = (denominator / this->get_denominator()) * this->get_numerator() - (denominator / rhs.get_denominator()) * rhs.get_numerator();
		
		this->set_value(numerator, denominator);
		return *this;
	};

	BigRational& operator*=(const BigRational& rhs) {
		this->set_value((this->get_numerator() * rhs.get_numerator()).get_value(), (this->get_denominator() * rhs.get_denominator()).get_value());
		return *this;
	};

	BigRational& operator/=(const BigRational& rhs) {
		this->set_value((this->get_numerator() * rhs.get_denominator()).get_value(), (this->get_denominator() * rhs.get_numerator()).get_value());
		return *this;
	};

	double sqrt() const {

		std::cout << std::numeric_limits<double>::max() << std::endl;
		if (this->n < 0) {
			throw std::runtime_error("Cannot calculate square root for negative numbers!");
		}
		else if (this->n > std::numeric_limits<double>::max()) {
			throw std::runtime_error("Calculated number is greater than possible maximum!");
		}


		return std::sqrt(this->n);
	};

#if SUPPORT_ISQRT == 1
	BigInteger isqrt() const {
		return BigInteger(static_cast<int>( std::floor( this->numerator.isqrt().get_value() / this->denominator.isqrt().get_value())));
	};
#endif

	// static methods
	static // Function to calculate the GCD of two numbers
		int gcd(int a, int b) {
		while (b != 0) {
			int temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

	static void normalize_fraction(int64_t& numerator, int64_t& denominator) {
		int commonDivisor = gcd(numerator, denominator);
		
		// Divide both numerator and denominator by their GCD
		numerator /= commonDivisor;
		denominator /= commonDivisor;
	}

	// user interface methods
	double get_value() const {
		return this->n;
	};

	BigInteger get_numerator() const {
		return this->numerator;
	}

	BigInteger get_denominator() const {
		return this->denominator;
	}

private:
	double n = 0;
	BigInteger numerator = BigInteger(0);
	BigInteger denominator = BigInteger(1);
	
	// class utility methods
	void set_value(const BigInteger& numerator, const BigInteger& denominator) {
		if (denominator.get_value() == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}

		this->numerator = numerator;
		this->denominator = denominator;

		if (this->denominator < 0) {
			this->numerator = -this->numerator;
			this->denominator = -this->denominator;
		}

		this->normalize_fraction();
		this->n = this->numerator.get_value() / static_cast<double>(this->denominator.get_value());
	}

	void set_value(const int64_t numerator, const int64_t denominator) {
		if (denominator == 0) {
			throw std::runtime_error("Division by zero is not defined!");
		}

		this->numerator = BigInteger(numerator);
		this->denominator = BigInteger(denominator);

		this->normalize_fraction();

		this->n = this->numerator.get_value() / static_cast<double>(this->denominator.get_value());
	}

	void normalize_fraction() {
		int commonDivisor = gcd(this->numerator.get_value(), this->denominator.get_value());

		// Divide both numerator and denominator by their GCD
		this->numerator /= abs(commonDivisor);
		this->denominator /= abs(commonDivisor);
	}
};

inline BigRational operator+(BigRational lhs, const BigRational& rhs) {

	auto denominator = lhs.get_denominator() * rhs.get_denominator();
	auto numerator = (denominator / lhs.get_denominator()) * lhs.get_numerator() + (denominator / rhs.get_denominator()) * rhs.get_numerator();

	return BigRational(numerator.get_value(), denominator.get_value());
};

inline BigRational operator-(BigRational lhs, const BigRational& rhs) {
	auto denominator = lhs.get_denominator() * rhs.get_denominator();
	auto numerator = (denominator / lhs.get_denominator()) * lhs.get_numerator() - (denominator / rhs.get_denominator()) * rhs.get_numerator();

	return BigRational(numerator.get_value(), denominator.get_value());
};

inline BigRational operator*(BigRational lhs, const BigRational& rhs) {
	return BigRational((lhs.get_numerator() * rhs.get_numerator()).get_value(), (lhs.get_denominator() * rhs.get_denominator()).get_value());
};

inline BigRational operator/(BigRational lhs, const BigRational& rhs) {

	std::cout << (lhs.get_numerator() * rhs.get_denominator()).get_value() << std::endl;
	std::cout << (lhs.get_denominator() * rhs.get_numerator()).get_value() << std::endl;

	return BigRational((lhs.get_numerator() * rhs.get_denominator()).get_value(), (lhs.get_denominator() * rhs.get_numerator()).get_value());
};

std::strong_ordering operator<=>(const BigRational& lhs, const BigRational& rhs) {
	if (lhs.get_value() < rhs.get_value()) {
		return std::strong_ordering::less;
	}
	else if (lhs.get_value() > rhs.get_value()) {
		return std::strong_ordering::greater;
	}
	
	else{
		return std::strong_ordering::equal;
	}

};

bool operator==(const BigRational& lhs, const BigRational& rhs) {
	return (lhs <=> rhs) == 0;
}

inline std::ostream& operator<<(std::ostream& lhs, const BigRational& rhs) {
	return (rhs.get_denominator() == 1) ? lhs << rhs.get_numerator() : lhs << rhs.get_numerator() << '/' << rhs.get_denominator();
}

#if SUPPORT_IFSTREAM == 1
// this should behave exactly the same as reading int with respect to 
// whitespace, consumed characters etc...
	inline std::istream& operator>>(std::istream& lhs, BigRational& rhs) {
		// firstly, we need to read the first character from the stream in order to process it
		char cur_char = lhs.peek();

		//lhs.get(cur_char);

		// variables for sign (+, -) management
		auto sign_type = true;
		auto read_next = false;

		// we are processing the first character here, if it is sign_type (+, -) we set read_next to true
		// and sign_type to false

		switch (cur_char) {
		case '+':
			read_next = true;
			break;
		case '-':
			read_next = true;
			sign_type = false;
			break;
		default:
			break;
		}

		// variables for effective input stream processing, the stringstream is used for
		// efficient string-from-stream building
		std::ostringstream numerator;
		std::ostringstream denominator;
		bool failbit_ = true;
		bool denom_f = false;


		// here we loop processing individual characters
		while (true) {

			// this statement ensures that potential initial signs are skipped
			if (read_next) {
				lhs.get(cur_char);
				cur_char = lhs.peek();

				//lhs.get(cur_char);
				read_next = false;
			}

			// firstly, we need to check whether eof() bit wasnt set, in that case we leave the loop
			if (cur_char == '\n' or lhs.eof()) {
				break;
			}
			

			// once a valid digit is found, failbit is set to false and a valid character is
			// inserted into a proper stringstream
			if (std::isdigit(cur_char)) {
				failbit_ = false;

				//here we are already building denominator
				if (denom_f) {
					denominator << cur_char;
				}
				// in this case / hasnt been processed yet, so we are still building numerator
				else {
					numerator << cur_char;
				}

				lhs.get(cur_char);
				cur_char = lhs.peek();
			}

			// this is the case, when we can move from numerator to denominator by setting oss_2 flag
			else if (!numerator.str().empty() and cur_char == '/') {
				denom_f = true;
				lhs.get(cur_char);
				cur_char = lhs.peek();
			}

			// in this case, the first character in denominator is not numerical, so we check whether it
			// is not a sign
			// otherwise we initialize denominator to 1
			else if (denom_f and denominator.str().empty()) {

				switch (cur_char) {
				case '-':
					sign_type = (sign_type) ? false : true;

					lhs.get(cur_char);
					cur_char = lhs.peek();
					break;
				case '+':
					lhs.get(cur_char);
					cur_char = lhs.peek();
				default:
					denominator << '1';
					break;
				}
			
			}
			else if (numerator.str().empty() and cur_char == ' ') {
				lhs.get(cur_char);
				cur_char = lhs.peek();
			}
			else {
				break;
			}
		}

		//if numerator is not specified, we set failbit_ flag, this is invalid
		if (numerator.str() == "") {
			failbit_ = true;
		}

		// if denominator is not specified, we initialize it to 1, this is valid
		if (denominator.str() == "") {
			denominator << '1';
		}


		// here we set failbit of the stream according to the flag variable
		if (failbit_) {
			lhs.setstate(std::ios::failbit); // Set the failbit
		}
		// here we clear all potential flags set on the stream previously and initialize rhs parameter
		// with the content of stringstream, also using a negative sign if needed
		else {
			lhs.clear();
			rhs = (sign_type) ? BigRational(std::stoll(numerator.str()), std::stoll(denominator.str())) : -BigRational(std::stoll(numerator.str()), std::stoll(denominator.str()));
		}

		return lhs;
	};

#endif