package hydraulic;

/**
 * Represents a source of water, i.e. the initial element for the simulation.
 *
 * Lo status of the source is defined through the method
 * {@link #setFlow(double) setFlow()}.
 */
public class Source extends Element {
	
	private double flow;

	/**
	 * Constructor
	 * @param name
	 */
	public Source(String name) {
		super(name);
	}

	public void setFlow(double flow){
		this.flow = flow;
	}

	@Override
	public StringBuffer layout(int indent) {
		StringBuffer result = new StringBuffer();
		result.append("[").append(getName()).append("] Source -> ");
		result.append(getOutput().layout(result.length()));
		return result;
	}

	@Override
	public void simulate(double inFlow) {
		System.out.println(getName()+" "+flow+" "+flow);
		getOutput().simulate(flow);
	}
	
}
