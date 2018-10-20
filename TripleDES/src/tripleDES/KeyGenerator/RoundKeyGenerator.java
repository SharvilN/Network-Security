package tripleDES.KeyGenerator;

import java.util.ArrayList;
import java.util.Arrays;

public class RoundKeyGenerator {
	private String keyWithParityBits;
	private static final ArrayList<Integer> ROUND_SHIFT = new ArrayList<Integer>(Arrays.asList(1, 2, 9, 16));
	private static final ArrayList<Integer> PARITY_DROP_TABLE = new ArrayList<Integer>(Arrays.asList(57  , 49   , 41   ,33 ,   25   , 17 ,   9,
            1 ,  58    ,50  , 42  ,  34  ,  26  , 18,
           10 ,   2   , 59 ,  51  ,  43  ,  35  , 27,
           19  , 11   ,  3  , 60  ,  52  ,  44  , 36,
           63  , 55  ,  47  , 39  ,  31   , 23  , 15,
            7  , 62   , 54  , 46  ,  38  ,  30  , 22,
           14  ,  6   , 61  , 53  ,  45   , 37  , 29,
           21  , 13  ,   5  , 28  ,  20  ,  12  ,  4));
	
	private static final ArrayList<Integer> PBOX_KEY_COMPRESSION_TABLE = new ArrayList<Integer>(Arrays.asList(14,    17,   11,    24,     1,    5,
		    3   , 28 ,  15    , 6  ,  21  , 10 ,
		    23    ,19  , 12   ,  4 ,  26  ,  8,
		    16     ,7  , 27  ,  20  ,  13  ,  2,
		    41   , 52 ,  31  ,  37  ,  47  , 55,
		    30   , 40  , 51  ,  45  ,  33 , 48,
		    44    ,49 ,  39  ,  56  ,  34 ,  53,
		    46    ,42 ,  50  ,  36 ,   29 ,  32));
	
	public RoundKeyGenerator(final String keyWithParityBits){
		
		this.keyWithParityBits = keyWithParityBits;
		while(this.keyWithParityBits.length() < 64){
			this.keyWithParityBits = "0" + this.keyWithParityBits;
		}
	}
	
	public ArrayList<String> getRoundKeys(){
		ArrayList<String> roundKeyList = new ArrayList<String>();
		final String cipherKey = this.parityDrop();

		String leftPartOfCipherKey = cipherKey.substring(0, cipherKey.length()/2);
		String rightPartOfCipherKey = cipherKey.substring(cipherKey.length()/2);
		
		for(int round = 1; round <= 16; round++){
			if(ROUND_SHIFT.contains(round)){
				leftPartOfCipherKey = leftPartOfCipherKey.substring(1) + leftPartOfCipherKey.substring(0, 1);
				rightPartOfCipherKey = rightPartOfCipherKey.substring(1) + rightPartOfCipherKey.substring(0, 1);
			}
			else{
				leftPartOfCipherKey = leftPartOfCipherKey.substring(2) + leftPartOfCipherKey.substring(0, 2);
				rightPartOfCipherKey = rightPartOfCipherKey.substring(2) + rightPartOfCipherKey.substring(0, 2);
			}
			final String combinedKey = leftPartOfCipherKey + rightPartOfCipherKey;
			roundKeyList.add(this.compressKeyWithPBox(combinedKey));
		}
		return roundKeyList;
	}
	
	private String compressKeyWithPBox(final String combinedKey) {
		String compressedKey = "";
		for(int i=0; i<PBOX_KEY_COMPRESSION_TABLE.size(); i++){
			compressedKey += combinedKey.charAt(PBOX_KEY_COMPRESSION_TABLE.get(i)-1);
		}
		return compressedKey;
	}

	public String parityDrop(){
		String cipherKey = "";
		for(int i=0; i<PARITY_DROP_TABLE.size(); i++){
			cipherKey += keyWithParityBits.charAt(PARITY_DROP_TABLE.get(i)-1);
		}
		return cipherKey;
	}
}
