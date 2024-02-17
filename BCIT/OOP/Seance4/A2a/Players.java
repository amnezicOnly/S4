public abstract class Players{
	String[] lifeForms = {"Herbs","Herbivors"};
	
	public int getLifeFormNumber(Players type) {
		if(type==null)
			return -2;
		int max = lifeForms.length;
		String temp = type.getClass().getSimpleName();
        	for (int i = 0; i < max; i++) {
            		if(lifeForms[i]==temp) {
                		return i;
            		}
        	}
        	// Si aucune correspondance trouvée, retourner une valeur par défaut
        	return -1;
    	}
}
