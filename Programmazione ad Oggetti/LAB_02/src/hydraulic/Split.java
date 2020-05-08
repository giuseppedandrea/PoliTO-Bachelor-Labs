package hydraulic;

/**
 * Represents a split element, a.k.a. T element
 * 
 * During the simulation each downstream element will
 * receive a stream that is half the input stream of the split.
 */

public class Split extends Element {
	
	private static final int MAX_OUTPUTS = 2;
	
	private Element[] outputs = new Element[MAX_OUTPUTS];

	/**
	 * Constructor
	 * @param name
	 */
	public Split(String name) {
		super(name);
	}
	
	/**
	 * Connects this element to a given element.
	 * The given element will be connected downstream of this element
	 * @param elem the element that will be placed downstream
	 * @param noutput determines the output that is being connected
	 */
	public void connect(Element elem, int noutput){
		outputs[noutput]=elem;
	}
    
	/**
	 * returns the downstream elements
	 * @return array containing the two downstream element
	 */
    public Element[] getOutputs(){
        return outputs;
    }

	@Override
	public StringBuffer layout(int indent) {
		StringBuffer result = new StringBuffer();
		result.append("[").append(getName()).append("] Split +-> ");
		int spaces=result.length()+indent-4;
		result.append(getOutputs()[0].layout(result.length()+indent));
		result.append("\n");
		for (int i = 0; i < spaces; i++) {
			result.append(" ");
		}
		result.append("|\n");
		for (int i = 0; i < spaces; i++) {
			result.append(" ");
		}
		result.append("+-> ");
		result.append(getOutputs()[1].layout(result.length()+indent));
		return result;
	}

	@Override
	public void simulate(double inFlow) {
		double outFlow=inFlow/2;
		System.out.println(getName()+" "+inFlow+" "+outFlow);
		getOutputs()[0].simulate(outFlow);
		getOutputs()[1].simulate(outFlow);
	}

}
