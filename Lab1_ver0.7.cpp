#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>
#include <map>

using namespace std;
using namespace std::chrono;
using namespace System::Globalization; // ��� NumberStyles::AllowHexSpecifier
using namespace System::Numerics;
using namespace System;

void input(string message, string el)  // ���� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // �������� ���������� �������
	SetConsoleTextAttribute(hStdOut, 7);  // ������ ���� ������ �� �����
	cout << message;  // ������� ���������
	SetConsoleTextAttribute(hStdOut, 15);  // ������ ���� ������ �� �����
	cin >> el; // ������ �������
}

void print(string message, BigInteger el)  // ����� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // �������� ���������� �������
	SetConsoleTextAttribute(hStdOut, 7);  // ������ ���� ������ �� �����
	cout << message;  // ������� ���������
	SetConsoleTextAttribute(hStdOut, 15);  // ������ ���� ������ �� �����
	Console::WriteLine(el);  // ������� �������
}

void print(string message, string el)  // ����� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // �������� ���������� �������
	SetConsoleTextAttribute(hStdOut, 7);  // ������ ���� ������ �� �����
	cout << message;  // ������� ���������
	SetConsoleTextAttribute(hStdOut, 15);  // ������ ���� ������ �� �����
	cout << el << endl;  // ������� �������
}
string elapsedTime(time_point<system_clock> start, time_point<system_clock> end)  // ��������������� ����� � ������
{
	int count = duration_cast<microseconds>(end - start).count();  // ������� ��������� �����
	return count > 1000 ? to_string(count / 1000) + " ��." : to_string(count) + " ���.";  // ���������� ������
}

long elapsedTime2(time_point<system_clock> start, time_point<system_clock> end)  // ��������������� ����� � ������
{
	return duration_cast<microseconds>(end - start).count();  // ���������� ��������� ����� � ���
}

static BigInteger mod(BigInteger a, BigInteger b)
{
	if (a > BigInteger(0))  // ���� ������� ������ 0
		return a % b;  // ���������� ������ a �� b
	if ((a % b) != BigInteger(0))  // ���� ������ �� ����� 0
		// ���������� ������� �� �������
		return BigInteger::Subtract(BigInteger::Multiply(BigInteger::Add(BigInteger::Divide(BigInteger::Abs(a),
			b), BigInteger(1)), b), BigInteger::Abs(a));
	return 0;  // ���������� 0
}

