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
	
	protected Color getColor(){
		return color;
	}
	
	protected Range getRange(){
		return range;
	}
	
	public static int compareCardsRange(Card card1, Card card2){
		return card1.range-card2.range;
	}
	
	public static boolean areTheSame(Card card1, Card card2){
		return (compareCardsRange(card1,card2)==0 && card1.color==card2.color);
	}
}
