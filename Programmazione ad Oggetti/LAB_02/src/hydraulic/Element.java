package hydraulic;

/**
 * Represents the generic abstract element of an hydraulics system.
 * It is the base class for all elements.
 *
 * Any element can be connect to a downstream element
 * using the method {@link #connect(Element) connect()}.
 */
public abstract class Element {
	
	private String name;
	private Element output;
	
	/**
	 * Constructor
	 * @param name the name of the element
	 */
	public Element(String name){
		this.name=name;
	}

	/**
	 * getter method
	 * @return the name of the element
	 */
	public String getName(){
		return name;
	}
	
	/**
	 * Connects this element to a given element.
	 * The given element will be connected downstream of this element
	 * @param elem the element that will be placed downstream
	 */
	public void connect(Element elem){
		output=elem;
	}
	
	/**
	 * Retrieves the element connected downstream of this
	 * @return downstream element
	 */
	public Element getOutput(){
		return output;
	}
	
	public abstract StringBuffer layout(int indent) ;
	
	public abstract void simulate(double inFlow) ;
	
}
