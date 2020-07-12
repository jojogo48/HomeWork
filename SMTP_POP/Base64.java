import java.io.*;

public class Base64
{

	private static char[] encodeChars = new char[] {
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
'w', 'x', 'y', 'z', '0', '1', '2', '3',
'4', '5', '6', '7', '8', '9', '+', '/' };

	private static byte[] decodeChars = new byte[] {
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1 };

	public Base64() { }

	public String encode(byte[] data)
	{
		String res = "";
		int len = data.length;
		int i = 0;
		int m1, m2, m3;
		while (i < len)
		{
			m1 = data[i++] & 0xff;
			if (i == len)
			{

				res += encodeChars[m1 >>> 2];
				res += encodeChars[(m1 & 0x3) << 4];
				res += "==";
				break;
			}
			m2 = data[i++] & 0xff;
			if (i == len)
			{
				res += encodeChars[m1 >>> 2];
				res += encodeChars[((m1 & 0x03) << 4) | ((m2 & 0xf0) >>> 4)];
				res += encodeChars[(m2 & 0x0f) << 2];
				res += "=";
				break;
			}
			m3 = data[i++] & 0xff;
			res += encodeChars[m1 >>> 2];
			res += encodeChars[((m1 & 0x03) << 4) | ((m2 & 0xf0) >>> 4)];
			res += encodeChars[((m2 & 0x0f) << 2) | ((m3 & 0xc0) >>> 6)];
			res += encodeChars[m3 & 0x3f];
			if (i >= len) break;
			//System.out.println(i);
		}
		//if (res.length > 76)
		//{
		//	for(int i=0;i<=res.length/76;i++)
		//	{
				
		//	}
		//}
		
		return res;
	}
	public static byte[] decode(String str)
	{
		byte[] data = str.getBytes();
		int len = data.length;
		ByteArrayOutputStream buf = new ByteArrayOutputStream(len);
		int i = 0;
		int b1, b2, b3, b4;

		while (i < len)
		{

			/* b1 */
			do
			{
				b1 = decodeChars[data[i++]];
			} while (i < len && b1 == -1);
			if (b1 == -1)
			{
				break;
			}

			/* b2 */
			do
			{
				b2 = decodeChars[data[i++]];
			} while (i < len && b2 == -1);
			if (b2 == -1)
			{
				break;
			}
			buf.write((int)((b1 << 2) | ((b2 & 0x30) >>> 4)));

			/* b3 */
			do
			{
				b3 = data[i++];
				if (b3 == 61)
				{
					return buf.toByteArray();
				}
				b3 = decodeChars[b3];
			} while (i < len && b3 == -1);
			if (b3 == -1)
			{
				break;
			}
			buf.write((int)(((b2 & 0x0f) << 4) | ((b3 & 0x3c) >>> 2)));

			/* b4 */
			do
			{
				b4 = data[i++];
				if (b4 == 61)
				{
					return buf.toByteArray();
				}
				b4 = decodeChars[b4];
			} while (i < len && b4 == -1);
			if (b4 == -1)
			{
				break;
			}
			buf.write((int)(((b3 & 0x03) << 6) | b4));
		}
		return buf.toByteArray();
	}

}