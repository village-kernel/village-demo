/// @brief print
/// @param string 
void print(char* string)
{
	char* videoMemory = (char*)0xb8000;

	for (int i = 0; 0 != string[i]; i++)
	{
		*videoMemory = string[i];
		videoMemory = videoMemory + 2;
	}
}


/// @brief main
/// @return 
int main()
{
	print("Village-Kernel, Hello C world!");

	while (1) {}
}
