package hydraulic;

/**
 * Main class that act as a container of the elements for
 * the simulation of an hydraulics system 
 * 
 */
public class HSystem {
	
	private static final int MAX_ELEMENTS = 100;

	private Element[] elements = new Element[MAX_ELEMENTS];
	
	private int nextElement=0;
	
	/**
	 * Adds a new element to the system
	 * @param elem
	 */
	public void addElement(Element elem){
		elements[nextElement++]=elem;
	}
	
	/**
	 * returns the element added so far to the system
	 * @return an array of elements whose length is equal to the number of added elements
	 */
	public Element[] getElements(){
		Element[] result = new Element[nextElement];
		for (int i = 0; i < result.length; i++) {
			result[i]=elements[i];
		}
		return result;
	}
	
	/**
	 * Prints the layout of the system starting at each Source
	 */
	public String layout(){
		StringBuffer result = new StringBuffer();
		for (Element element : elements) {
			if (element != null && element instanceof Source) {
				result.append(element.layout(0)).append("\n");
			}
		}
		return result.toString();
	}
	
	/**
	 * starts the simulation of the system
	 */
	public void simulate(){
		for (Element element : elements) {
			if (element != null && element instanceof Source) {
				element.simulate(-1);
			}
		}
	}

}