void print(BigInteger a, BigInteger b, BigInteger c, BigInteger mod_amount) {
	BigInteger result;
	time_point<system_clock> start, end;  // ���������� ��� ��������� �������

	print("������ ������� (a): ", a);
	print("������ ������� (b): ", b);
	print("������ ������� (c): ", c);
	print("������ (mod): ", mod_amount);
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger(0), BigInteger(1));
	end = system_clock::now();

	start = system_clock::now();
	c = mod(c, mod_amount);
	end = system_clock::now();

	print("������ ������� �� ������:", c);
	print("����� ������ �������� ������ �� ������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Add(c, a), mod_amount);
	end = system_clock::now();

	print("����� ������� � �������� �� ������: ", result);
	print("����� ������ �������� ��������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Subtract(a, b), mod_amount);
	end = system_clock::now();

	print("������� ������� �������� � ������� �� ������: ", result);
	print("����� ������ �������� �������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Multiply(a, b), mod_amount);
	end = system_clock::now();

	print("��������� ������� �������� �� ������ �� ������: ", result);
	print("����� ������ �������� ���������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Pow(a, 2), mod_amount);
	end = system_clock::now();

	print("���������� ������� �������� � ������� �� ������ (��� �������): ", result);
	print("����� ������ �������� ���������� � ������� ������� ��������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = BigInteger::ModPow(a, BigInteger(2), mod_amount);
	end = system_clock::now();

	print("���������� ������� �������� � ������� �� ������ (���������� �������): ", result);
	print("����� ������ �������� ���������� � ������� ������� ��������: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = BigInteger::Divide(a, b);
	end = system_clock::now();

	print("����� ����� �� ������� a �� b: ", result);
	print("����� ������ �������� �������: ", elapsedTime(start, end));
	cout << endl;

	print("���� �� ������������ (�������� ����������������): ", "");
	print("��� ������ ������� (a): ", a);
	print("��� ������ ������� (b): ", b);
	print("��� ������ ������� (c): ", BigInteger::Subtract(c, BigInteger(1)));
	print("��������� (a+b)*c : ", mod(BigInteger::Multiply(BigInteger::Add(a, b), BigInteger::Subtract(c, BigInteger(1))), mod_amount));
	print("��������� b*c+c*a : ", mod(BigInteger::Add(BigInteger::Multiply(b, BigInteger::Subtract(c, BigInteger(1))), BigInteger::Multiply(BigInteger::Subtract(c, BigInteger(1)), a)), mod_amount));
	cout << endl;
}

void average_time_count(BigInteger a, BigInteger b, BigInteger mod_amount, BigInteger iter_amount) {
	BigInteger num_iter = BigInteger(0);
	BigInteger result;
	BigInteger average_time_count_add = BigInteger(0);
	BigInteger average_time_count_sub = BigInteger(0);
	BigInteger average_time_count_mul = BigInteger(0);
	BigInteger average_time_count_div = BigInteger(0);
	BigInteger average_time_count_powb = BigInteger(0);
	BigInteger average_time_count_pow2 = BigInteger(0);
	BigInteger average_time_count_pow2_rem = BigInteger(0);
	//---------------------------------------------------
	BigInteger average_time_count_add_my = BigInteger(0);
	BigInteger average_time_count_sub_my = BigInteger(0);
	BigInteger average_time_count_mul_my = BigInteger(0);
	BigInteger average_time_count_div_my = BigInteger(0);
	BigInteger average_time_count_pow2_my = BigInteger(0);
	time_point<system_clock> start, end;  // ���������� ��� ��������� �������
	start = system_clock::now();
	a = mod(a, mod_amount);
	end = system_clock::now();

	while (BigInteger::Compare(num_iter, iter_amount) != 0) { // ���� �� ������� iter_amount ��������, ������

		start = system_clock::now();
		result = BigInteger::Remainder(BigInteger::Add(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_add = BigInteger::Add(average_time_count_add, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Remainder(BigInteger::Subtract(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_sub = BigInteger::Add(average_time_count_sub, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Remainder(BigInteger::Multiply(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_mul = BigInteger::Add(average_time_count_mul, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Remainder(BigInteger::Divide(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_div = BigInteger::Add(average_time_count_div, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::ModPow(a, 2, mod_amount);
		end = system_clock::now();
		average_time_count_pow2 = BigInteger::Add(average_time_count_pow2, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Remainder(BigInteger::Pow(a, 2), mod_amount);
		end = system_clock::now();
		average_time_count_pow2_rem = BigInteger::Add(average_time_count_pow2_rem, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::ModPow(a, b, mod_amount);
		end = system_clock::now();
		average_time_count_powb = BigInteger::Add(average_time_count_powb, BigInteger(elapsedTime2(start, end)));

		// -------------With my func "mod":
		start = system_clock::now();
		result = mod(BigInteger::Add(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_add_my = BigInteger::Add(average_time_count_add_my, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = mod(BigInteger::Subtract(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_sub_my = BigInteger::Add(average_time_count_sub_my, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = mod(BigInteger::Multiply(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_mul_my = BigInteger::Add(average_time_count_mul_my, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = mod(BigInteger::Divide(a, b), mod_amount);
		end = system_clock::now();
		average_time_count_div_my = BigInteger::Add(average_time_count_div_my, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = mod(BigInteger::Pow(a, 2), mod_amount);
		end = system_clock::now();
		average_time_count_pow2_my = BigInteger::Add(average_time_count_pow2_my, BigInteger(elapsedTime2(start, end)));

		//a = BigInteger::Add(a, BigInteger(1));
		//b = BigInteger::Add(b, BigInteger(1));
		num_iter++;
	}
	//average_time_count_add = BigInteger::Divide(average_time_count_add, BigInteger(iter_amount));
	//average_time_count_sub = BigInteger::Divide(average_time_count_sub, BigInteger(iter_amount));
	//average_time_count_mul = BigInteger::Divide(average_time_count_mul, BigInteger(iter_amount));
	//average_time_count_div = BigInteger::Divide(average_time_count_div, BigInteger(iter_amount));
	if (average_time_count_add > BigInteger(1000)) 
		print("����� ������ �������� Add (� ��): ", BigInteger::Divide(average_time_count_add, BigInteger(1000)));
	else print("����� ������ �������� Add (� ���): ", average_time_count_add);

	if (average_time_count_add_my > BigInteger(1000))
		print("����� ������ �������� Add (my mod_func, � ��): ", BigInteger::Divide(average_time_count_add_my, BigInteger(1000)));
	else print("����� ������ �������� Add (my mod_func, � ���): ", average_time_count_add_my);

	if (average_time_count_sub > BigInteger(1000))
		print("����� ������ �������� Subtract (� ��): ", BigInteger::Divide(average_time_count_sub, BigInteger(1000)));
	else print("����� ������ �������� Subtract (� ���): ", average_time_count_sub);

	if (average_time_count_sub_my > BigInteger(1000))
		print("����� ������ �������� Subtract (my mod_func, � ��): ", BigInteger::Divide(average_time_count_sub_my, BigInteger(1000)));
	else print("����� ������ �������� Subtract (my mod_func, � ���): ", average_time_count_sub_my);
	//--------------------Multiply--------------------------------------
	if (average_time_count_mul > BigInteger(1000000))
		print("����� ������ �������� Multiply (� �): ", BigInteger::Divide(average_time_count_mul, BigInteger(1000000)));
	else 
		if (average_time_count_mul > BigInteger(1000))
			print("����� ������ �������� Multiply (� ��): ", BigInteger::Divide(average_time_count_mul, BigInteger(1000)));
		else print("����� ������ �������� Multiply (� ���): ", average_time_count_mul);
	//---------------------Multiply(My mod_func)------------------------
	if (average_time_count_mul_my > BigInteger(1000000))
		print("����� ������ �������� Multiply (my mod_func, � �): ", BigInteger::Divide(average_time_count_mul_my, BigInteger(1000000)));
	else
		if (average_time_count_mul_my > BigInteger(1000))
			print("����� ������ �������� Multiply (my mod_func, � ��): ", BigInteger::Divide(average_time_count_mul_my, BigInteger(1000)));
		else print("����� ������ �������� Multiply (my mod_func, � ���): ", average_time_count_mul_my);
	//-------------------------------------------------------------------
	if (average_time_count_div > BigInteger(1000))
		print("����� ������ �������� Divide (� ��): ", BigInteger::Divide(average_time_count_div, BigInteger(1000)));
	else print("����� ������ �������� Divide (� ���): ", average_time_count_div);

	if (average_time_count_div_my > BigInteger(1000))
		print("����� ������ �������� Divide (my mod_func, � ��): ", BigInteger::Divide(average_time_count_div_my, BigInteger(1000)));
	else print("����� ������ �������� Divide (my mod_func, � ���): ", average_time_count_div_my);
	//---------------------------ModPow----------------------------------------
	if (average_time_count_pow2 > BigInteger(1000000))
		print("����� ������ �������� ModPow (a^2, � �): ", BigInteger::Divide(average_time_count_pow2, BigInteger(1000000)));
	else 
		if (average_time_count_pow2 > BigInteger(1000))
			print("����� ������ �������� ModPow (a^2, � ��): ", BigInteger::Divide(average_time_count_pow2, BigInteger(1000)));
		else print("����� ������ �������� ModPow (a^2, � ���): ", average_time_count_pow2);
	//----------------------------Pow(Rem_func)------------------------------------
	if (average_time_count_pow2_rem > BigInteger(1000000))
		print("����� ������ �������� Pow (a^2, Rem_func, � �): ", BigInteger::Divide(average_time_count_pow2_rem, BigInteger(1000000)));
	else
		if (average_time_count_pow2_rem > BigInteger(1000))
			print("����� ������ �������� Pow (a^2, Rem_func, � ��): ", BigInteger::Divide(average_time_count_pow2_rem, BigInteger(1000)));
		else print("����� ������ �������� Pow (a^2, Rem_func, � ���): ", average_time_count_pow2_rem);
	//----------------------------Pow(my mod_func)------------------------------------
	if (average_time_count_pow2_my > BigInteger(1000000))
		print("����� ������ �������� Pow (a^2, my mod_func, � �): ", BigInteger::Divide(average_time_count_pow2_my, BigInteger(1000000)));
	else 
		if (average_time_count_pow2_my > BigInteger(1000))
			print("����� ������ �������� Pow (a^2, my mod_func, � ��): ", BigInteger::Divide(average_time_count_pow2_my, BigInteger(1000)));
		else print("����� ������ �������� Pow (a^2, my mod_func, � ���): ", average_time_count_pow2_my);
	//----------------------------ModPow (a^b)-----------------------------------------
	if (average_time_count_powb > BigInteger(1000000))
		print("����� ������ �������� ModPow (a^b, � �): ", BigInteger::Divide(average_time_count_powb, BigInteger(1000000)));
	else 
		if (average_time_count_powb > BigInteger(1000))
			print("����� ������ �������� ModPow (a^b, � ��): ", BigInteger::Divide(average_time_count_powb, BigInteger(1000)));
		else print("����� ������ �������� ModPow (a^b, � ���): ", average_time_count_powb);
}

void main()
{
	setlocale(LC_ALL, "rus");  // ��������� ���������
	// ���������� (seed)
	BigInteger a_256 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 256), BigInteger(50000000000));
	BigInteger b_256 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 256), BigInteger(10000000000));
	BigInteger c_256 = BigInteger::Add(BigInteger::Pow(BigInteger(2), 256), BigInteger(500));

	BigInteger a_512 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 512), BigInteger(50000000000));
	BigInteger b_512 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 512), BigInteger(10000000000));
	BigInteger c_512 = BigInteger::Add(BigInteger::Pow(BigInteger(2), 512), BigInteger(500));

	BigInteger a_1024 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 1024), BigInteger(50000000000));
	BigInteger b_1024 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 1024), BigInteger(10000000000));
	BigInteger c_1024 = BigInteger::Add(BigInteger::Pow(BigInteger(2), 1024), BigInteger(500));

	BigInteger a_2048 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 2048), BigInteger(50000000000));
	BigInteger b_2048 = BigInteger::Subtract(BigInteger::Pow(BigInteger(2), 2048), BigInteger(10000000000));
	BigInteger c_2048 = BigInteger::Add(BigInteger::Pow(BigInteger(2), 2048), BigInteger(500));

	// ������
	BigInteger mod_256 = BigInteger::Pow(BigInteger(2), 256);
	BigInteger mod_512 = BigInteger::Pow(BigInteger(2), 512);
	BigInteger mod_1024 = BigInteger::Pow(BigInteger(2), 1024);
	BigInteger mod_2048 = BigInteger::Pow(BigInteger(2), 2048);

	/*print(a_256, b_256, c_256, mod_256);
	cout << endl;
	print(a_512, b_512, c_512, mod_512);
	cout << endl;
	print(a_1024, b_1024, c_1024, mod_1024);
	cout << endl;
	print(a_2048, b_2048, c_2048, mod_2048);*/
	int sizeIter_amount = 6; // 1 000,   10 000,   100 000,   1 000 000,   10 000 000,   1 000 000 000
	int *Iter_amount = new int[sizeIter_amount];
	for (int i = 0, j = 1000; i < sizeIter_amount; i++) {
		Iter_amount[i] = j;
		j *= 10;
	}
	Iter_amount[5] = 1000000000; // 1 000 000 000
	cout << "-------------------------------------------------------" << endl;
	/*for (int i = 0; i < sizeIter_amount; i++) {
		cout << "������ �������� ������� ������� �������� �� ������ 2^256 ��� " << Iter_amount[i] << " ��������: " << endl;
		average_time_count(a_256, b_256, mod_256, BigInteger(Iter_amount[i]));
		cout << endl << "������ �������� ������� ������� �������� �� ������ 2^512 ��� " << Iter_amount[i] << " ��������: " << endl;
		average_time_count(a_512, b_512, mod_512, BigInteger(Iter_amount[i]));
		cout << endl << "������ �������� ������� ������� �������� �� ������ 2^1024 ��� " << Iter_amount[i] << " ��������: " << endl;
		average_time_count(a_1024, b_1024, mod_1024, BigInteger(Iter_amount[i]));
		cout << endl << "������ �������� ������� ������� �������� �� ������ 2^2048 ��� " << Iter_amount[i] << " ��������: " << endl;
		average_time_count(a_2048, b_2048, mod_2048, BigInteger(Iter_amount[i]));
		cout << "-------------------------------------------------------" << endl;
	}*/
	cout << "������ �������� ������� ������� �������� �� ������ 2^256 ��� " << Iter_amount[5] << " ��������: " << endl;
	average_time_count(a_256, b_256, mod_256, BigInteger(Iter_amount[5]));
	cout << endl << "������ �������� ������� ������� �������� �� ������ 2^512 ��� " << Iter_amount[5] << " ��������: " << endl;
	average_time_count(a_512, b_512, mod_512, BigInteger(Iter_amount[5]));
	cout << endl << "������ �������� ������� ������� �������� �� ������ 2^1024 ��� " << Iter_amount[5] << " ��������: " << endl;
	average_time_count(a_1024, b_1024, mod_1024, BigInteger(Iter_amount[5]));
	cout << endl << "������ �������� ������� ������� �������� �� ������ 2^2048 ��� " << Iter_amount[5] << " ��������: " << endl;
	average_time_count(a_2048, b_2048, mod_2048, BigInteger(Iter_amount[5]));
	cout << "-------------------------------------------------------" << endl;
	delete[] Iter_amount;

	/*BigInteger a_bigInt = BigInteger::Parse("17BC9E6E5CA3078D067DDB15CB2DF7B7D5E6437F99FE5FBB91750C3D2E4AFC7FCABC5F8795D0570EBF7A90AA0603D88FB10169B55D592959BBF88E2F141B16C3", NumberStyles::AllowHexSpecifier);
	BigInteger b_bigInt = BigInteger::Parse("1F2A11C94AB245C494806E38BDADD88C3EBFD5E688A51FDDFDFFE23069EFF0BAE0BC82B1B2D07E6B56764F01B331B47D7DDE8641778784A6AEF78BC72F337B3E", NumberStyles::AllowHexSpecifier);
	BigInteger mod_bigInt = BigInteger::Parse("10C6E1E34644B70666262C3DC6BD321A8C8A65753C6D90F4628EB5866FA0B4D494CC9294BF4A7F252B74521DFBC9D290AFB73B7844D896C658F5A76423D074D8", NumberStyles::AllowHexSpecifier);
	print("A: ", a_bigInt);
	print("B: ", b_bigInt);
	print("N: ", mod_bigInt);
	print("A+B: ", BigInteger::Add(a_bigInt, b_bigInt));
	print("(A+B)modN: ", mod(BigInteger::Add(a_bigInt, b_bigInt), mod_bigInt));
	print("A-B: ", BigInteger::Subtract(a_bigInt, b_bigInt));
	print("(A-B)modN: ", mod(BigInteger::Subtract(a_bigInt, b_bigInt), mod_bigInt));
	print("A*B: ", BigInteger::Multiply(a_bigInt, b_bigInt));
	print("(A*B)modN: ", mod(BigInteger::Multiply(a_bigInt, b_bigInt), mod_bigInt));
	if (BigInteger::Compare(a_bigInt, b_bigInt) == 1) {
		print("A/B: ", BigInteger::Divide(a_bigInt, b_bigInt));
		print("(A/B)modN: ", mod(BigInteger::Divide(a_bigInt, b_bigInt), mod_bigInt));
		print("Rem_(A/B)modN: ", mod(BigInteger::Remainder(a_bigInt, b_bigInt), mod_bigInt));
	}
	else {
		print("B/A: ", BigInteger::Divide(b_bigInt, a_bigInt));
		print("(B/A)modN: ", mod(BigInteger::Divide(b_bigInt, a_bigInt), mod_bigInt));
		print("Rem_(B/A)modN: ", mod(BigInteger::Remainder(b_bigInt, a_bigInt), mod_bigInt));
	}
	cout << "-------------------------------------------------------" << endl;*/



	cin.get();
	cin.get();
}