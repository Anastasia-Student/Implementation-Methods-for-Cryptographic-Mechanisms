#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace std::chrono;
using namespace System::Globalization; // Äëÿ NumberStyles::AllowHexSpecifier
using namespace System::Numerics;
using namespace System;

void input(string message, string el)  // Ââîä ýëåìåíòîâ
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Ïîëó÷àåì äåñêðèïòîð êîíñîëè
	SetConsoleTextAttribute(hStdOut, 7);  // Ìåíÿåì öâåò òåêñòà íà ñåðûé
	cout << message;  // Âûâîäèì ñîîáùåíèå
	SetConsoleTextAttribute(hStdOut, 15);  // Ìåíÿåì öâåò òåêñòà íà áåëûé
	cin >> el; // Ââîäèì ýëåìåíò
}

void print(string message, BigInteger el)  // Âûâîä ýëåìåíòîâ
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Ïîëó÷àåì äåñêðèïòîð êîíñîëè
	SetConsoleTextAttribute(hStdOut, 7);  // Ìåíÿåì öâåò òåêñòà íà ñåðûé
	cout << message;  // Âûâîäèì ñîîáùåíèå
	SetConsoleTextAttribute(hStdOut, 15);  // Ìåíÿåì öâåò òåêñòà íà áåëûé
	Console::WriteLine(el);  // Âûâîäèì ýëåìåíò
}

void print(string message, string el)  // Âûâîä ýëåìåíòîâ
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Ïîëó÷àåì äåñêðèïòîð êîíñîëè
	SetConsoleTextAttribute(hStdOut, 7);  // Ìåíÿåì öâåò òåêñòà íà ñåðûé
	cout << message;  // Âûâîäèì ñîîáùåíèå
	SetConsoleTextAttribute(hStdOut, 15);  // Ìåíÿåì öâåò òåêñòà íà áåëûé
	cout << el << endl;  // Âûâîäèì ýëåìåíò
}
string elapsedTime(time_point<system_clock> start, time_point<system_clock> end)  // Êîíâåðòèðîâàíèå âðåìÿ â ñòðîêó
{
	int count = duration_cast<microseconds>(end - start).count();  // Ñ÷èòàåì ïðîøåäøåå âðåìÿ
	return count > 1000 ? to_string(count / 1000) + " ìñ." : to_string(count) + " ìêñ.";  // Âîçâðàùàåì ñòðîêó
}

long elapsedTime2(time_point<system_clock> start, time_point<system_clock> end)  // Êîíâåðòèðîâàíèå âðåìÿ â ñòðîêó
{
	return duration_cast<microseconds>(end - start).count();  // Âîçâðàùàåì ïðîøåäøåå âðåìÿ â ìêñ
}

static BigInteger mod(BigInteger a, BigInteger b)
{
	if (a > BigInteger(0))  // Åñëè äåëèìîå áîëüøå 0
		return a % b;  // Âîçâðàùàåì ìîäóëü a íà b
	if ((a % b) != BigInteger(0))  // Åñëè ìîäóëü íå ðàâåí 0
		// Âîçâðàùàåì îñòàòîê îò äåëåíèÿ
		return BigInteger::Subtract(BigInteger::Multiply(BigInteger::Add(BigInteger::Divide(BigInteger::Abs(a),
			b), BigInteger(1)), b), BigInteger::Abs(a));
	return 0;  // Âîçâðàùàåì 0
}

