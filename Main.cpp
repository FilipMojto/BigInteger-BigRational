#include <iostream>
#include "my_types.h"
#include <nlohmann/json.hpp>


using json = nlohmann::json;


BigInteger eval(const json& json_) {
	
	BigInteger left_val, right_val;

	if (json_.find("left") == json_.end() or json_.find("right") == json_.end() or json_.find("op") == json_.end() or !json_["op"].is_string()) {
		throw std::runtime_error("Provided JSON object contains invalid structure!");
	}

	if (json_["left"].is_object()) {
		left_val = eval(json_["left"]);
	}
	else if (json_["left"].is_string()) {
		left_val = BigInteger(static_cast<std::string>(json_["left"]));
	}
	else if (json_["left"].is_number_integer()) {
		left_val = BigInteger(static_cast<int64_t>(json_["left"]));
	}
	else {
		throw std::runtime_error("Unsupported value type for the key 'left'.");
	}

	if (json_.find("right") != json_.end() && json_["right"].is_object()) {
		right_val = eval(json_["right"]);
	}
	else if (json_["right"].is_string()) {
		right_val = BigInteger(static_cast<std::string>(json_["right"]));
	}
	else if (json_["right"].is_number_integer()) {
		right_val = BigInteger(static_cast<int64_t>(json_["right"]));
	}
	else {
		throw std::runtime_error("Unsupported value type for the key 'right'.");
	}

	switch (static_cast<std::string> (json_["op"]).at(0)) {
	case '+':
		return left_val + right_val;
	case '-':
		return left_val - right_val;
	case '*':
		return left_val * right_val;
	case '/':
		return left_val / right_val;
	case '%':
		return left_val / right_val;
	default:
		throw std::runtime_error("Unsupported operand!");
	}

	//return BigInteger(0);
}

int main(char* argv[], int argc) {
	std::cout << "Executing the program..." << std::endl;
	
	const json myJson = {
		{"op", "+"},
		{"left", 123},
		{"right", {
			{"op","*"},
			{"left", "12345678901234567"},
			{"right", {
				{"op", "%"},
				{"left", "34"},
				{"right", 1}
			}}
		}}
	};
	//const json myJson = {

	//	{"op", "+"},
	//	{"left", 123},

	//	{"right", {
	//			{"op", "-"},
	//			{"left", "24"},
	//			{"right", {
	//				{"op", "*"},
	//				{"left", 54},
	//				{"right", "32"}
	//			}}
	//		}
	//	}
	//	//{"name", "John"},
	//	//{"age", 30},
	//	//{"city", "New York"}
	//};

	
	auto res = eval(myJson);


	//auto cur = myJson["left"];
	//
	//do {
	//	std::cout << "NOW" << std::endl;

	//	// Check if the current value is an object before accessing "left"
	//	if (cur.find("left") != cur.end() && cur["left"].is_object()) {
	//		cur = cur["left"];
	//	}
	//	else {
	//		break; // Exit the loop if "left" is not an object
	//	}

	//} while (true);

	////do {

	////	std::cout << "NOW" << std::endl;

	////} while ((cur = cur["left"]).type() == json_::value_t::object);

	//auto cur_2 = myJson["right"];
	//cur_2.find("right");
	//cur_2.end();
	//std::cout << cur_2["right"].is_object();
	//do {
	//	std::cout << "HEHE" << std::endl;

	//	// Check if the current value is an object before accessing "left"
	//	if (cur_2.find("right") != cur_2.end() && cur_2["right"].is_object()) {
	//		cur_2 = cur_2["right"];
	//	}
	//	else {
	//		break; // Exit the loop if "left" is not an object
	//	}

	//} while (true);

	//if (myJson["name"].type() == json_::value_t::string) {
	//	std::cout << "Name is a string." << std::endl;
	//}

	//if (myJson["age"].type() == json_::value_t::number_integer) {
	//	std::cout << "Age is an integer." << std::endl;
	//}

	//if (myJson["address"].type() == json_::value_t::object) {
	//	std::cout << "Address is an object." << std::endl;
	//}

	//while(myJson)
	//std::string haha = "haha" < "AHA";
	


	//auto bi_1 = BigInteger(10015434334343443434334443);
	//auto bi_2 = BigInteger(1200434334343443333333l);

	//auto res = bi_1 * bi_2;



	//std::cout << bi_1 << std::endl;
	//std::cout << bi_2 << std::endl;

	//auto bi_3 = BigInteger();
	////auto i = 0;

	//std::cin >> bi_3;

	////auto bi_4 = BigInteger();
	////std::cin >> bi_4;

	//std::cout << std::cin.fail() << std::endl;

	//auto test = 0;

	//std::cin >> bi_1;


	//std::cout << br_1.sqrt() << std::endl;

	//auto result = (br_1 <=> br_2);
	//auto haha = (br_1 == br_2);
	////auto haha2 = (br_1 != br_2);
	//auto haha3 = (br_1 < br_2);
	//auto haha4 = (br_1 <= br_2);
	//auto haha5 = (br_1 >= br_2);
	//auto haha6 = (br_1 > br_2);


	//auto i = 0;
	//auto j = 2;

	//std::cout << (i + j) << std::endl;

	//BigInteger bi = BigInteger("5638");
	//BigInteger bi_copy = BigInteger("-750");

	//auto res = bi * bi_copy;
	//auto res_2 = bi + bi_copy;
	//auto res_3 = bi - bi_copy;

	
	//auto dividend = BigInteger(1015);
	//auto divisor = BigInteger(12);

	//auto division = dividend / divisor;
	//auto remainder = dividend % divisor;


	//auto test = 0;
	//std::string rest = "";


	//std::cin >> test;
	//std::cin >> rest;

	////
	//BigRational br_1 = BigRational("1", "-7");
	//////const BigRational br_2 = BigRational(25, -1);

	////std::string rest = "";
	////
	//std::cin >> br_1;

	//auto res_1 = br_1.isqrt();
	//auto res_2 = br_1.sqrt();

	//std::cin >> rest;

	//std::string rest = "";

	//std::cin >> rest;

	//std::cout << br_1 << std::endl;
	//std::cout << br_2 << std::endl;
	//auto result = br_1 + br_2;
	//auto result_2 = br_1 - br_2;
	//auto result_3 = br_1 * br_2;
	//auto result_4 = br_1 / br_2;

	//std::cout << br_1.sqrt() << std::endl;

	//result += result;
	//result_2 -= result_2;
	//result_3 *= result_3;
	//result_4 /= result_4;

	//auto haha = (br_1 == br_2);
	//auto haha2 = (br_1 != br_2);
	//auto haha3 = (br_1 < br_2);
	//auto haha4 = (br_1 <= br_2);
	//auto haha5 = (br_1 >= br_2);
	//auto haha6 = (br_1 > br_2);

	//auto result_3 = br_1 * br_2;
	//auto result_4 = br_1 / br_2;


	//auto dividend = +1015;
	//auto divisor = +12;
	////std::cout << 1015 / 12 << std::endl;
	////std::cout << 1015 % 12 << std::endl;

	//int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

	//int remainder = 0;

	//auto moved = remainder <<= 1;

	std::cout << "Terminating the program..." << std::endl;
	return 0;
}