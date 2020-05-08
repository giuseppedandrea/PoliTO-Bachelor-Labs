package hydraulic;

/**
 * Represents the sink, i.e. the terminal element of a system
 *
 */
public class Sink extends Element {

	/**
	 * Constructor
	 * @param name
	 */
	public Sink(String name) {
		super(name);
	}
	
	@Override
	public void connect(Element elem){
		System.err.println("Metodo connect non disponibile per oggetto Sink");
	}

	@Override
	public StringBuffer layout(int indent) {
		StringBuffer result = new StringBuffer();
		result.append("[").append(getName()).append("] Sink |");
		return result;
	}

	@Override
	public void simulate(double inFlow) {
		System.out.println(getName()+" "+inFlow);		
	}
		
}
