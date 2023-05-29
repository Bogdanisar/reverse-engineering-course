using System;

public class Program
{

	public static string btnDecode_Click() {
		byte[] dat_secret = {0xA1, 0xB5, 0x44, 0x84, 0x14, 0xE4, 0xA1, 0xB5, 0xD4, 0x70,
		                     0xB4, 0x91, 0xB4, 0x70, 0xD4, 0x91, 0xE4, 0xC4, 0x96, 0xF4,
		                     0x54, 0x84, 0xB5, 0xC4, 0x40, 0x64, 0x74, 0x70, 0xA4, 0x64, 0x44};
		string text = "";
		foreach (byte b in dat_secret)
		{
			text += (char)((b >> 4 | ((int)b << 4 & 240)) ^ 41);
		}
		text += "\0";

		string text2 = "";
		for (int j = 0; j < text.Length; j += 2)
		{
			text2 += text[j + 1];
			text2 += text[j];
		}

		string text3 = "";
		for (int k = 0; k < text2.Length; k++)
		{
			char c = text2[k];
			text3 += (char)((byte)text2[k] ^ 102);
		}

		Console.WriteLine($"text = {text}");
		Console.WriteLine($"text2 = {text2}");
		Console.WriteLine($"text3 = {text3}");
		return text3;
	}

	public static void Main()
	{
		btnDecode_Click();
		//Console.WriteLine("Hello World");
	}
}