import java.util.*;

public class Game{
	private int maxCards;
	private ArrayList<Player> players;
	private ArrayList<Card> pioche = new ArrayList<>();
	private Random random = new Random();
	
	Game(int cardNumber, ArrayList<Player> joueurs){
		maxCards = cardNumber;
		players = joueurs;
		
	}
	
	void setCards(){
		for(int j=0; j<Color.values().length ; j++){
			for(int k=0; k<Range.values().length ; k++){
				pioche.add(new Card(Color.values()[j],Range.values()[k]));
			}
		}
		Collections.shuffle(pioche);
	}
	
	void distributionCartes(){
		int donnees = 0;
		int numPlayers = players.size();
		while(donnees<numPlayers*9){
			for(int i = 0; i<numPlayers ; i++){
				(players.get(i)).addInMainCard(pioche.remove(random.nextInt(pioche.size())));
				donnees++;
			}
		}
	}
	
	boolean setSixCards(){
		for(Player player : players){
			player.setHiddenCards();
			player.setVisibleCards();
		}
		return true;
	}
	
	boolean firstLap(){
		setCards();
		distributionCartes();
		setSixCards();
		return true;
	}
	
	<T> void swap(ArrayList<T> liste, int i, int j){
		T temp = liste.get(i);
		liste.set(i,liste.get(j));
		liste.set(j,temp);
	}
	
	<T> void push(ArrayList<T> liste, int i){
		int max = liste.size();
		while(i<max-1){
			swap(liste,i,i+1);
		}
	}
	
	void game(){
		boolean ready = firstLap();
		int stillPlaying = players.size();
		Card joker = new Card(Color.values()[1],Range.values()[0]);
		ArrayList<Integer> jouables;
		// tant qu'il y a au moins 2 joueurs
		while(stillPlaying>1){
			// on crée la liste qui va contenir les cartes du tour actuel
			ArrayList<Card> current = new ArrayList<>();
			// pour chaque joueur restant
			for(int i = 0; i<stillPlaying ; i++){
				// On regarde si le joueur courant peut joueur
				int type = players.get(i).getType();
				if(current.size()==0){	// Si c'est le premier à poser une carte, il peut mettre n'importe quelle carte
					 jouables = players.get(i).couldPlay(joker,type);
				} else {					
					jouables = players.get(i).couldPlay(current.get(current.size()-1),type);
				}
				// Sinon : il reprend toutes les cartes de la liste current (la pile) et donc ne peut pas avoir fini
				if(jouables.size()==0){
					// TODO
				}
				else{
					// Si oui, il pose la carte qu'il a choisi (pour l'instant simulé par un random)
					int index = random.nextInt(jouables.size());
					// Si la carte posée est un 10, on jette le tas et on refait jouer le joueur actuel
					if(current.get(current.size()-1).getRange()==10){
						current.clear();
						// on fait rejouer le joueur qui vient de poser le 10 si c'est possible
					}
					// S'il n'a plus de carte, cela veut dire qu'il ne joue plus
					if(players.get(i).hasFinished()){
						// on le décale à la fin de la liste des joueurs
						push(players,i);
						// on décrémente le nombre de joueurs restants
						stillPlaying--;
					}
				}
			}
		}
	}
	
}
