import java.util.*;

public class Player{
	private String name;
	public ArrayList<Card> main = new ArrayList<>();
	public ArrayList<Card> visible = new ArrayList<>();
	public ArrayList<Card> hidden = new ArrayList<>();
	
	Player(String Name){
		name = Name;
	}
	
	// méthode pour définir les cartes faces cachées en début de partie
	protected void setHiddenCards(){
		/*
		// En attendant de savoir comment faire pour appeler cette fonction sans arguments
		if(hidden.size()==0){
			hidden.add(card1);
			hidden.add(card2);
			hidden.add(card3);
		}
		else{
			System.out.println("Tente de rajouter une nouvelle carte face cachée après le début du jeu.");
		}
		*/
	}
	
	// méthode pour définir les cartes visibles en début de partie
	protected void setVisibleCards(){
		/*
		// En attendant de savoir comment faire pour appeler cette fonction sans arguments
		if(visible.size()<4){
			visible.add(card1);
		}
		else{
			System.out.println("Tente de rajouter une 4eme carte face visible.");
		}*/
	}
	
	// enlève la carte à l'index i de la liste des cartes visibles
	protected void unsetVisibleCard(int i){
		visible.remove(i);
	}
	
	// enlève la carte à l'index i de la liste des cartes en main
	protected void unsetMainCard(int i){
		main.remove(i);
	}
	
	// enlève la carte à l'index i de la liste des cartes faces cachées
	protected void unsetHiddenCard(int i){
		hidden.remove(i);
	}
	
	// ajoute la carte card dans la liste main en la gardant triée (ordre croissant de range puis ordre croissant de couleur)
	protected void addInMainCard(Card card){
		int i = 0;
		while(i<main.size()){
			while(i<main.size() && main.get(i).getRange()<card.getRange())
				i++;
			while(i<main.size() && main.get(i).getRange()==card.getRange() && main.get(i).getColor()<=card.getColor())
				i++;
			break;
		}
		main.add(i,card);
	}
	
	// ajoute une liste de cartes à la liste main en la gardant triée
	protected void getCards(ArrayList<Card> liste){
		for(Card card : liste)
			addInMainCard(card);
	}
	
	// vérifie si le joueur a un carré
	protected void checkCarre(){
		int i = 0;
		int j = 1;
		// si le joueur a moins de 4 cartes en main
		if(main.size()<4)
			return;
		// parcours de la main
		while(i-3<main.size()){
			// tant que deux cartes consécutives n'ont pas la même range, on avance dans la liste main
			while(i-3<main.size() && !Card.areTheSame(main.get(i),main.get(j))){
				i++;
				j++;
			}
			// tant que la range de la carte à l'index i de la liste main est la même que celle à l'index j, on incrémente j de 1
			while(i-3<main.size() && Card.areTheSame(main.get(i),main.get(j)) && j<i+3)
				j++;	
		}
		// si le joueur a 4 cartes identiques, on les supprime toutes les 4
		if(j==i+3){
			for(int k=i; k<=j ; k++){
				unsetMainCard(k);
			}
		}
	}
	
	// on enlève la carte à l'index i au joueur
	protected void throwCard(int i){
		// détermine de quelle liste on enlève la carte à l'index i
		if(main.size()>0 && i<main.size()){
				unsetMainCard(i);
		}
		else if(main.size()==0 && visible.size()>0 && i<visible.size()){
				unsetVisibleCard(i);
		}
		else if(main.size()==0 && visible.size()==0 && hidden.size()>0 && i<hidden.size()){
				unsetHiddenCard(i);
		}
		else{
			System.out.println("Erreur : tente de jeter une carte alors qu'il n'y en a plus (Player.throwCard())");
			return;
		}
	}
	
	// indique quelle liste on utilise
	protected int getType(){
		if(main.size()>0)
			return 0;
		if(visible.size()>0)
			return 1;
		if(hidden.size()>0)
			return 2;
		return 3;
	}
	
	// indique si la carte à l'index i de la liste liste est jouable après qu'on est posé la carte lastCard sur le tas
	private boolean canPlay(Card lastCard, ArrayList<Card> liste, int i){
		// 8 --> saute le tour
		if(lastCard.getRange()==8)
			return false;
			
		// 2/3/10 --> peuvent toujours être jouées
		if(lastCard.getRange()==2 || liste.get(i).getRange()==2 || liste.get(i).getRange()==3 || liste.get(i).getRange()==10){
			return true;
		}
		
		// si la dernière carte posée est un 7 est qu'on a au moins une carte en dessous ou égale à 7
		if(lastCard.getRange()==7 && (liste.size()>0 && liste.get(i).getRange()<=7)){
			return true;
		}
		
		// Si la range de la carte posée est inférieure ou égale à la carte que l'on regarde
		if(liste.get(i).getRange()>=lastCard.getRange()){
			return true;
		}
		
		// sinon
		return false;		
	}
	
	// retourne la liste des index des cartes jouables
	protected ArrayList<Integer> couldPlay(Card lastCard, int type){
		ArrayList<Integer> res = new ArrayList<>();
		ArrayList<Card> temp;
		// détermine la liste qu'on utilise
		switch(type){
			case 1 :
				temp = visible;
				break;
			case 2 :
				temp = hidden;
				break;
			default:
				temp = main;
		}
		
		// pour chaque carte de cette liste, on ajoute son index si on peut la joueur
		for(int i=0; i<temp.size(); i++){
			if(canPlay(lastCard,temp,i))
				res.add(i);
		}
		
		// on retourne la liste
		return res;
	}
	
	
	// indique si le joueur a fini la partie
	protected boolean hasFinished(){
		return (visible.size()==0 && hidden.size()==0 && main.size()==0);
	}

}
