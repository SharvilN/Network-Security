package tripleDES;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;

import tripleDES.KeyGenerator.RoundKeyGenerator;

public class TripleDES {
	private static final ArrayList<Integer> INITIAL_PERMUTATION_TABLE = new ArrayList<Integer>(Arrays.asList(
			58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,  
            62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,  
            57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,  
            61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7));
	
	private static final ArrayList<Integer> FINAL_PERMUTATION_TABLE = new ArrayList<Integer>(Arrays.asList(
			40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,  
            38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,  
            36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,  
            34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25));
	
	ArrayList<String> roundKeys;
	
	private String hexToBinary(final String hexString){
		final BigInteger num = new BigInteger(hexString, 16);
		final String binaryString = num.toString(2);
		return binaryString;
	}
	
	public TripleDES(final String keyWithParityBits){
		roundKeys = new RoundKeyGenerator(hexToBinary(keyWithParityBits)).getRoundKeys();
	}
	
	public String des3Encrypt(String hexPlainBlock){
		String encryptedString = "";
		for(int i=0; i<3; i++){
			encryptedString = this.desEncrypt(hexPlainBlock);
			hexPlainBlock = encryptedString;
		}
		return encryptedString;
	}
	
	public String des3Decrypt(String hexPlainBlock){
		String decryptedString = "";
		for(int i=0; i<3; i++){
			decryptedString = this.desDecrypt(hexPlainBlock);
			hexPlainBlock = decryptedString;
		}
		return decryptedString;
	}
	
	private String desEncrypt(final String hexPlainBlock){
		String plainBlock = this.hexToBinary(hexPlainBlock);
		System.out.println("Plain block : " + plainBlock);
		System.out.println("Plain block Hex : " + binaryToHex(plainBlock));
		DESFunction desFunction = new DESFunction();
		int differenceInLength = 64-plainBlock.length();
		String zeros = "";
		while(differenceInLength>0){
			zeros += "0";
			differenceInLength--;
		}
		plainBlock = zeros + plainBlock;
		plainBlock = this.initialPermutation(plainBlock);

		String leftBlock = plainBlock.substring(0, (plainBlock.length())/2);
		String rightBlock = plainBlock.substring(plainBlock.length()/2);
		System.out.println("Left : " + binaryToHex(leftBlock) + " Right : " + binaryToHex(rightBlock));

		for(int round=1; round<=16; round++){
			String functionedBlock = desFunction.coreFunction(rightBlock, roundKeys.get(round-1));
			String xoredBlock = this.doXOR(leftBlock, functionedBlock);
			if(round != 16){
				leftBlock = rightBlock;
				rightBlock = xoredBlock;	
			}
			else{
				leftBlock = xoredBlock;
			}
			System.out.println("Round key " + round + " : " + binaryToHex(roundKeys.get(round-1)));
			System.out.println("Left : " + binaryToHex(leftBlock) + " Right : " + binaryToHex(rightBlock));
		}
		System.out.println("Left : " + leftBlock + " Right : " + rightBlock);
		final String cipherBlock = this.finalPermutation(leftBlock + rightBlock);
		return binaryToHex(cipherBlock);
	}
	
	public String desDecrypt(final String hexPlainBlock){
		String plainBlock = this.hexToBinary(hexPlainBlock);
		System.out.println("Plain block : " + plainBlock);
		System.out.println("Plain block Hex : " + binaryToHex(plainBlock));
		DESFunction desFunction = new DESFunction();
		int differenceInLength = 64-plainBlock.length();
		String zeros = "";
		while(differenceInLength>0){
			zeros += "0";
			differenceInLength--;
		}
		plainBlock = zeros + plainBlock;
		plainBlock = this.initialPermutation(plainBlock);

		String leftBlock = plainBlock.substring(0, (plainBlock.length())/2);
		String rightBlock = plainBlock.substring(plainBlock.length()/2);
		System.out.println("Left : " + binaryToHex(leftBlock) + " Right : " + binaryToHex(rightBlock));

		for(int round=1; round<=16; round++){
			String functionedBlock = desFunction.coreFunction(rightBlock, roundKeys.get(16 - round));
			String xoredBlock = this.doXOR(leftBlock, functionedBlock);
			if(round != 16){
				leftBlock = rightBlock;
				rightBlock = xoredBlock;	
			}
			else{
				leftBlock = xoredBlock;
			}
			System.out.println("Round key " + round + " : " + binaryToHex(roundKeys.get(16 - round)));
			System.out.println("Left : " + binaryToHex(leftBlock) + " Right : " + binaryToHex(rightBlock));
		}
		System.out.println("Left : " + leftBlock + " Right : " + rightBlock);
		final String cipherBlock = this.finalPermutation(leftBlock + rightBlock);
		return binaryToHex(cipherBlock);	}
	
	private String doXOR(final String plainText32Bit, final String keyString) {
		String xoredString = "";
		for(int i=0; i<keyString.length(); i++){
			if(plainText32Bit.charAt(i) != keyString.charAt(i)){
				xoredString += "1";
			}
			else{
				xoredString += "0";
			}
		}
		return xoredString;
	}
	
	private String binaryToHex(final String binaryString){
		final BigInteger num = new BigInteger(binaryString, 2);
		return num.toString(16);
	}
	
	private String initialPermutation(final String plainBlock){
		String permutedBlock = "";
		for(int i=0; i<INITIAL_PERMUTATION_TABLE.size(); i++){
			permutedBlock += plainBlock.charAt(INITIAL_PERMUTATION_TABLE.get(i)-1);
		}
		return permutedBlock;
	}
	
	private String finalPermutation(final String cipherBlock){
		String permutedBlock = "";
		for(int i=0; i<FINAL_PERMUTATION_TABLE.size(); i++){
			permutedBlock += cipherBlock.charAt(FINAL_PERMUTATION_TABLE.get(i)-1);
		}
		return permutedBlock;
	}
}
