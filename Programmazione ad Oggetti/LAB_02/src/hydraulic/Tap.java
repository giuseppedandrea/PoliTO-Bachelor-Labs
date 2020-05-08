package hydraulic;

/**
 * Represents a tap that can interrupt the flow.
 * 
 * The status of the tap is defined by the method
 * {@link #setOpen(boolean) setOpen()}.
 */

public class Tap extends Element {
	
	private boolean open;

	/**
	 * Constructor
	 * @param name
	 */
	public Tap(String name) {
		super(name);
	}
	
	public void setOpen(boolean open){
		this.open = open;
	}

	@Override
	public StringBuffer layout(int indent) {
		StringBuffer result = new StringBuffer();
		result.append("[").append(getName()).append("] Tap -> ");
		result.append(getOutput().layout(result.length()+indent));
		return result;
	}

	@Override
	public void simulate(double inFlow) {
		double outFlow=0;
		if (open) {
			outFlow=inFlow;
		}
		System.out.println(getName()+" "+inFlow+" "+outFlow);
		getOutput().simulate(outFlow);
	}

}
