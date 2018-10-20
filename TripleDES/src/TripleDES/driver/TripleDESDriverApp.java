package TripleDES.driver;

import tripleDES.TripleDES;

public class TripleDESDriverApp {

	public static void main(String[] args){
//		String plaintext = "123456ABCD132536";
		String plaintext2 = "0123456789ABCDEF";
//		final String key = "AABB09182736CCDD";
		final String key2 = "133457799BBCDFF1";
		
		String encryptedString = "";
		
		// For adding padding bits
		int numberOfBlocks = plaintext2.length()/16;
		int padding = plaintext2.length()%16;
		if(padding != 0){
			numberOfBlocks++;
			padding = 16 - padding;
			while(padding > 0){
				plaintext2 += "0";
				padding--;
			}
		}
		int beginIndex = 0;
		while(numberOfBlocks>0) {
			final String encryptedBlock =  new TripleDES(key2).des3Encrypt(plaintext2.substring(beginIndex, beginIndex+16));			
			encryptedString += encryptedBlock;
			beginIndex +=16;
			numberOfBlocks--;
		}
		System.out.println("Encrypted String : " + encryptedString);
		
		
		final String decryptedString = new TripleDES(key2).des3Decrypt(encryptedString);
		System.out.println("Decrypted String : " + decryptedString);
		
	}
}