void print(BigInteger a, BigInteger b, BigInteger c, BigInteger mod_amount) {
	BigInteger result;
	time_point<system_clock> start, end;  // Ïåðåìåííûå äëÿ èçìåðåíèÿ âðåìåíè

	print("Ïåðâûé ýëåìåíò (a): ", a);
	print("Âòîðîé ýëåìåíò (b): ", b);
	print("Òðåòèé ýëåìåíò (c): ", c);
	print("Ìîäóëü (mod): ", mod_amount);
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger(0), BigInteger(1));
	end = system_clock::now();

	start = system_clock::now();
	c = mod(c, mod_amount);
	end = system_clock::now();

	print("Òðåòèé ýëåìåíò ïî ìîäóëþ:", c);
	print("Âðåìÿ ðàáîòû îïåðàöèè âçÿòèÿ ïî ìîäóëþ: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Add(c, a), mod_amount);
	end = system_clock::now();

	print("Ñóììà ïåðâîãî è òðåòüåãî ïî ìîäóëþ: ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè ñëîæåíèÿ: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Subtract(a, b), mod_amount);
	end = system_clock::now();

	print("Ðàçíèöà ïåðâîãî ýëåìåíòà è âòîðîãî ïî ìîäóëþ: ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè ðàçíèöà: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Multiply(a, b), mod_amount);
	end = system_clock::now();

	print("Óìíîæåíèå ïåðâîãî ýëåìåíòà íà âòîðîé ïî ìîäóëþ: ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè óìíîæåíèÿ: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = mod(BigInteger::Pow(a, 2), mod_amount);
	end = system_clock::now();

	print("Âîçâåäåíèå ïåðâîãî ýëåìåíòà â êâàäðàò ïî ìîäóëþ (ìîÿ ôóíêöèÿ): ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè âîçâåäåíèÿ â êâàäðàò ïåðâîãî ýëåìåíòà: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = BigInteger::ModPow(a, BigInteger(2), mod_amount);
	end = system_clock::now();

	print("Âîçâåäåíèå ïåðâîãî ýëåìåíòà â êâàäðàò ïî ìîäóëþ (âñòðîåííàÿ ôóíêöèÿ): ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè âîçâåäåíèÿ â êâàäðàò ïåðâîãî ýëåìåíòà: ", elapsedTime(start, end));
	cout << endl;

	start = system_clock::now();
	result = BigInteger::Divide(a, b);
	end = system_clock::now();

	print("Öåëàÿ ÷àñòü îò äåëåíèÿ a íà b: ", result);
	print("Âðåìÿ ðàáîòû îïåðàöèè äåëåíèå: ", elapsedTime(start, end));
	cout << endl;

	print("Òåñò íà êîððåêòíîñòü (ïðîâåðêà äèñòðèáóòèâíîñòè): ", "");
	print("Íàø ïåðâûé ýëåìåíò (a): ", a);
	print("Íàø âòîðîé ýëåìåíò (b): ", b);
	print("Íàø òðåòèé ýëåìåíò (c): ", BigInteger::Subtract(c, BigInteger(1)));
	print("Ðåçóëüòàò (a+b)*c : ", mod(BigInteger::Multiply(BigInteger::Add(a, b), BigInteger::Subtract(c, BigInteger(1))), mod_amount));
	print("Ðåçóëüòàò b*c+c*a : ", mod(BigInteger::Add(BigInteger::Multiply(b, BigInteger::Subtract(c, BigInteger(1))), BigInteger::Multiply(BigInteger::Subtract(c, BigInteger(1)), a)), mod_amount));
	cout << endl;
}

void average_time_count(BigInteger a, BigInteger b, BigInteger mod_amount) {
	BigInteger num_iter = BigInteger(0);
	BigInteger result;
	BigInteger average_time_count_add = BigInteger(0);
	BigInteger average_time_count_sub = BigInteger(0);
	BigInteger average_time_count_mul = BigInteger(0);
	BigInteger average_time_count_div = BigInteger(0);
	time_point<system_clock> start, end;  // Ïåðåìåííûå äëÿ èçìåðåíèÿ âðåìåíè
	start = system_clock::now();
	a = mod(a, mod_amount);
	end = system_clock::now();

	while (BigInteger::Compare(num_iter, BigInteger(1000000000)) != 0) { // Ïîêà íå ïðîéäåò 1000 èòåðàöèé, äåëàåì

		start = system_clock::now();
		result = BigInteger::Add(a, b);
		end = system_clock::now();
		average_time_count_add = BigInteger::Add(average_time_count_add, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Subtract(a, b);
		end = system_clock::now();
		average_time_count_sub = BigInteger::Add(average_time_count_sub, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Multiply(a, b);
		end = system_clock::now();
		average_time_count_mul = BigInteger::Add(average_time_count_mul, BigInteger(elapsedTime2(start, end)));

		start = system_clock::now();
		result = BigInteger::Divide(a, b);
		end = system_clock::now();
		average_time_count_div = BigInteger::Add(average_time_count_div, BigInteger(elapsedTime2(start, end)));

		a = BigInteger::Add(a, BigInteger(1));
		b = BigInteger::Add(b, BigInteger(1));
		num_iter++;
	}
	average_time_count_add = BigInteger::Divide(average_time_count_add, BigInteger(1000000000));
	average_time_count_sub = BigInteger::Divide(average_time_count_sub, BigInteger(1000000000));
	average_time_count_mul = BigInteger::Divide(average_time_count_mul, BigInteger(1000000000));
	average_time_count_div = BigInteger::Divide(average_time_count_div, BigInteger(1000000000));
	print("Âðåìÿ ðàáîòû îïåðàöèè Add: ", average_time_count_add);
	print("Âðåìÿ ðàáîòû îïåðàöèè Subtract: ", average_time_count_sub);
	print("Âðåìÿ ðàáîòû îïåðàöèè Multiply: ", average_time_count_mul);
	print("Âðåìÿ ðàáîòû îïåðàöèè Divide: ", average_time_count_div);
}

void main()
{
	setlocale(LC_ALL, "rus");  // Ïîääåðæêà êèðèëëèöû
	// Ïåðåìåííûå (seed)
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

	// Ìîäóëè
	BigInteger mod_256 = BigInteger::Pow(BigInteger(2), 256);
	BigInteger mod_512 = BigInteger::Pow(BigInteger(2), 512);
	BigInteger mod_1024 = BigInteger::Pow(BigInteger(2), 1024);
	BigInteger mod_2048 = BigInteger::Pow(BigInteger(2), 2048);

	print(a_256, b_256, c_256, mod_256);
	cout << endl;
	print(a_512, b_512, c_512, mod_512);
	cout << endl;
	print(a_1024, b_1024, c_1024, mod_1024);
	cout << endl;
	print(a_2048, b_2048, c_2048, mod_2048);
	cout << "-------------------------------------------------------" <<endl;
	cout << "Çàìåðû ñðåäíåãî âðåìåíè áàçîâûõ îïåðàöèé ïî ìîäóëþ 2^256 äëÿ 1000000000 èòåðàöèé (â ìêñ): " << endl;
	average_time_count(a_256, b_256, mod_256);
	cout << endl << "Çàìåðû ñðåäíåãî âðåìåíè áàçîâûõ îïåðàöèé ïî ìîäóëþ 2^512 äëÿ 1000000000 èòåðàöèé (â ìêñ): " << endl;
	average_time_count(a_512, b_512, mod_512);
	cout << endl << "Çàìåðû ñðåäíåãî âðåìåíè áàçîâûõ îïåðàöèé ïî ìîäóëþ 2^1024 äëÿ 1000000000 èòåðàöèé (â ìêñ): " << endl;
	average_time_count(a_1024, b_1024, mod_1024);
	cout << endl << "Çàìåðû ñðåäíåãî âðåìåíè áàçîâûõ îïåðàöèé ïî ìîäóëþ 2^2048 äëÿ 1000000000 èòåðàöèé (â ìêñ): " << endl;
	average_time_count(a_2048, b_2048, mod_2048);
	cout << "-------------------------------------------------------" << endl;

	BigInteger a_bigInt = BigInteger::Parse("17BC9E6E5CA3078D067DDB15CB2DF7B7D5E6437F99FE5FBB91750C3D2E4AFC7FCABC5F8795D0570EBF7A90AA0603D88FB10169B55D592959BBF88E2F141B16C3", NumberStyles::AllowHexSpecifier);
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
	cout << "-------------------------------------------------------" << endl;



	cin.get();
	cin.get();
}
