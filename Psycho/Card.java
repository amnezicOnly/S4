enum Color{
	COEUR,
	TREFLE,
	CARREAU,
	PIC
}
	
enum Range{
	DEUX,
	TROIS,
	QUATRE,
	CINQ,
	SIX,
	SEPT,
	HUIT,
	NEUF,
	DIX,
	VALET,
	DAME,
	ROI,
	AS
}

public class Card{
	private Color color;
	private Range range; 

	
	
	Card(Color _color, Range _range){
		color = _color;
		range = _range;
	}
	
    	protected int getColor(){
    		switch(color){
    			case COEUR :
    				return 0;
    			case TREFLE :
    				return 1;
    			case CARREAU :
    				return 2;
    			case PIC :
    				return 3;
    		}
    		return -1;
    	}
    	
    	protected int getRange(){
    		switch(range){
    			case DEUX :
    				return 0;
    			case TROIS :
    				return 1;
    			case QUATRE :
    				return 2;
    			case CINQ :
    				return 3;
    			case SIX :
    				return 4;
    			case SEPT :
    				return 5;
    			case HUIT :
    				return 6;
    			case NEUF :
    				return 7;
    			case DIX :
    				return 8;
    			case VALET :
    				return 9;
    			case DAME :
    				return 10;
    			case ROI :
    				return 11;
    			case AS :
    				return 12;
    		}
    		return -1;
    	}
    	
    	protected static int compare(Card card1, Card card2){
    		return card1.getRange()-card2.getRange();
    	}
    	
    	protected static boolean areTheSame(Card card1, Card card2){
    		return (compare(card1,card2)==0 && card1.getColor()==card2.getColor());
    	}
}
