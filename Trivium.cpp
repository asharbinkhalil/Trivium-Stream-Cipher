#include <iostream>
#include <bitset>
#include <sstream>
#include<string>
using namespace std;
class trivium
{
public:
	int	*LFSR_A, *LFSR_B, *LFSR_C, *KEY, *IV;

	string toBinary(string const& str)
	{
		string binary = "";
		for (char const& c : str) {
			binary += std::bitset<8>(c).to_string();
		}
		return binary;
	}
	trivium()
	{
		LFSR_A = new int[93];
		std::fill(LFSR_A, LFSR_A + 93, 0);
		LFSR_B = new int[84];
		std::fill(LFSR_B, LFSR_B + 84, 0);
		LFSR_C = new int[111];
		std::fill(LFSR_C, LFSR_C + 111, 0);
		IV = new int[80];
		KEY = new int[80];
	}
	string getData()
	{
		string plaintext="";
		cout << "\t\t\t\t\tEnter Text: ";
		cin.ignore();
		getline(cin, plaintext);
		string Binary_Plaintext = toBinary(plaintext);
		return Binary_Plaintext;
	}
	void initialization()
	{
		string iv,key,key2;
		cout << "\t\t\t\t\tENTER IV : ";
		cin >> iv;
		cout << "\t\t\t\t\tENTER KEY : ";
		cin >> key;
		iv = toBinary(iv);
		key = toBinary(key);
		iv[80] = '\0';
		key[80] = '\0';
		for (int i = 0; i < 80; i++)
		{
			IV[i] = iv[i]-48;
			KEY[i] = key[i]-48;
		}

		for (int i = 0; i < 80; i++)
		{
			LFSR_A[i] = IV[i];
			LFSR_B[i] = KEY[i];
		}
		LFSR_C[110] = 1, LFSR_C[109] = 1, LFSR_C[108] = 1;

	}
	string Encrypt(string BinaryText,string LFSR_stream)
	{
		string EncryptedBinary = "", EncryptedText = "";
		for (int i = 0; i < BinaryText.length(); i++)
			EncryptedBinary += (BinaryText[i] - 48 ^ LFSR_stream[i] - 48) + 48;

		stringstream sstream(EncryptedBinary);
		while (sstream.good())
		{
			bitset<8> bits;
			sstream >> bits;
			EncryptedText += char(bits.to_ulong());
		}
		cout << "\n\t\t\t\t\tENCRYPTED TEXT : " << EncryptedText;
		return EncryptedBinary;
	}
	void Decrypt(string BinaryText, string LFSR_stream)
	{
		string DecryptedBinary = "", DecryptedText = "";
		for (int i = 0; i < BinaryText.length(); i++)
			DecryptedBinary += (BinaryText[i] - 48 ^ LFSR_stream[i] - 48) + 48;

		stringstream sstream1(DecryptedBinary);
		while (sstream1.good())
		{
			bitset<8> bits;
			sstream1 >> bits;
			DecryptedText += char(bits.to_ulong());
		}
		cout << "\n\t\t\t\t\tDECRYPTED TEXT : " << DecryptedText;
	}
	void generate()
	{

		int ANDRES_A = 0, OUTPUT_A = 0,		ANDRES_B = 0, OUTPUT_B = 0,		ANDRES_C = 0,OUTPUT_C = 0,
			INPUT_B = 0,INPUT_C = 0,INPUT_A = 0;
		string Binary_plaintext = getData();
		string LFSR_stream="";

		int temp = 0,res=0;
		int j = 0,warmup=1152;

		while (Binary_plaintext[j] !='\0')
		{
		//LFSR_A right shift 
		temp = LFSR_A[92];
		for (int i = 92; i > 0; i--)
			LFSR_A[i] = LFSR_A[i - 1];
		LFSR_A[0] = INPUT_A;

		ANDRES_A = LFSR_A[90] * LFSR_A[91];
		OUTPUT_A = LFSR_A[65] ^ ANDRES_A ^ LFSR_A[92];
		INPUT_B = OUTPUT_A ^ LFSR_B[77];

		//LFSR_B RIGHT SHIFT
		temp = LFSR_B[83];
		for (int i = 83; i > 0; i--)
			LFSR_B[i] = LFSR_B[i - 1];

		LFSR_B[0] = INPUT_B;


		ANDRES_B = LFSR_B[81] * LFSR_B[82];
		OUTPUT_B = LFSR_B[68] ^ ANDRES_B ^ LFSR_B[83];
		INPUT_C = OUTPUT_B ^ LFSR_C[86];

		//LFSR_C RIGHT SHIFT

		temp = LFSR_C[110];
		for (int i = 110; i > 0; i--)
			LFSR_C[i] = LFSR_C[i - 1];

		LFSR_C[0] = INPUT_C;


		ANDRES_C = LFSR_C[108] * LFSR_C[109];
		OUTPUT_C = LFSR_C[65] ^ ANDRES_C ^ LFSR_C[110];
		INPUT_A = OUTPUT_C ^ LFSR_A[68];
		res= OUTPUT_A ^ OUTPUT_B ^OUTPUT_C;
		LFSR_stream += res+48;
		j++;
	}
		//cout <<"STREAM GENERATED BY LFSR: \n" << LFSR_stream;
		int choice = 0;
		cout << "\t\t\t\t\tStream Generated: \n\t\t\t\t\tEnter Choice : ";
		cin >> choice;
		if (choice == 1)
		{
			string Encrypted_PLaintext = Encrypt(Binary_plaintext, LFSR_stream);
			Decrypt(Encrypted_PLaintext, LFSR_stream);
		}
		else if (choice == 2)
			string v=Encrypt(Binary_plaintext, LFSR_stream);
		else if (choice == 3)
			Decrypt(Binary_plaintext, LFSR_stream);
	}
};
int main() {
	cout << "\t\t\t\t------------------- ASHAR KHALIL----------------------\n";
	cout << "\t\t\t\t-------------	      20K - 1724        --------------\n";
	cout << "\t\t\t\t------------  NUMBER THEORY & CRYPTO   ---------------\n";
	cout << "\t\t\t\t---------- TRIVIUM CIPHER IMPLEMENTATION  ------------\n\n\n";
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t|      Made with love by ASHAR  :)     | ";
	cout << "\n\t\t\t\t\t| -> Loads data from a file.           |";
	cout << "\n\t\t\t\t\t| -> Convert to binary.                |";
	cout << "\n\t\t\t\t\t| -> Generate stream by LFSR's.        |";
	cout << "\n\t\t\t\t\t| -> Apply Mechanism.                  |";
	cout << "\n\t\t\t\t\t| -> Do Encryption or Decryption.      |";
	cout << "\n\t\t\t\t\t/--------------------------------------/\n\n\n\n";
	trivium t;
	t.initialization();
	t.generate();
}